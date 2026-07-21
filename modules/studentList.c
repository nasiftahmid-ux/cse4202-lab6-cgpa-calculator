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

/* Feature 010 */
void rankStudentsByCGPA(StudentList *list) {
    /* Stable insertion sort, descending by CGPA.
       Stable so students with equal CGPA keep their original
       insertion order (e.g. alphabetical, or roll-number order). */
    for (int i = 1; i < list->count; i++) {
        Student key = list->items[i];
        int j = i - 1;
        while (j >= 0 && list->items[j].gpa.cgpa < key.gpa.cgpa) {
            list->items[j + 1] = list->items[j];
            j--;
        }
        list->items[j + 1] = key;
    }
}

/* Feature 010 */
void viewRankingTable(StudentList *list) {
    printf("\n%-6s %-10s %-20s %-8s %-8s\n", "Rank", "ID", "Name", "CGPA", "Credits");
    printf("------ ---------- -------------------- -------- --------\n");
    for (int i = 0; i < list->count; i++) {
        printf("%-6d %-10s %-20s %-8.2f %-8.1f\n",
               i + 1,
               list->items[i].id,
               list->items[i].name,
               list->items[i].gpa.cgpa,
               list->items[i].gpa.totalCredits);
    }
}
