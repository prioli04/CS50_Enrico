-- Keep a log of any SQL queries you execute as you solve the mystery.
-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Using the date and street of the crime to find its description
SELECT description
  FROM crime_scene_reports
 WHERE year = 2021 AND
       month = 7 AND
       day = 28 AND
       street = "Humphrey Street";
-- Key information obtained: took place at 10:15am at the Humphery Street Bakery. Three interviews conducted.

-- Searching the interviews table for the transcripts
SELECT name, transcript
  FROM interviews
 WHERE year = 2021 AND
       month = 7 AND
       day = 28;
-- Key information obtained:

-- Raymond - "thief leaving the bakery, called someone, talked for less than a minute.
-- thief planning to take the earliest flight out of Fiftyville tomorrow.
-- thief asked person on the other end to purchase the flight ticket."

-- Eugene - "ATM on Leggett Street and saw the thief there withdrawing some money."

-- Ruth - "within ten minutes of the theft, thief get into a car in the bakery parking lot.
-- security footage from bakery parking lot"

-- Searching the bakery security logs
SELECT activity, license_plate
  FROM bakery_security_logs
 WHERE year = 2021 AND
       month = 7 AND
       day = 28 AND
       hour = 10 AND
       minute BETWEEN 15 AND 25;

-- Key information obtained:
-- License Plates of exiting vehicles:
-- 5P2BI95
-- 94KL13X
-- 6P58WS2
-- 4328GD8
-- G412CB7
-- L93JTIZ
-- 322W7JE
-- 0NTHK55

-- Obtaining information about the owners of the license plates
SELECT license_plate, name, phone_number, passport_number
  FROM people
 WHERE license_plate IN (SELECT license_plate
                           FROM bakery_security_logs
                          WHERE year = 2021 AND
                                month = 7 AND
                                day = 28 AND
                                hour = 10 AND
                                activity = "exit" AND
                                minute BETWEEN 15 AND 25);

-- Key information obtained:
--+---------------+---------+----------------+-----------------+
--| license_plate |  name   |  phone_number  | passport_number |
--+---------------+---------+----------------+-----------------+
--| 5P2BI95       | Vanessa | (725) 555-4692 | 2963008352      |
--| 6P58WS2       | Barry   | (301) 555-4174 | 7526138472      |
--| L93JTIZ       | Iman    | (829) 555-5269 | 7049073643      |
--| G412CB7       | Sofia   | (130) 555-0289 | 1695452385      |
--| 4328GD8       | Luca    | (389) 555-5198 | 8496433585      |
--| 322W7JE       | Diana   | (770) 555-1861 | 3592750733      |
--| 0NTHK55       | Kelsey  | (499) 555-9472 | 8294398571      |
--| 94KL13X       | Bruce   | (367) 555-5533 | 5773159633      |

-- Who withdrew money from the ATM that morning
SELECT p.name
  FROM people AS p
       JOIN bank_accounts AS b
       ON p.id = b.person_id
       JOIN atm_transactions AS a
       ON b.account_number = a.account_number
 WHERE a.year = 2021 AND
       a.month = 7 AND
       a.day = 28 AND
       atm_location = "Leggett Street";

-- Key information obtained:
--| Bruce   |
--| Kaelyn  |
--| Diana   |
--| Brooke  |
--| Kenny   |
--| Iman    |
--| Luca    |
--| Taylor  |
--| Benista |

-- Possible suspects
-- (exited the bakery's parking lot within 10 minutes of the theft and withdrew money from Leggett Street ATM that day)
-- Bruce, Iman, Luca and Diana

-- Searching the phone-call records for calls with less than 1 minute duration that day, from those four suspects
SELECT P1.name AS "Caller Name", ph.caller, ph.receiver, P2.name AS "Receiver Name"
  FROM phone_calls AS ph
       JOIN people AS P1
       ON P1.phone_number = ph.caller
       JOIN people AS P2
       ON P2.phone_number = ph.receiver
 WHERE ph.year = 2021 AND
       ph.month = 7 AND
       ph.day = 28 AND
       ph.duration <= 60 AND
       ph.caller IN (SELECT L.phone_number
                    FROM (SELECT p.name
                            FROM people AS p
                                 JOIN bank_accounts AS b
                                 ON p.id = b.person_id
                                 JOIN atm_transactions AS a
                                 ON b.account_number = a.account_number
                           WHERE a.year = 2021 AND
                                 a.month = 7 AND
                                 a.day = 28 AND
                                atm_location = "Leggett Street") AS A
                          JOIN (SELECT name, phone_number
                                  FROM people
                                 WHERE license_plate IN (SELECT license_plate
                                                           FROM bakery_security_logs
                                                          WHERE year = 2021 AND
                                                                month = 7 AND
                                                                day = 28 AND
                                                                hour = 10 AND
                                                                activity = "exit" AND
                                                                minute BETWEEN 15 AND 25)) AS L
                            ON A.name = L.name);

-- Key information obtained:
--+-------------+----------------+----------------+---------------+
--| Caller Name |     caller     |    receiver    | Receiver Name |
--+-------------+----------------+----------------+---------------+
--| Bruce       | (367) 555-5533 | (375) 555-8161 | Robin         |
--| Diana       | (770) 555-1861 | (725) 555-3243 | Philip        |
--+-------------+----------------+----------------+---------------+
-- Possible Thief-Accomplice pairs:
-- Bruce-Robin
-- Diana-Philip

-- Earliest flight out of Fiftyville on July 29th 2021
SELECT a.city
  FROM flights AS f
       JOIN airports AS a
       ON a.id = f.destination_airport_id
 WHERE f.year = 2021 AND
       f.month = 7 AND
       f.day = 29 AND
       f.origin_airport_id = (SELECT id
                                FROM airports
                               WHERE city = "Fiftyville")
 ORDER BY f.hour, f.minute LIMIT 1;

 -- Key information obtained:
 -- Earliest flight leaving Fiftyville on July 29th 2021 has New York City as its destination.
 -- So, the thief escaped to New York City

 -- Passengers of the flight to New York City
 SELECT pe.name
   FROM people AS pe
        JOIN passengers AS pa
        ON pe.passport_number = pa.passport_number
        JOIN flights AS f
        ON pa.flight_id = f.id
 WHERE f.id = (SELECT f.id
                 FROM flights AS f
                      JOIN airports AS a
                      ON a.id = f.destination_airport_id
                WHERE f.year = 2021 AND
                      f.month = 7 AND
                      f.day = 29 AND
                      f.origin_airport_id = (SELECT id
                                               FROM airports
                                              WHERE city = "Fiftyville")
                ORDER BY f.hour, f.minute LIMIT 1);

 -- Key information obtained:
--| Kenny  |
--| Sofia  |
--| Taylor |
--| Luca   |
--| Kelsey |
--| Edward |
--| Bruce  |
--| Doris  |
-- Bruce is a passenger of that flight. So he is the thief and Robin the accomplice
