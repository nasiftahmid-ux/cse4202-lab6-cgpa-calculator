#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "studentList.h"

StudentList createStudentList(void) {
    StudentList list;
    list.count = 0;
    list.capacity = STUDENT_LIST_INITIAL_CAPACITY;
    list.items = (Student *)malloc(list.capacity * sizeof(Student));
    if (!list.items) {
        fprintf(stderr, "Error: failed to allocate StudentList\n");
        exit(EXIT_FAILURE);
    }
    return list;
}

void addStudent(StudentList *list, Student student) {
    if (list->count >= list->capacity) {
        list->capacity *= 2;
        list->items = (Student *)realloc(list->items, list->capacity * sizeof(Student));
        if (!list->items) {
            fprintf(stderr, "Error: failed to grow StudentList\n");
            exit(EXIT_FAILURE);
        }
    }
    list->items[list->count++] = student;
}

Student *getStudent(StudentList *list, int index) {
    return &list->items[index];
}

void viewStudentList(StudentList *list) {
    for (int i = 0; i < list->count; i++) {
        printf("%d. %s (%s) -> CGPA %.2f\n",
               i + 1,
               list->items[i].name,
               list->items[i].id,
               list->items[i].gpa.cgpa);
    }
}

void freeStudentList(StudentList *list) {
    for (int i = 0; i < list->count; i++) {
        freeStudent(&list->items[i]);
    }
    free(list->items);
    list->items = NULL;
    list->count = 0;
    list->capacity = 0;
}
