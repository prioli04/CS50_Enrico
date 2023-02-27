import sqlite3
import csv

conn = sqlite3.connect("roster.db")
c = conn.cursor()

with open("students.csv") as students:
    reader = csv.DictReader(students)
    rows = [row for row in reader]

with open("schema.sql") as schema:
    script_schema = schema.read()

c.executescript(script_schema)

for row in rows:
    c.execute("INSERT INTO students VALUES (?, ?);", (row["id"], row["student_name"]))
    c.execute("INSERT INTO houses (house_name, head_name) VALUES (?, ?);", (row["house"], row["head"]))

    c.execute("SELECT id FROM houses WHERE house_name = ?;", (row["house"],))
    c.execute("INSERT INTO assingments VALUES (?, ?);", (row["id"], c.fetchone()[0]))

conn.commit()

with open("student_info.sql") as info:
    info_sql = info.read()

c.execute(info_sql)
[print(row) for row in c.fetchall()]
conn.close()

