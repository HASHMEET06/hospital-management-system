# Hospital Management System

A menu-driven Hospital Management System developed in **C**. The program
lets a user manage basic patient records through a console interface and
stores records in a local binary file.

## Features

-   Add a new patient record
-   View all patient records
-   Search for a patient using Patient ID
-   Update patient details
-   Delete a patient record
-   Generate a basic hospital bill
-   Save and load patient records automatically

## Technologies Used

-   Programming language: C
-   Standard C libraries: `stdio.h`, `stdlib.h`, and `string.h`
-   IDE used: Dev-C++

## Project Files

-   `hospital_management.c` --- main C source code
-   `patients.dat` --- data file created automatically when the program
    saves patient records (it may not exist until the program is run)

## How to Run in Dev-C++

1.  Download or clone this repository.
2.  Open Dev-C++.
3.  Select **File → Open** and open `hospital_management.c`.
4.  Select **Execute → Compile & Run** (or press `F11`, depending on
    your Dev-C++ setup).
5.  Follow the menu shown in the console and enter the number for the
    operation you want.

## Menu Options

  Option   Operation
  -------- -------------------
  1        Add Patient
  2        View All Patients
  3        Search Patient
  4        Update Patient
  5        Delete Patient
  6        Generate Bill
  0        Exit

## How Data Is Stored

Patient records are saved in `patients.dat` in the program's working
directory. The program loads this file when it starts and saves changes
after adding, updating, or deleting records.

**Note:** `patients.dat` is a local binary data file. Do not upload real
or confidential patient information to a public GitHub repository. Use
fictional/sample data for demonstrations.

## Limitations

This is a basic educational project. It does not provide user login,
encryption, network access, or a production-ready medical record system.
The generated bill is a basic project bill, not a tax invoice.

## Author

Add your name here.

## License

This project is shared for educational purposes. Add a license if you
want to specify permissions for reuse.
