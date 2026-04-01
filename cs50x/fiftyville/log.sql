-- Keep a log of any SQL queries you execute as you solve the mystery.
-- Theft took place on July 28, 2025
-- Theft took place on Humphrey Street

-- Look for crime scene report
SELECT * FROM crime_scene_reports
WHERE year = 2025
AND month = 7
AND day = 28;
-- Two reports, one for the CS50 duck theft at 10:15am at the bakery; three witnesses; ID = 295
-- Other is for littering at 16:36 (4:36pm); no witnesses; ID = 297

-- Look at interviews for the three witnesses
SELECT * FROM interviews
WHERE year = 2025
AND month = 7
AND day = 28;
-- ID 161; Ruth; Theft + 10 mins theft drove away in a car
-- ID 162; Eugene; recognized theif but doesn't remember name; theif withdrawing money from ATM on Leggett St
-- ID 163; Raymond; theif made sub-minute phone call to take earliest flight out of Fiftyville on 7/29/25; person on phone purchased the flight

-- Look for cars on security footage for 7/28/25 between 10:10am and 10:35am
SELECT * FROM bakery_security_logs
WHERE year = 2025
AND month = 7
AND day = 28
AND hour = 10
AND minute BETWEEN 10 AND 35;
-- One car entered at 10:14am with license_plate 13FNH73
-- 9 cars exited between 10:16am and 10:35am with license plates (xxx)

-- See if one of the 9 cars leaving also entered in the 30 mins prior to the theft
SELECT * FROM bakery_security_logs
WHERE license_plate IN (
    SELECT license_plate FROM bakery_security_logs
    WHERE year = 2025
    AND month = 7
    AND day = 28
    AND hour = 10
    AND minute BETWEEN 16 AND 35
    AND activity = 'exit'
) AND activity = 'entrance'
AND year = 2025
AND month = 7
AND day = 28;
-- All 9 of them entered the parking lot between 8:18am and 9:28am

-- using the 9 license plates, attach them to people and then passengers on flights leaving Fiftyville on 7/29/25
SELECT * FROM passengers
WHERE flight_id IN (
    SELECT id FROM flights
    WHERE origin_airport_id = (
        SELECT id FROM airports
        WHERE city = 'Fiftyville'
    ) AND year = 2025
    AND month = 7
    AND day = 29
) AND passport_number IN (
    SELECT passport_number FROM people
    WHERE license_plate IN (
        SELECT license_plate FROM bakery_security_logs
        WHERE year = 2025
        AND month = 7
        AND day = 28
        AND hour = 10
        AND minute BETWEEN 16 AND 35
        AND activity = 'exit'
    )
);
-- Came back with 6 people on two possible flights; 1 on Flight 18 and 5 on Flight 36

-- Phone call gave it was the earliest so figure out which one was at which time
SELECT * FROM flights
WHERE origin_airport_id = (
    SELECT id FROM airports
    WHERE city = 'Fiftyville'
) AND year = 2025
AND month = 7
AND day = 29
ORDER BY hour, minute;
-- Flight 36 is at 8:20am and Flight 18 is at 16:00 (4:00pm)
-- Going to assume we want Flight 36

-- Look for phone calls made on 7/28/25 that are less than a minute long (going to assume duration is in seconds)
SELECT * FROM phone_calls
WHERE year = 2025
AND month = 7
AND day = 28
AND duration <= 60;
-- Came back with 10 calls

-- Maybe cross reference caller with phone number of people with the same license_plate or passport_number
-- Phone number is for the caller of a 60 second or less on day of theft
-- License plate is for the vehicles exiting 20 minutes following theft
-- passport number is for people on the earliest flight on 7/29/25
SELECT * FROM people
WHERE phone_number IN (
    SELECT caller FROM phone_calls
    WHERE year = 2025
    AND month = 7
    AND day = 28
    AND duration <= 60
) AND license_plate IN (
    SELECT license_plate FROM bakery_security_logs
    WHERE year = 2025
    AND month = 7
    AND day = 28
    AND hour = 10
    AND minute BETWEEN 16 AND 35
    AND activity = 'exit'
) AND passport_number IN (
    SELECT passport_number FROM passengers
    WHERE flight_id = (
        SELECT id FROM flights
        WHERE origin_airport_id = (
            SELECT id FROM airports
            WHERE city = 'Fiftyville'
        ) AND year = 2025
        AND month = 7
        AND day = 29
        ORDER BY hour, minute
        LIMIT 1
    )
);
-- This has narrowed it down to Sofie, Taylor, Kelsey and Bruce

-- Look at the ATM logs for Leggett St
SELECT * FROM atm_transactions
WHERE year = 2025
AND month = 7
AND day = 28
AND atm_location LIKE 'Leggett%'
AND transaction_type = 'withdraw';
-- 8 withdraws that day

-- Look at account number and person id
-- This will be the people who withdrew money on Leggett St on 7/28/25
SELECT * FROM people
WHERE id IN (
    SELECT person_id FROM bank_accounts
    WHERE account_number IN (
        SELECT account_number FROM atm_transactions
        WHERE year = 2025
        AND month = 7
        AND day = 28
        AND atm_location LIKE 'Leggett%'
        AND transaction_type = 'withdraw'
    )
);
-- Got the 8 names and see some overlap

-- Combine with the above query starting on line 96
SELECT * FROM people
WHERE phone_number IN (
    SELECT caller FROM phone_calls
    WHERE year = 2025
    AND month = 7
    AND day = 28
    AND duration <= 60
) AND license_plate IN (
    SELECT license_plate FROM bakery_security_logs
    WHERE year = 2025
    AND month = 7
    AND day = 28
    AND hour = 10
    AND minute BETWEEN 16 AND 35
    AND activity = 'exit'
) AND passport_number IN (
    SELECT passport_number FROM passengers
    WHERE flight_id = (
        SELECT id FROM flights
        WHERE origin_airport_id = (
            SELECT id FROM airports
            WHERE city = 'Fiftyville'
        ) AND year = 2025
        AND month = 7
        AND day = 29
        ORDER BY hour, minute
        LIMIT 1
    )
) AND id IN (
    SELECT person_id FROM bank_accounts
    WHERE account_number IN (
        SELECT account_number FROM atm_transactions
        WHERE year = 2025
        AND month = 7
        AND day = 28
        AND atm_location LIKE 'Leggett%'
        AND transaction_type = 'withdraw'
    )
);
-- Narrowed down to Taylor and Bruce
-- So guess is that one is the theif and one is the co-consipirator

-- Dropping the extra ten minutes off the security footage
SELECT * FROM people
WHERE phone_number IN (
    SELECT caller FROM phone_calls
    WHERE year = 2025
    AND month = 7
    AND day = 28
    AND duration <= 60
) AND license_plate IN (
    SELECT license_plate FROM bakery_security_logs
    WHERE year = 2025
    AND month = 7
    AND day = 28
    AND hour = 10
    AND minute BETWEEN 16 AND 25
    AND activity = 'exit'
) AND passport_number IN (
    SELECT passport_number FROM passengers
    WHERE flight_id = (
        SELECT id FROM flights
        WHERE origin_airport_id = (
            SELECT id FROM airports
            WHERE city = 'Fiftyville'
        ) AND year = 2025
        AND month = 7
        AND day = 29
        ORDER BY hour, minute
        LIMIT 1
    )
) AND id IN (
    SELECT person_id FROM bank_accounts
    WHERE account_number IN (
        SELECT account_number FROM atm_transactions
        WHERE year = 2025
        AND month = 7
        AND day = 28
        AND atm_location LIKE 'Leggett%'
        AND transaction_type = 'withdraw'
    )
);
-- This leaves just Bruce

-- See who Bruce was calling for the co-consipirator
SELECT * FROM people
WHERE phone_number IN (
    SELECT receiver FROM phone_calls
    WHERE caller IN (
        SELECT phone_number FROM people
        WHERE name = 'Bruce'
    ) AND year = 2025
    AND month = 7
    AND day = 28
    AND duration <= 60
);
-- Got Robin back
-- Going to assume that Robin is the co-conspirator

-- Now need to find where Bruce was going on his flight
SELECT city FROM airports
WHERE id = (
    SELECT destination_airport_id FROM flights
    WHERE id = (
        SELECT flight_id FROM passengers
        WHERE passport_number = (
            SELECT passport_number FROM people
            WHERE name = 'Bruce'
        )
    )
);
-- Got New York City

-- Final Answers:
-- Bruce stole the CS50 duck with the help of Robin and fled to New York City
