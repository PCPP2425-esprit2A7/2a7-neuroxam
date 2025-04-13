# Student Management System

This is a Qt-based student management system that allows you to manage student information, including personal details, academic information, and photos.

## Features

- Add, update, and delete student records
- Search and filter students by various criteria
- Sort students by different fields
- Generate statistics about students
- Export student data to PDF (individual or all students)
- Upload and store student photos

## Requirements

- Qt 5.12 or higher
- Qt Modules: Core, GUI, SQL, Charts, PrintSupport, Widgets
- Oracle Database (or MySQL with configuration change)
- Oracle Instant Client (for Oracle connection)

## Database Setup (Oracle)

1. Install Oracle Database or use an existing installation
2. Connect as the system user with the password 123456789
3. Make sure you have a database named 'toust' 
4. Run the oracle_database.sql script to create the necessary tables and sample data:
   ```
   sqlplus system/123456789@//localhost:1521/toust @oracle_database.sql
   ```

4. Verify tables are created:
   ```sql
   SELECT table_name FROM user_tables WHERE table_name = 'STUDENTS';
   ```

## Database Setup (MySQL Alternative)

If you prefer using MySQL instead of Oracle:

1. Modify connection.cpp to use QMYSQL driver instead of QOCI
2. Create a database named `studentdb`:
   ```sql
   CREATE DATABASE studentdb;
   ```
3. Run the update_database.sql script:
   ```
   mysql -u root -p studentdb < update_database.sql
   ```

## Application Configuration

The application is configured to connect to Oracle with:
- Database: toust
- Username: system
- Password: 123456789
- Host: localhost
- Port: 1521

If you need to change these settings, edit the connection.cpp file.

## Building the Application

1. Make sure Oracle Instant Client is installed (for Oracle connection)
2. Make sure the Qt SQL drivers for your database are installed
3. Open the project in Qt Creator
4. Configure the project with the appropriate kit
5. Build the project

## Usage

1. Launch the application
2. The interface is divided into two main sections:
   - Left: Form for adding/editing student information
   - Right: Table displaying student records and actions

### Adding a Student

1. Fill in all required fields in the form
2. Click on "Browse" to upload a photo (optional)
3. Click "Add" to add the student to the database

### Editing a Student

1. Select a student from the table
2. Update the information in the form
3. Click "Update" to save changes

### Deleting a Student

1. Select a student from the table
2. Click "Delete" to remove the student from the database

### Searching and Sorting

- Use the search field to filter students by name, CIN, speciality, etc.
- Use the sort dropdown to order students by different criteria

### Statistics and Reports

- Click "Statistics" to view charts showing student distribution by speciality, etc.
- Click "Export PDF" to generate a PDF with all student records
- Click "Student PDF" to generate a detailed PDF for the selected student

## Troubleshooting

- If you encounter Oracle connection issues:
  - Ensure Oracle Instant Client is properly installed
  - Verify your database name is 'toust'
  - Verify the system account password is '123456789'
  - Check that OCI libraries are in your system PATH
  - Make sure the QOCI driver is available in your Qt installation

- For the "No rule to make target '../../map.qml'" error:
  - This was fixed by removing the reference to map.qml in the resources.qrc file
  - If you still see this error, make sure you're using the updated resources.qrc file

## License

This project is released under the MIT License. 