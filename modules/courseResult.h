#ifndef COURSE_RESULT_H
#define COURSE_RESULT_H

#include "course.h"

/*
 * CourseResult
 * ------------
 * Associates a Course with a numeric marks score (0–100) and stores the
 * derived letter grade and grade point according to the IUT grading scale.
 *
 * IUT Grading Scale:
 *   A+  = 4.00  (marks >= 90)
 *   A   = 3.75  (85 <= marks < 90)
 *   A-  = 3.50  (80 <= marks < 85)
 *   B+  = 3.25  (75 <= marks < 80)
 *   B   = 3.00  (70 <= marks < 75)
 *   B-  = 2.75  (65 <= marks < 70)
 *   C+  = 2.50  (60 <= marks < 65)
 *   C   = 2.25  (55 <= marks < 60)
 *   D   = 2.00  (50 <= marks < 55)
 *   F   = 0.00  (marks <  50)
 */
typedef struct CourseResult {
    Course course;
    double marks;       /* raw score: 0.0 – 100.0     */
    char   grade[4];    /* letter grade: "A+", "B-", … */
    double gradePoint;  /* grade point:  0.00 – 4.00   */
} CourseResult;

/* Create a CourseResult by computing grade and gradePoint from marks. */
CourseResult createCourseResult(Course course, double marks);

/* Print a formatted summary of the CourseResult to stdout. */
void viewCourseResult(CourseResult cr);

#endif /* COURSE_RESULT_H */
