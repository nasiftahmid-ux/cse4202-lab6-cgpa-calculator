#include <stdio.h>
#include <string.h>
#include "../modules/course.h"

int testCourseCode()
{
    Course course = createCourse("CSE 4202", "Structured Programming II Lab", 1.5);
    return strcmp(course.code, "CSE 4202") == 0;
}

int testCourseName()
{
    Course course = createCourse("CSE 4202", "Structured Programming II Lab", 1.5);
    return strcmp(course.name, "Structured Programming II Lab") == 0;
}

int testCourseCredit()
{
    Course course = createCourse("CSE 4202", "Structured Programming II Lab", 1.5);
    return course.credit == 1.5;
}

int main()
{
    printf("Course module tests\n");
    int passed = 0;
    int total = 0;

    total++;
    if (testCourseCode()) passed++;
    total++;
    if (testCourseName()) passed++;
    total++;
    if (testCourseCredit()) passed++;

    printf("Passed %d/%d tests\n", passed, total);
    if (passed == total) return 0;
    return 1;
}