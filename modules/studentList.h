#ifndef STUDENT_LIST_H
#define STUDENT_LIST_H

#include "student.h"

#define STUDENT_LIST_INITIAL_CAPACITY 4

/*
 * StudentList
 * -----------
 * A dynamically growing array of Student items.
 * Identical growth strategy as CourseList (capacity doubles).
 */
typedef struct StudentList {
    Student *items;
    int      count;
    int      capacity;
} StudentList;

StudentList createStudentList(void);
void        addStudent(StudentList *list, Student student);
Student    *getStudent(StudentList *list, int index);
void        viewStudentList(StudentList *list);
void        freeStudentList(StudentList *list);

#endif /* STUDENT_LIST_H */
