#include <stdio.h>
#include <string.h>
#include "course.h"

Course createCourse(char code[], char name[], double credit) {
    Course course;
    strcpy(course.code, code);
    strcpy(course.name, name);
    course.credit = credit;
    return course;
}

void viewCourse(Course course) {
    printf("Code: %s\n", course.code);
    printf("Name: %s\n", course.name);
    printf("Credit: %.1f\n", course.credit);
}