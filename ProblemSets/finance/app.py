import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    ownedStocks = db.execute(
        "SELECT symbol as symbol, SUM(shares) as shares FROM history  WHERE user_id = ? GROUP BY symbol HAVING SUM(shares) > 0", session["user_id"])
    runningTotal = 0
    for ownedStock in ownedStocks:
        symbol = ownedStock["symbol"]
        shares = ownedStock["shares"]

        # current price of each stock
        item = lookup(symbol)
        price = item["price"]
        ownedStock["currentprice"] = usd(price)

        # total value of each holding
        tmp = price * ownedStock["shares"]
        ownedStock["total"] = usd(tmp)
        runningTotal += tmp

    liquid = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
    totalValue = runningTotal + liquid[0]["cash"]

    return render_template('index.html', stocks=ownedStocks, cash=usd(liquid[0]["cash"]), totalValue=usd(totalValue))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():

    if request.method == "POST":
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("Enter stock symbol!")

        try:
            shares = int(request.form.get("shares"))
            if shares < 1:
                return apology("Enter valid number of shares!")
        except:
            return apology("Enter valid number of shares!")

        item = lookup(symbol)
        if not item:
            return apology("Invalid stock symbol!")

        price = shares * item["price"]
        liquid = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        liquid = liquid[0]["cash"]
        if price > liquid:
            return apology("Not enough cash!")

        uptd_cash = liquid - price
        db.execute("UPDATE users SET cash = ? WHERE id = ?", uptd_cash, session["user_id"])

        date = datetime.now()

        db.execute("CREATE TABLE IF NOT EXISTS history (transaction_id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, symbol TEXT NOT NULL, shares INTEGER NOT NULL, price NUMERIC NOT NULL, timestamp DATETIME NOT NULL, user_id NOT NULL, FOREIGN KEY (user_id) REFERENCES users(id))")
        db.execute("INSERT INTO history (user_id, symbol, shares, price, timestamp) VALUES (?, ?, ?, ?, ?)",
                   session["user_id"], symbol, shares, usd(price), date)
        flash("Bought!")
        return redirect("/")
    else:
        return render_template('buy.html')


@app.route("/history")
@login_required
def history():
    historys = db.execute("SELECT * FROM history WHERE user_id = ?", session["user_id"])

    return render_template('history.html', historys=historys)


@app.route("/login", methods=["GET", "POST"])
def login():

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password")

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    if request.method == "POST":
        symbol = request.form.get("symbol")

        if not symbol:
            return apology("Enter stock symbol!")

        item = lookup(symbol)

        if not item:
            return apology("Invalid stock symbol!")

        return render_template('quoted.html', stock=item["symbol"], cost=usd(item["price"]))

    else:
        return render_template('quote.html')


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":
        username = request.form.get("username")

        if not username:
            return apology("must provide username")

        # Ensure username has not been used already
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )
        if len(rows) != 0:
            return apology("username already in use")

        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        if not password or not confirmation:
            return apology("must provide password")

        if password != confirmation:
            return apology("passwords must match")

        password = generate_password_hash(password)
        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, password)
        return redirect("/")
    else:
        return render_template("register.html")


@app.route("/addCash", methods=["GET", "POST"])
@login_required
def addCash():
    if request.method == "POST":

        # number form only takes ints anyway
        amount = float(request.form.get("amount"))
        if amount < 0:
            return apology("Amount must be more than $0!")

        liquid = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        liquid = liquid[0]["cash"] + amount
        db.execute("UPDATE users SET cash = ? WHERE id = ?", liquid, session["user_id"])

        flash("Added!")
        return redirect("/")

    else:
        return render_template('addCash.html')


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():

    if request.method == "POST":
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("must provide stock name")

        shares = int(request.form.get("shares"))
        if shares < 1:
            return apology("must sell at least one stock")

        item = lookup(symbol)
        price = item["price"]

        ownedStocks = db.execute(
            "SELECT symbol as symbol, SUM(shares) as shares FROM history WHERE user_id = ? GROUP BY symbol ", session["user_id"])
        for ownedStock in ownedStocks:
            if ownedStock["symbol"] == symbol:
                 sharesOwned = ownedStock["shares"]

        if shares > sharesOwned:
            return apology("Too many shares")

        date = datetime.now()

        liquid = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        liquid = liquid[0]["cash"]
        liquid += (price * shares)
        db.execute("UPDATE users SET cash = ? WHERE id = ?", liquid, session["user_id"])

        db.execute("INSERT INTO history (user_id, symbol, shares, price, timestamp) VALUES (?, ?, ?, ?, ?)",
                   session["user_id"], symbol, -shares, usd(price), date)
        flash("Sold!")
        return redirect("/")

    else:
        stocksOwned = []
        ownedStocks = db.execute(
            "SELECT symbol as symbol, SUM(shares) as shares FROM history WHERE user_id = ? GROUP BY symbol ", session["user_id"])

        for ownedStock in ownedStocks:
            if ownedStock["shares"] > 0:
                stocksOwned.append(ownedStock["symbol"])
        return render_template('sell.html', stocks=stocksOwned)

