DROP TABLE IF EXISTS students;
DROP TABLE IF EXISTS assingments;
DROP TABLE IF EXISTS houses;

CREATE TABLE students (
    id INTEGER NOT NULL,
    student_name TEXT NOT NULL,
    PRIMARY KEY(id)
);

CREATE TABLE houses (
    id INTEGER NOT NULL,
    house_name TEXT NOT NULL,
    head_name TEXT NOT NULL,
    PRIMARY KEY(id)
);

CREATE TABLE assingments (
    student_id INTEGER NOT NULL,
    house_id INTEGER NOT NULL,
    FOREIGN KEY(student_id) REFERENCES student(id)
    FOREIGN KEY(house_id) REFERENCES houses(id)
);