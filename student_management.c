
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUBJECTS 5
#define MAX_NAME 50
#define MAX_UID 20
#define DATA_FILE "students.dat"

#define ACTIVE 1u
#define SCHOLARSHIP 2u

// Personal Information
typedef struct
{
    char name[MAX_NAME];
    char uid[MAX_UID];

    int contactType;

    union
    {
        char phone[20];
        char email[50];
    } contact;

} PersonalInfo;


// Academic Information
typedef struct
{
    int marks[SUBJECTS];

} AcademicInfo;


// Student Structure
typedef struct
{
    PersonalInfo personal;
    AcademicInfo academic;
    unsigned int flags;

} Student;


// Function declarations
void readLine(char message[], char text[], int size);
int readInt(char message[], int min, int max);

int calculateTotal(int marks[], int n);
float calculatePercentage(int marks[]);
char calculateGrade(float percentage);

int findStudent(Student students[], int count, char uid[]);

void addStudent(Student **students, int *count, int *capacity);
void displayOne(Student *s);
void displayStudents(Student students[], int count);
void searchStudent(Student students[], int count);
void updateStudent(Student students[], int count);
void deleteStudent(Student students[], int *count);
void sortStudents(Student students[], int count);
void classStatistics(Student students[], int count);

int saveRecords(Student students[], int count);
int loadRecords(Student **students, int *capacity);
void exportReport(Student students[], int count);


// Read string input
void readLine(char message[], char text[], int size)
{
    printf("%s", message);

    if (fgets(text, size, stdin) == NULL)
    {
        text[0] = '\0';
        return;
    }

    int len = (int)strcspn(text, "\n");

    if (text[len] == '\n')
    {
        text[len] = '\0';
    }
    else
    {
        int ch;

        while ((ch = getchar()) != '\n' && ch != EOF);
    }
}


// Read integer with validation
int readInt(char message[], int min, int max)
{
    char input[100];
    char *end;
    long value;

    while (1)
    {
        readLine(message, input, sizeof(input));

        value = strtol(input, &end, 10);

        if (end != input && *end == '\0' &&
            value >= min && value <= max)
        {
            return (int)value;
        }

        printf("Invalid input! Enter between %d and %d.\n",
               min, max);
    }
}


// Recursive total calculation
int calculateTotal(int marks[], int n)
{
    if (n == 0)
    {
        return 0;
    }

    return marks[n - 1] + calculateTotal(marks, n - 1);
}


// Calculate percentage
float calculatePercentage(int marks[])
{
    int total = calculateTotal(marks, SUBJECTS);

    return (float)total / SUBJECTS;
}


// Grade calculation
char calculateGrade(float percentage)
{
    if (percentage >= 90)
        return 'A';

    else if (percentage >= 80)
        return 'B';

    else if (percentage >= 70)
        return 'C';

    else if (percentage >= 60)
        return 'D';

    else if (percentage >= 50)
        return 'E';

    else
        return 'F';
}


// Search using UID
int findStudent(Student students[], int count, char uid[])
{
    for (int i = 0; i < count; i++)
    {
        if (strcmp(students[i].personal.uid, uid) == 0)
        {
            return i;
        }
    }

    return -1;
}


// Add student
void addStudent(Student **students, int *count, int *capacity)
{
    if (*count == *capacity)
    {
        int newCapacity = (*capacity) * 2;

        Student *temp = realloc(
            *students, newCapacity * sizeof(Student));

        if (temp == NULL)
        {
            printf("Memory allocation failed!\n");
            return;
        }

        *students = temp;
        *capacity = newCapacity;
    }

    Student s = {0};

    printf("\n===== ADD STUDENT =====\n");

    readLine("Enter name: ", s.personal.name, MAX_NAME);

    readLine("Enter UID: ", s.personal.uid, MAX_UID);

    if (strlen(s.personal.name) == 0 ||
        strlen(s.personal.uid) == 0)
    {
        printf("Name and UID cannot be empty!\n");
        return;
    }

    if (findStudent(*students, *count, s.personal.uid) != -1)
    {
        printf("UID already exists!\n");
        return;
    }

    printf("\n1. Phone Number\n");
    printf("2. Email Address\n");

    s.personal.contactType =
        readInt("Choose contact type: ", 1, 2);

    if (s.personal.contactType == 1)
    {
        readLine("Enter phone: ",
                 s.personal.contact.phone, 20);
    }
    else
    {
        readLine("Enter email: ",
                 s.personal.contact.email, 50);
    }

    printf("\nEnter marks out of 100:\n");

    for (int i = 0; i < SUBJECTS; i++)
    {
        char message[50];

        sprintf(message, "Subject %d: ", i + 1);

        s.academic.marks[i] = readInt(message, 0, 100);
    }

    s.flags |= ACTIVE;

    int scholarship = readInt(
        "Scholarship? (1=Yes, 0=No): ", 0, 1);

    if (scholarship)
    {
        s.flags |= SCHOLARSHIP;
    }

    (*students)[*count] = s;

    (*count)++;

    printf("\nStudent added successfully!\n");
}


// Display one student
void displayOne(Student *s)
{
    float percentage =
        calculatePercentage(s->academic.marks);

    printf("\n-----------------------------\n");

    printf("Name       : %s\n", s->personal.name);
    printf("UID        : %s\n", s->personal.uid);

    if (s->personal.contactType == 1)
    {
        printf("Phone      : %s\n",
               s->personal.contact.phone);
    }
    else
    {
        printf("Email      : %s\n",
               s->personal.contact.email);
    }

    printf("Marks      : ");

    for (int i = 0; i < SUBJECTS; i++)
    {
        printf("%d ", s->academic.marks[i]);
    }

    printf("\nTotal      : %d / 500",
           calculateTotal(s->academic.marks, SUBJECTS));

    printf("\nPercentage : %.2f%%", percentage);

    printf("\nGrade      : %c", calculateGrade(percentage));

    printf("\nStatus     : %s",
           (s->flags & ACTIVE) ? "Active" : "Inactive");

    printf("\nScholarship: %s",
           (s->flags & SCHOLARSHIP) ? "Yes" : "No");

    printf("\n-----------------------------\n");
}


// Display all students
void displayStudents(Student students[], int count)
{
    if (count == 0)
    {
        printf("No student records found!\n");
        return;
    }

    for (int i = 0; i < count; i++)
    {
        displayOne(&students[i]);
    }
}


// Search student
void searchStudent(Student students[], int count)
{
    if (count == 0)
    {
        printf("No records available!\n");
        return;
    }

    printf("\n1. Search by UID\n");
    printf("2. Search by Name\n");

    int choice = readInt("Enter choice: ", 1, 2);

    char search[100];

    readLine("Enter search value: ", search, sizeof(search));

    int found = 0;

    for (int i = 0; i < count; i++)
    {
        int match = 0;

        if (choice == 1)
        {
            match = (strcmp(students[i].personal.uid, search) == 0);
        }
        else
        {
            match = (strstr(students[i].personal.name, search) != NULL);
        }

        if (match)
        {
            displayOne(&students[i]);
            found = 1;
        }
    }

    if (!found)
    {
        printf("Student not found!\n");
    }
}


// Update marks
void updateStudent(Student students[], int count)
{
    char uid[MAX_UID];

    readLine("Enter student UID: ", uid, MAX_UID);

    int index = findStudent(students, count, uid);

    if (index == -1)
    {
        printf("Student not found!\n");
        return;
    }

    printf("Enter updated marks:\n");

    for (int i = 0; i < SUBJECTS; i++)
    {
        char message[50];

        sprintf(message, "Subject %d: ", i + 1);

        students[index].academic.marks[i] =
            readInt(message, 0, 100);
    }

    printf("Marks updated successfully!\n");
}


// Delete student
void deleteStudent(Student students[], int *count)
{
    char uid[MAX_UID];

    readLine("Enter UID to delete: ", uid, MAX_UID);

    int index = findStudent(students, *count, uid);

    if (index == -1)
    {
        printf("Student not found!\n");
        return;
    }

    for (int i = index; i < *count - 1; i++)
    {
        students[i] = students[i + 1];
    }

    (*count)--;

    printf("Student deleted successfully!\n");
}


// Sort students by percentage
void sortStudents(Student students[], int count)
{
    if (count == 0)
    {
        printf("No records to sort!\n");
        return;
    }

    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            float p1 = calculatePercentage(
                students[j].academic.marks);

            float p2 = calculatePercentage(
                students[j + 1].academic.marks);

            if (p1 < p2)
            {
                Student temp = students[j];

                students[j] = students[j + 1];

                students[j + 1] = temp;
            }
        }
    }

    printf("Students sorted successfully!\n");
}


// Class statistics with dynamic 2D array
void classStatistics(Student students[], int count)
{
    if (count == 0)
    {
        printf("No records available!\n");
        return;
    }

    int (*matrix)[SUBJECTS] =
        malloc((size_t)count * sizeof(*matrix));

    if (matrix == NULL)
    {
        printf("Memory allocation failed!\n");
        return;
    }

    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < SUBJECTS; j++)
        {
            matrix[i][j] = students[i].academic.marks[j];
        }
    }

    float total = 0;
    float highest = -1;
    float lowest = 101;

    int highIndex = 0;
    int lowIndex = 0;
    int passed = 0;

    for (int i = 0; i < count; i++)
    {
        float p = (float)calculateTotal(matrix[i], SUBJECTS)
                  / SUBJECTS;

        total += p;

        if (p > highest)
        {
            highest = p;
            highIndex = i;
        }

        if (p < lowest)
        {
            lowest = p;
            lowIndex = i;
        }

        if (p >= 50)
        {
            passed++;
        }
    }

    printf("\n===== CLASS STATISTICS =====\n");

    printf("Total Students : %d\n", count);

    printf("Class Average  : %.2f%%\n", total / count);

    printf("Highest Score  : %.2f%% (%s)\n",
           highest, students[highIndex].personal.name);

    printf("Lowest Score   : %.2f%% (%s)\n",
           lowest, students[lowIndex].personal.name);

    printf("Passed         : %d\n", passed);

    printf("Failed         : %d\n", count - passed);

    printf("Pass Percentage: %.2f%%\n",
           (float)passed * 100 / count);

    free(matrix);
}


// Save records
int saveRecords(Student students[], int count)
{
    FILE *fp = fopen(DATA_FILE, "wb");

    if (fp == NULL)
    {
        printf("Unable to save records!\n");
        return 0;
    }

    int success = 1;

    if (fwrite(&count, sizeof(int), 1, fp) != 1)
    {
        success = 0;
    }

    if (success && count > 0)
    {
        if (fwrite(students, sizeof(Student), count, fp)
            != (size_t)count)
        {
            success = 0;
        }
    }

    fclose(fp);

    if (success)
    {
        printf("Records saved successfully!\n");
    }
    else
    {
        printf("Error saving records!\n");
    }

    return success;
}


// Load records
int loadRecords(Student **students, int *capacity)
{
    FILE *fp = fopen(DATA_FILE, "rb");

    if (fp == NULL)
    {
        return 0;
    }

    int count;

    if (fread(&count, sizeof(int), 1, fp) != 1 ||
        count < 0 || count > 100000)
    {
        fclose(fp);
        return 0;
    }

    if (count == 0)
    {
        fclose(fp);
        return 0;
    }

    Student *temp = realloc(
        *students, (size_t)count * sizeof(Student));

    if (temp == NULL)
    {
        fclose(fp);
        return 0;
    }

    *students = temp;
    *capacity = count;

    if (fread(*students, sizeof(Student), count, fp)
        != (size_t)count)
    {
        fclose(fp);
        return 0;
    }

    fclose(fp);

    return count;
}


// Export report
void exportReport(Student students[], int count)
{
    FILE *fp = fopen("student_report.txt", "w");

    if (fp == NULL)
    {
        printf("Unable to create report!\n");
        return;
    }

    fprintf(fp, "STUDENT ACADEMIC PERFORMANCE REPORT\n");
    fprintf(fp, "====================================\n\n");

    for (int i = 0; i < count; i++)
    {
        float p = calculatePercentage(
            students[i].academic.marks);

        fprintf(fp, "Name: %s\n",
                students[i].personal.name);

        fprintf(fp, "UID: %s\n",
                students[i].personal.uid);

        fprintf(fp, "Total: %d / 500\n",
                calculateTotal(
                    students[i].academic.marks, SUBJECTS));

        fprintf(fp, "Percentage: %.2f%%\n", p);

        fprintf(fp, "Grade: %c\n", calculateGrade(p));

        fprintf(fp, "-----------------------------\n");
    }

    fclose(fp);

    printf("Report exported successfully!\n");
}


// Main function
int main()
{
    int count = 0;
    int capacity = 2;

    Student *students = calloc(
        capacity, sizeof(Student));

    if (students == NULL)
    {
        printf("Memory allocation failed!\n");
        return 1;
    }

    count = loadRecords(&students, &capacity);

    printf("\n====================================\n");
    printf("    STUDENT MANAGEMENT SYSTEM\n");
    printf("====================================\n");

    printf("Loaded %d student records.\n", count);

    int choice;

    do
    {
        printf("\n========== MAIN MENU ==========\n");

        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student Marks\n");
        printf("5. Delete Student\n");
        printf("6. Sort Students\n");
        printf("7. Class Statistics\n");
        printf("8. Export Text Report\n");
        printf("9. Save Records\n");
        printf("0. Save and Exit\n");

        printf("===============================\n");

        choice = readInt("Enter your choice: ", 0, 9);

        switch (choice)
        {
            case 1:
                addStudent(&students, &count, &capacity);
                break;

            case 2:
                displayStudents(students, count);
                break;

            case 3:
                searchStudent(students, count);
                break;

            case 4:
                updateStudent(students, count);
                break;

            case 5:
                deleteStudent(students, &count);
                break;

            case 6:
                sortStudents(students, count);
                break;

            case 7:
                classStatistics(students, count);
                break;

            case 8:
                exportReport(students, count);
                break;

            case 9:
                saveRecords(students, count);
                break;

            case 0:
                saveRecords(students, count);
                printf("\nThank you for using the system!\n");
                break;
        }

    } while (choice != 0);

    free(students);

    return 0;
}
