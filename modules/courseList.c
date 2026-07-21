#include <stdio.h>
#include <stdlib.h>
#include "courseList.h"

CourseList createCourseList(void) {
    CourseList list;
    list.count    = 0;
    list.capacity = COURSE_LIST_INITIAL_CAPACITY;
    list.items    = (CourseResult *)malloc(list.capacity * sizeof(CourseResult));
    if (!list.items) {
        fprintf(stderr, "Error: failed to allocate CourseList\n");
        exit(EXIT_FAILURE);
    }
    return list;
}

void addCourseResult(CourseList *list, CourseResult cr) {
    if (list->count >= list->capacity) {
        list->capacity *= 2;
        list->items = (CourseResult *)realloc(list->items,
                                              list->capacity * sizeof(CourseResult));
        if (!list->items) {
            fprintf(stderr, "Error: failed to grow CourseList\n");
            exit(EXIT_FAILURE);
        }
    }
    list->items[list->count++] = cr;
}

CourseResult getCourseResult(CourseList *list, int index) {
    return list->items[index];
}

void viewCourseList(CourseList *list) {
    printf("%-10s %-30s %4s %7s %4s %6s\n",
           "Code", "Name", "Sem", "Marks", "Gr", "GP");
    printf("%-10s %-30s %4s %7s %4s %6s\n",
           "----------","------------------------------","----","-------","----","------");
    for (int i = 0; i < list->count; i++) {
        CourseResult cr = list->items[i];
        if (cr.isIncomplete)
            printf("%-10s %-30s %4d %7s %4s %6s\n",
                   cr.course.code, cr.course.name, cr.semester,
                   "---", "INC", "---");
        else
            printf("%-10s %-30s %4d %7.2f %4s %6.2f\n",
                   cr.course.code, cr.course.name, cr.semester,
                   cr.marks, cr.grade, cr.gradePoint);
    }
}

void freeCourseList(CourseList *list) {
    free(list->items);
    list->items    = NULL;
    list->count    = 0;
    list->capacity = 0;
}
