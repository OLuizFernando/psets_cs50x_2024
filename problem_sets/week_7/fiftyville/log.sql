-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Get the description of the crime scene
SELECT description
FROM crime_scene_reports
WHERE day = 28
AND month = 7
AND year = 2023
AND street = 'Humphrey Street';

-- Get the witnesses interviews transcript
SELECT transcript
FROM interviews
WHERE day = 28
AND month = 7
AND year
AND transcript LIKE '%bakery%';

-- Get the license plates of those who exit the bakery between 10:15am and 10:25am
SELECT license_plate
FROM bakery_security_logs
WHERE day = 28
AND month = 7
AND year = 2023
AND hour = 10
AND minute >= 15 AND minute <= 25;

-- Get information from the owners of the suspicious license plates
SELECT license_plate, name, phone_number, passport_number
FROM people
WHERE license_plate IN (
    SELECT license_plate
    FROM bakery_security_logs
    WHERE day = 28
    AND month = 7
    AND year = 2023
    AND hour = 10
    AND minute >= 15 AND minute <= 25
);

-- Get the phone calls that match with the 3rd interview transcript
SELECT caller, receiver, duration
FROM phone_calls
WHERE day = 28
AND month = 7
AND year = 2023
AND duration < 60
AND caller IN (
    SELECT phone_number
    FROM people
    WHERE license_plate IN (
        SELECT license_plate
        FROM bakery_security_logs
        WHERE day = 28
        AND month = 7
        AND year = 2023
        AND hour = 10
        AND minute >= 15 AND minute <= 25
    )
);

-- Get information from the flight that matches the one mentioned on 3rd interview transcript
SELECT id, origin_airport_id, destination_airport_id, hour, minute
FROM flights
WHERE day = 29
AND month = 7
AND year = 2023
ORDER BY hour, minute;

-- Search for the passport numbers of the suspects in the 'passengers' table of the flight
SELECT seat, passport_number
FROM passengers
WHERE passport_number IN (1695452385, 3592750733, 8294398571, 5773159633)
AND flight_id = 36;

-- Get information about the destination airport
SELECT abbreviation, full_name, city
FROM airports
WHERE id = 4;

-- Get information about the phone numbers of the possible accomplices
SELECT name, license_plate, phone_number, passport_number
FROM people
WHERE phone_number IN ('(996) 555-8899', '(892) 555-8872', '(375) 555-8161', '(717) 555-1342');

-- Get bank account information of the suspects
SELECT person_id, account_number, creation_year
FROM bank_accounts
WHERE person_id IN (398010, 560886, 686048);

-- Get suspicious ATM transactions mentioned on 2nd interview transcript
SELECT account_number, atm_location, transaction_type, amount
FROM atm_transactions
WHERE day = 28
AND month = 7
AND year = 2023
AND account_number = 49610011;
