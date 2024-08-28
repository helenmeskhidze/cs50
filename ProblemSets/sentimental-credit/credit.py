import math


def get_int(prompt):
    while True:
        try:
            return int(input(prompt))
        except ValueError:
            pass


def main():
    inputNumber = str(get_int("Number: "))

    if checksum(inputNumber):
        if len(inputNumber) == 15 and int(inputNumber[0:2]) in [34, 37]:
            print("AMEX")
        elif len(inputNumber) == 16 and (int(inputNumber[0:2]) in [51, 52, 53, 54, 55]):
            print("MASTERCARD")
        elif (len(inputNumber) == 13 or len(inputNumber) == 16) and int(inputNumber[0:1]) == 4:
            print("VISA")
        else:
            print("INVALID")
    else:
        print("INVALID")


def checksum(inputNumber):
    sum = 0
    inputNumberlen = len(inputNumber)
    parity = inputNumberlen % 2

    for i in range(inputNumberlen):
        if i % 2 != parity:
            sum += int(inputNumber[i])
        elif int(inputNumber[i]) > 4:
            sum += 2 * int(inputNumber[i]) - 9
        else:
            sum += 2 * int(inputNumber[i])

    if sum % 10 == 0:
        return True


main()
