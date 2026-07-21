#ifndef STUDENT_H
#define STUDENT_H

#include "courseList.h"
#include "gpa.h"

/*
 * Student
 * -------
 * Represents a single student with a dynamic transcript and computed GPA.
 *
 * Workflow:
 *   1. createStudent(id, name)
 *   2. addCourseToStudent(&student, cr)   — multiple times
 *   3. computeStudentGPA(&student)
 *   4. viewStudent(&student)
 *   5. freeStudent(&student)             — release heap memory
 */
typedef struct Student {
    char       id[20];
    char       name[64];
    CourseList courseList;
    GpaResult  gpa;
} Student;

Student createStudent(char id[], char name[]);
void    addCourseToStudent(Student *student, CourseResult cr);
void    computeStudentGPA(Student *student);
void    viewStudent(Student *student);
void    freeStudent(Student *student);

#endif /* STUDENT_H */
