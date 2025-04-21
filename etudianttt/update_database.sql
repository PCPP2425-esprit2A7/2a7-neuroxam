-- Drop the existing students table if it exists
DROP TABLE IF EXISTS students;

-- Create a new students table with all the required fields
CREATE TABLE students (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    family_name VARCHAR(100) NOT NULL,
    cin VARCHAR(20) NOT NULL,
    speciality VARCHAR(100) NOT NULL,
    note FLOAT DEFAULT 0,
    photo_path VARCHAR(255),
    phone_number VARCHAR(20) NOT NULL,
    email VARCHAR(100) NOT NULL,
    birth_date DATE NOT NULL,
    gender VARCHAR(20) NOT NULL
);

-- Insert sample data
INSERT INTO students (name, family_name, cin, speciality, note, phone_number, email, birth_date, gender)
VALUES 
('Mohamed', 'Ben Ali', '12345678', 'Informatique', 15.5, '55123456', 'mohamed@example.com', '2000-05-15', 'Homme'),
('Fatima', 'Zahra', '87654321', 'Mathématiques', 17.8, '55987654', 'fatima@example.com', '2001-08-22', 'Femme'),
('Ahmed', 'Karim', '11223344', 'Physique', 14.2, '55112233', 'ahmed@example.com', '1999-11-10', 'Homme'); 
--and the database name toust , username : system , password 123456789