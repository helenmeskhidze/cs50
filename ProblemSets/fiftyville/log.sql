-- Keep a log of any SQL queries you execute as you solve the mystery.

SELECT * from bakery_security_logs WHERE month ="7" AND year="2023" AND day ="28" and hour = "10" AND minute > 15 AND minute <25;
SELECT license_plate FROM bakery_security_logs WHERE month ="7" AND year="2023" AND day ="28" and hour = "10" AND minute > 15 AND minute <25;
SELECT * FROM atm_transactions WHERE month="7" AND day="28" AND year = "2023" AND atm_location = "Leggett Street" AND transaction_type = "withdraw";
SELECT license_plate FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE month="7" AND day="28" AND year = "2023" AND atm_location = "Leggett Street" AND transaction_type = "withdraw")) AND license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE month ="7" AND year="2023" AND day ="28" and hour = "10" AND minute > 15 AND minute <25);
SELECT caller FROM phone_calls WHERE month="7" AND day="28" AND year = "2023" AND duration < 60;
SELECT * FROM passengers
WHERE flight_id = (SELECT id FROM flights WHERE month="7" AND day="29" AND year = "2023" AND origin_airport_id  = (SELECT id FROM airports WHERE city="Fiftyville") ORDER BY hour ASC Limit 1) AND passport_number IN (SELECT passport_number from people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE month="7" AND day="28" AND year = "2023" AND duration < 60) AND license_plate IN (SELECT license_plate FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE month="7" AND day="28" AND year = "2023" AND atm_location = "Leggett Street" AND transaction_type = "withdraw")) AND license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE month ="7" AND year="2023" AND day ="28" and hour = "10" AND minute > 15 AND minute <25)));
SELECT * FROM people WHERE passport_number="5773159633";
SELECT * from phone_calls WHERE caller="(367) 555-5533" AND duration<60;
SELECT * FROM people WHERE phone_number="(375) 555-8161";
