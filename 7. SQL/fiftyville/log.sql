-- Keep a log of any SQL queries you execute as you solve the mystery.
.schema

-- Check crime description in Humphrey Street, got information about Interviews with 3 witnesses, all mention bakery
SELECT description FROM crime_scene_reports WHERE street='Humphrey Street' and year >= 2023;

-- Check interview transcript
SELECT name, transcript from interviews where transcript LIKE '%bakery%' and year >= 2023;

SELECT * FROM atm_transactions WHERE day = 28 and month = 7 and year = 2023 and atm_location = 'Leggett Street' and transaction_type = 'withdraw';

-- Get Eugene licenplate-transcation before 8:13
SELECT license_plate FROM bakery_security_logs WHERE year = 2023 and month = 7 and day = 28 and hour = 10 and minute > 15 and minute < 25;

-- Find phone number
SELECT phone_number from people  WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = 2023 and month
= 7 and day = 28 and hour = 10 and minute > 15 and minute < 25);
SELECT * from phone_calls WHERE duration <= 60 and caller IN (SELECT phone_number from people WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = 2023 and month
= 7 and day = 28 and hour = 10 and minute > 15 and minute < 25));

-- earliest flight in day 29
SELECT * from airports; -- id 8
SELECT * from flights WHERE origin_airport_id = 8 and day = 29 and month = 7 and year = 2023;
SELECT city from airports WHERE id = 4; -- Target city found New York City and fligth id is 36

-- Find person Name with passport_number and phone_number.
SELECT passport_number from passengers WHERE flight_id = 36;
SELECT caller from phone_calls WHERE duration <= 60 and caller IN (SELECT phone_number from people WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = 2023 and month
= 7 and day = 28 and hour = 10 and minute > 15 and minute < 25));

SELECT name from people WHERE phone_number IN
(SELECT caller from phone_calls WHERE duration <= 60 and caller
 IN (SELECT phone_number from people WHERE license_plate
 IN (SELECT license_plate FROM bakery_security_logs WHERE year = 2023 and month = 7 and day = 28 and hour = 10 and minute > 15 and minute < 25)))
AND
passport_number IN (SELECT passport_number from passengers WHERE flight_id = 36)
AND
id IN (SELECT person_id FROM bank_accounts WHERE account_number
 IN (SELECT account_number FROM atm_transactions WHERE day = 28 and month = 7 and year = 2023 and atm_location = 'Leggett Street' and transaction_type = 'withdraw'));

-- By nesting all information we got into one Query the thief is Bruce, But who helped?.
SELECT phone_number FROM people WHERE name = 'Bruce';

-- Bruce phone (367) 555-5533
SELECT * FROM phone_calls WHERE duration <= 60 and caller = '(367) 555-5533';

-- Accomplice phone number: (375) 555-8161
-- By checking the number's name we get the accomplece and complete the exercise
SELECT name FROM people WHERE phone_number='(375) 555-8161';

-- The accomplice is Robin.
