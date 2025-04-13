-- Note: This script should be run while connected to the 'toust' database
-- using the 'system' user with password '123456789'
-- Example connection: sqlplus system/123456789@//localhost:1521/toust @oracle_database.sql

-- Create a sequence for generating student IDs
CREATE SEQUENCE student_seq
    START WITH 1
    INCREMENT BY 1
    NOCACHE
    NOCYCLE;

-- Drop the existing students table if it exists
BEGIN
   EXECUTE IMMEDIATE 'DROP TABLE students';
EXCEPTION
   WHEN OTHERS THEN
      IF SQLCODE != -942 THEN
         RAISE;
      END IF;
END;
/

-- Create a new students table with all the required fields
CREATE TABLE students (
    id NUMBER DEFAULT student_seq.NEXTVAL PRIMARY KEY,
    name VARCHAR2(100) NOT NULL,
    family_name VARCHAR2(100) NOT NULL,
    cin VARCHAR2(20) NOT NULL,
    speciality VARCHAR2(100) NOT NULL,
    note NUMBER(5,2) DEFAULT 0,
    photo_path VARCHAR2(255),
    phone_number VARCHAR2(20) NOT NULL,
    email VARCHAR2(100) NOT NULL,
    birth_date DATE NOT NULL,
    gender VARCHAR2(20) NOT NULL
);

-- Create index on commonly searched fields
CREATE INDEX idx_student_name ON students(name);
CREATE INDEX idx_student_cin ON students(cin);
CREATE INDEX idx_student_speciality ON students(speciality);

-- Insert sample data
INSERT INTO students (name, family_name, cin, speciality, note, phone_number, email, birth_date, gender)
VALUES ('Mohamed', 'Ben Ali', '12345678', 'Informatique', 15.5, '55123456', 'mohamed@example.com', TO_DATE('2000-05-15', 'YYYY-MM-DD'), 'Homme');

INSERT INTO students (name, family_name, cin, speciality, note, phone_number, email, birth_date, gender)
VALUES ('Fatima', 'Zahra', '87654321', 'Mathématiques', 17.8, '55987654', 'fatima@example.com', TO_DATE('2001-08-22', 'YYYY-MM-DD'), 'Femme');

INSERT INTO students (name, family_name, cin, speciality, note, phone_number, email, birth_date, gender)
VALUES ('Ahmed', 'Karim', '11223344', 'Physique', 14.2, '55112233', 'ahmed@example.com', TO_DATE('1999-11-10', 'YYYY-MM-DD'), 'Homme');

COMMIT;

-- Create a trigger to automatically set the ID when inserting a new student
CREATE OR REPLACE TRIGGER trg_students_id
BEFORE INSERT ON students
FOR EACH ROW
BEGIN
    IF :NEW.id IS NULL THEN
        SELECT student_seq.NEXTVAL INTO :NEW.id FROM dual;
    END IF;
END;
/ 