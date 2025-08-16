#include <stdio.h>
#include <string.h>

#define MAX_NAME 50   // maximum characters for a student's name
#define MAX_STUDENTS 100  // maximum number of students allowed

int main() {
    int n;  
    char names[MAX_STUDENTS][MAX_NAME];  // array of strings (names)
    float grades[MAX_STUDENTS];          // array of grades
    float sum = 0, average;
    float highest, lowest;
    int i, index_highest, index_lowest;

    // Step 1: Ask how many students
    printf("Enter number of students: ");
    scanf("%d", &n);

    // Basic validation
    if (n <= 0 || n > MAX_STUDENTS) {
        printf("Invalid number of students.\n");
        return 1;
    }

    // Step 2: Input names and grades
    for (i = 0; i < n; i++) {
        printf("\nEnter name of student %d: ", i + 1);
        scanf("%s", names[i]);   // read string (no spaces)

        printf("Enter grade of %s (0-20): ", names[i]);
        scanf("%f", &grades[i]);

        // accumulate for average
        sum += grades[i];
    }

    // Step 3: Initialize highest and lowest
    highest = grades[0];
    lowest = grades[0];
    index_highest = 0;
    index_lowest = 0;

    // Step 4: Find highest and lowest
    for (i = 1; i < n; i++) {
        if (grades[i] > highest) {
            highest = grades[i];
            index_highest = i;
        }
        if (grades[i] < lowest) {
            lowest = grades[i];
            index_lowest = i;
        }
    }

    // Step 5: Calculate average
    average = sum / n;

    // Step 6: Display results
    printf("\n--- Student Grades ---\n");
    for (i = 0; i < n; i++) {
        printf("%s : %.2f\n", names[i], grades[i]);
    }

    printf("\nClass Average: %.2f\n", average);
    printf("Highest Grade: %.2f (by %s)\n", highest, names[index_highest]);
    printf("Lowest Grade: %.2f (by %s)\n", lowest, names[index_lowest]);

    return 0;
}
