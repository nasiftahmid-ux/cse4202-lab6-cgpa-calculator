#ifndef GPA_H
#define GPA_H

#include "courseResult.h"

/*
 * GpaResult
 * ---------
 * Aggregated result of computing the weighted CGPA.
 * Feature 004 — incompleteCount : courses excluded from CGPA.
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

#endif /* GPA_H */
