# Office Management Database System

This project implements a simple office management database system using file handling in C. The system allows users to perform various operations such as user registration, updating user information, recording work transactions, viewing user details, removing users, and viewing the office portal directory.

## Features

- **User Registration:** Adds a new user to the system with details like registration date, name, date of birth, age, address, contact, position, and salary. The user information is stored in a file (`officedata.txt`) and a formatted version in another file (`formattedData.txt`).
- **Update User Information:** Allows users to update contact information, position, or salary of an existing user.
- **Work Transactions:** Records work transactions including project details, date, and hours worked by a user. Transaction details are stored in a separate file (`officeTransactions.txt`).
- **User Details:** Fetches user details based on either username or user ID, displaying information such as registration date, date of birth, age, address, contact, position, and salary.
- **Remove User:** Deletes a user from the system, updating both the main user data file and the formatted version.
- **View Office Portal Directory:** Displays a list of all users in the database along with some of their personal information, including user ID, username, age, and position.

# SQL-like SELECT Command Simulator in C

This program, `select.c`, simulates SQL's SELECT commands in a C environment. It allows users to query data from a specified table with various conditions and attributes, providing a versatile way to retrieve information. This uses command-line interface and takes arguments directly from the terminal.

## Usage

```bash
./select "SELECT [* <OR> {attributes separated by ,}] from <table_name>.txt"


## Tech Stack

- Language: C
- Data Storage: File Handling

## How to Run

1. Clone the repository.
2. Compile the code using a C compiler.
3. Run the executable.

## Thought Process

- The project uses a file-based approach for data storage, allowing for simplicity and easy management.
- User registration and transaction functionalities are implemented through file handling operations like reading, writing, and updating records.
- The project demonstrates basic CRUD (Create, Read, Update, Delete) operations on user data.
- The structured code with comments reflects a modular design, making it easy to understand and maintain.

