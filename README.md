
# 🎓 Student Management & Academic Performance System

A menu-driven Student Management System developed using **C Programming (C11)**. This project helps manage student information, academic records, marks, grades, and performance statistics through a command-line interface.

The project demonstrates fundamental and advanced C programming concepts, including pointers, structures, recursion, dynamic memory allocation, arrays, and file handling.

---

## 🚀 Features

- **Add Student:** Register new students with their name, UID, contact details, and subject marks.
- **Display Records:** View complete student information and academic performance.
- **Search Student:** Search records using student UID or name.
- **Update Marks:** Modify existing academic records.
- **Delete Student:** Remove student records.
- **Sort Students:** Rank students according to their percentage.
- **Class Statistics:** Calculate class average, highest score, lowest score, and pass percentage.
- **Grade Calculation:** Automatically assign grades based on academic performance.
- **File Handling:** Save and retrieve student records permanently.
- **Export Reports:** Generate readable academic reports in a text file.
- **Dynamic Memory Management:** Expand memory capacity as new students are added.

---

## 🛠️ Technologies Used

| Technology | Purpose |
|---|---|
| C Programming (C11) | Core development |
| GCC Compiler | Compilation |
| VS Code | Development environment |
| Standard C Libraries | Input, output, memory and string operations |

### Libraries Used

- `stdio.h` – Input/output and file handling
- `stdlib.h` – Dynamic memory allocation and conversion
- `string.h` – String manipulation and comparison

---

## 📚 C Programming Concepts Implemented

This project combines multiple C programming concepts:

1. Variables and Data Types
2. Operators and Expressions
3. Conditional Statements
4. Loops and Nested Loops
5. One-Dimensional Arrays
6. Two-Dimensional Arrays
7. String Manipulation
8. User-Defined Functions
9. Pointers and Pointer to Pointer
10. Recursion
11. Structures and Nested Structures
12. Unions
13. Dynamic Memory Allocation
14. `malloc()`, `calloc()`, `realloc()` and `free()`
15. Searching and Sorting Algorithms
16. File Handling (`fopen`, `fread`, `fwrite`, `fprintf`)
17. Bitwise Operators
18. Preprocessor Directives and Macros

---

## 💻 Installation and Execution

### Prerequisites

- GCC Compiler
- Visual Studio Code (recommended)
- Windows, Linux or another GCC-supported environment

### Step 1: Clone the Repository

```bash
git clone https://github.com/MehraabSinghVirk/Student-Management-System-C.git
```

### Step 2: Navigate to the Project

```bash
cd Student-Management-System-C
```

### Step 3: Compile the Program

```bash
gcc student_management.c -o student_management -std=c11
```

### Step 4: Run the Program

**Windows:**

```bash
student_management.exe
```

**Linux:**

```bash
./student_management
```

---

## 📋 Application Menu

```text
====================================
    STUDENT MANAGEMENT SYSTEM
====================================

1. Add Student
2. Display All Students
3. Search Student
4. Update Student Marks
5. Delete Student
6. Sort Students
7. Class Statistics
8. Export Text Report
9. Save Records
0. Save and Exit

====================================
Enter your choice:
```

---

## 📂 Project Structure

```text
Student-Management-System-C/
│
├── student_management.c
│
├── README.md
│
├── .gitignore
│
├── students.dat
│
└── student_report.txt
```

**Generated files:**

- `students.dat` – Stores student records in binary format.
- `student_report.txt` – Contains exported academic reports.

These files are generated automatically when the application is used.

---

## 📊 Grading System

| Percentage | Grade |
|---|---|
| 90–100% | A |
| 80–89% | B |
| 70–79% | C |
| 60–69% | D |
| 50–59% | E |
| Below 50% | F |

---

## 🔮 Future Improvements

- Graphical User Interface (GUI)
- Student attendance management
- Subject-wise performance analysis
- Login and authentication system
- Database integration using MySQL
- Advanced academic analytics
- Web-based student dashboard

---

## 👨‍💻 Developer

**Mehraab Singh Virk**

Computer Science Engineering (AI)

---

## 🎯 Project Objective

The primary objective of this project is to apply C programming concepts to develop a practical application that manages student information and academic performance while demonstrating problem-solving, logical thinking, memory management, and programming skills.

---

⭐ If you find this project useful, consider giving the repository a star!
