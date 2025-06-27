#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to store student data
typedef struct
{
    char name[50];
    int rollnumber;
    float *subjectMarks;
    float average;
    int status_flag;


} Student;

// Function to calculate the average marks for a student
float Average(float *marks, int numSubjects)
{
    float sum = 0.0;
    for (int i = 0; i < numSubjects; i++)
    {
        sum += marks[i];
    }
    return sum / numSubjects;
}

// Function to find the topper
void Topper(Student *students, int numStudents, int numSubjects, Student *topper)
{
    float highestAverage = -1.0;
    for (int i = 0; i < numStudents; i++)
    {
        if (students[i].average > highestAverage)
        {
            highestAverage = students[i].average;
            *topper = students[i];
        }
    }
}

// Function to display subject-wise performance
void displaySubjectPerformance(Student *students, int numStudents, int numSubjects)
{
    printf("\nSubject-wise Performance:\n");
    for (int i = 0; i < numStudents; i++)
    {
        printf("Student Roll number: %d\n", students[i].rollnumber);
        for (int j = 0; j < numSubjects; j++)
        {
            printf("  Subject %d: %.2f\n", j + 1, students[i].subjectMarks[j]);
        }
        printf("  Average: %.2f\n", students[i].average);
    }
}

int main()
{
    int numStudents, numSubjects;


    // Get the number of students and subjects
    printf("Enter the number of students: ");
    scanf("%d", &numStudents);

    printf("Enter the number of subjects: ");
    scanf("%d", &numSubjects);

    // Allocate memory for an array of Student structures
    Student *students = (Student *)malloc(numStudents * sizeof(Student));
    if (students == NULL)
    {
        printf("Memory allocation failed!\n");
        return 1;
    }

    // Input student data
    for (int i = 0; i < numStudents; i++)
    {
        printf("\nEnter details for student %d:\n", i + 1);

        printf("Name: ");
        scanf(" %s", students[i].name);// Added space before %s to consume newline character
        printf("Roll number: ");
        scanf("%d", &students[i].rollnumber);

        // Allocate memory for subject marks
        students[i].subjectMarks = (float *)malloc(numSubjects * sizeof(float));
        if (students[i].subjectMarks == NULL)
        {
             printf("Memory allocation failed!\n");
            // Free previously allocated memory before exiting
            for (int j = 0; j < i; j++)
            {
                free(students[j].subjectMarks);
            }
            free(students);
            return 1;
        }



        printf("Enter marks for %d subjects:\n", numSubjects);
        for (int j = 0; j < numSubjects; j++)
        {
            printf("Subject %d: ", j + 1);
            scanf("%f", &students[i].subjectMarks[j]);

// Check status using bitwise AND
            // check for fail condition
           if (students[i].subjectMarks[j] >= 0 && students[i].subjectMarks[j] < 35 )
            {
                students[i].status_flag = 0;
            }

            // check for pass condition
            if (students[i].subjectMarks[j] >= 35 && students[i].subjectMarks[j] < 75)
            {
                students[i].status_flag = 1;
            }
            // Check for distinction condition
            if (students[i].subjectMarks[j] >= 75 && students[i].subjectMarks[j] <=100)
            {
                students[i].status_flag = 2;
            }


        if (students[i].status_flag == 1)
        {
            printf("Result: Passed\n");
        }
        else if (students[i].status_flag == 2)
            {
                printf("Result: Distinction\n");
            }
        else if (students[i].status_flag == 0)
        {
            printf("Result: Failed\n");
        }
        }
        // Calculate average marks
        students[i].average = Average(students[i].subjectMarks, numSubjects);
    }

    // Find the topper
    Student topper;
    Topper(students, numStudents, numSubjects, &topper);
    printf("\nTopper:\n");
    printf("Name: %s\n", topper.name);
    printf("Roll number: %d\n", topper.rollnumber);
    printf("Average: %.2f\n", topper.average);

    // Display subject-wise performance
    displaySubjectPerformance(students, numStudents, numSubjects);



    // Free allocated memory
    for (int i = 0; i < numStudents; i++)
    {
        free(students[i].subjectMarks);
    }
    free(students);


    return 0;
}


