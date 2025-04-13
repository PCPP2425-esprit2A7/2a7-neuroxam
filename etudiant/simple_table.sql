-- Simple script to create only the students table
-- Connect as system/123456789 to the toust database

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

-- Create a simple students table with all the required fields
CREATE TABLE students (
    id NUMBER PRIMARY KEY,
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

-- Grant permissions (optional)
GRANT SELECT, INSERT, UPDATE, DELETE ON students TO PUBLIC; 