#ifndef GPA_H
#define GPA_H

#include "courseResult.h"
#include "courseList.h"   /* Feature 006 */

/*
 * GpaResult
 * ---------
 * Aggregated result of computing the weighted CGPA.
 */
typedef struct GpaResult {
    int    courseCount;     /* total courses (including incomplete)  */
    int    incompleteCount; /* courses excluded from CGPA            */
    double totalCredits;    /* Σ credit (completed courses only)      */
    double weightedSum;     /* Σ (gradePoint × credit) completed      */
    double cgpa;            /* weightedSum / totalCredits              */
} GpaResult;

/* Overall CGPA across all semesters */
GpaResult computeGPA(CourseResult results[], int count);
void      viewGPA(GpaResult gpa);

/* Feature 005 — per-semester GPA */
GpaResult computeSemesterGPA(CourseResult results[], int count, int semester);
void      viewSemesterGPA(GpaResult gpa, int semester);

/* Feature 006 — compute from dynamic list */
GpaResult computeGPAFromList(CourseList *list);

#endif /* GPA_H */
