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

/*
 * RequiredGpaResult (Feature 007)
 * --------------------------------
 * Given a student's current GPA state and the credits still to be taken,
 * computes the minimum GPA they must achieve in remaining courses to hit
 * a target CGPA.
 *
 * Formula:
 *   requiredGPA = (targetCGPA * (current.totalCredits + remainingCredits)
 *                  - current.weightedSum) / remainingCredits
 *
 * isAchievable = 1 when requiredGPA <= 4.00
 * (negative requiredGPA means the target is already guaranteed)
 */
typedef struct RequiredGpaResult {
    double targetCGPA;
    double remainingCredits;
    double requiredGPA;
    int    isAchievable; /* 1 if requiredGPA <= 4.00 */
} RequiredGpaResult;

RequiredGpaResult computeRequiredGPA(GpaResult current,
                                     double remainingCredits,
                                     double targetCGPA);
void              viewRequiredGPA(RequiredGpaResult result);

#endif /* GPA_H */

