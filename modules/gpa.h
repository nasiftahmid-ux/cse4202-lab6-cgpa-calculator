#ifndef GPA_H
#define GPA_H

#include "courseResult.h"

/*
 * GpaResult
 * ---------
 * Aggregated result of computing the weighted CGPA.
 *
 * Feature 004 — incompleteCount:
 *   Tracks how many courses were skipped (isIncomplete == 1).
 *   Only completed courses contribute to totalCredits / weightedSum / cgpa.
 */
typedef struct GpaResult {
    int    courseCount;     /* total courses (including incomplete)  */
    int    incompleteCount; /* courses excluded from CGPA (Feat 004) */
    double totalCredits;    /* Σ credit (completed courses only)      */
    double weightedSum;     /* Σ (gradePoint × credit) completed      */
    double cgpa;            /* weightedSum / totalCredits              */
} GpaResult;

GpaResult computeGPA(CourseResult results[], int count);
void      viewGPA(GpaResult gpa);

#endif /* GPA_H */
