-- Connect as system user
-- In SQL Developer, use these credentials:
-- username: system
-- password: 123456789

-- Create the students table
CREATE TABLE students (
    id NUMBER GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
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

-- Create basic indexes for better performance
CREATE INDEX idx_student_name ON students(name);
CREATE INDEX idx_student_cin ON students(cin);

COMMIT; 