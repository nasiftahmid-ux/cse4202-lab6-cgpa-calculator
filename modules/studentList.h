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

/*
 * Feature 010 — Ranking
 * ---------------------
 * Sorts the list in place, highest CGPA first (descending).
 * Ties are broken by original insertion order (stable).
 * After sorting, index 0 is rank 1, index 1 is rank 2, etc.
 */
void        rankStudentsByCGPA(StudentList *list);

/*
 * Prints a formatted ranking table (Rank | ID | Name | CGPA | Credits).
 * Call rankStudentsByCGPA(list) first so the list is already sorted;
 * this function only renders — it does not sort.
 */
void        viewRankingTable(StudentList *list);

#endif /* STUDENT_LIST_H */
