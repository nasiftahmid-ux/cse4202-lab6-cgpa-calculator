#ifndef COURSE_LIST_H
#define COURSE_LIST_H

#include "courseResult.h"

#define COURSE_LIST_INITIAL_CAPACITY 4

/*
 * CourseList
 * ----------
 * A dynamically growing array of CourseResult items.
 * Capacity doubles when the array is full (amortised O(1) append).
 */
typedef struct CourseList {
    CourseResult *items;   /* heap-allocated array of CourseResult  */
    int           count;   /* current number of items               */
    int           capacity;/* allocated capacity                    */
} CourseList;

CourseList   createCourseList(void);
void         addCourseResult(CourseList *list, CourseResult cr);
CourseResult getCourseResult(CourseList *list, int index);
void         viewCourseList(CourseList *list);
void         freeCourseList(CourseList *list);

#endif /* COURSE_LIST_H */
