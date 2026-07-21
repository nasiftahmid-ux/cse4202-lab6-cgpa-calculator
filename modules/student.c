#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

Student createStudent(char id[], char name[]) {
    Student student;
    strcpy(student.id, id);
    strcpy(student.name, name);
    student.courseList = createCourseList();
    student.gpa = (GpaResult){0, 0, 0.0, 0.0, 0.0};
    return student;
}

void addCourseToStudent(Student *student, CourseResult cr) {
    addCourseResult(&student->courseList, cr);
}

void computeStudentGPA(Student *student) {
    student->gpa = computeGPAFromList(&student->courseList);
}

void viewStudent(Student *student) {
    printf("Student ID   : %s\n", student->id);
    printf("Student Name : %s\n", student->name);
    printf("Courses      : %d\n", student->courseList.count);
    printf("CGPA         : %.2f\n", student->gpa.cgpa);
    printf("Credits      : %.1f\n", student->gpa.totalCredits);
}

void freeStudent(Student *student) {
    freeCourseList(&student->courseList);
}
