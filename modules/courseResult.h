#ifndef COURSE_RESULT_H
#define COURSE_RESULT_H

#include "course.h"

/*
 * CourseResult
 * ------------
 * Associates a Course with marks, computed grade, and grade point.
 *
 * Feature 004 — isIncomplete:
 *   When set to 1, the course has not yet been graded.
 *   Incomplete courses are excluded from CGPA computation.
 *
 * IUT Grading Scale:
 *   A+ = 4.00 (>= 90)  A  = 3.75 (>= 85)  A- = 3.50 (>= 80)
 *   B+ = 3.25 (>= 75)  B  = 3.00 (>= 70)  B- = 2.75 (>= 65)
 *   C+ = 2.50 (>= 60)  C  = 2.25 (>= 55)  D  = 2.00 (>= 50)
 *   F  = 0.00 (< 50)
 */
typedef struct CourseResult {
    Course course;
    double marks;        /* raw score: 0.0 – 100.0     */
    char   grade[4];     /* letter grade: "A+", "B-", … */
    double gradePoint;   /* grade point:  0.00 – 4.00   */
    int    isIncomplete; /* 1 = not yet graded (Feat 004) */
} CourseResult;

CourseResult createCourseResult(Course course, double marks);
void         markIncomplete(CourseResult *cr);   /* Feature 004 */
void         viewCourseResult(CourseResult cr);

#endif /* COURSE_RESULT_H */
