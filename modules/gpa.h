#ifndef GPA_H
#define GPA_H

#include "courseResult.h"

/*
 * GpaResult
 * ---------
 * Aggregated result of computing the weighted CGPA across a set of courses.
 *
 * Formula:
 *   weightedSum  = Σ (gradePoint_i × credit_i)
 *   totalCredits = Σ credit_i
 *   cgpa         = weightedSum / totalCredits   (0.00 if no credits)
 */
typedef struct GpaResult {
    int    courseCount;   /* number of courses included in calculation  */
    double totalCredits;  /* Σ credit                                    */
    double weightedSum;   /* Σ (gradePoint × credit)                     */
    double cgpa;          /* final CGPA: weightedSum / totalCredits       */
} GpaResult;

/*
 * computeGPA
 * ----------
 * Computes the weighted CGPA from an array of CourseResult.
 * Returns a GpaResult with cgpa = 0.00 when count <= 0 or totalCredits == 0.
 */
GpaResult computeGPA(CourseResult results[], int count);

/*
 * viewGPA
 * -------
 * Prints a formatted CGPA summary to stdout.
 */
void viewGPA(GpaResult gpa);

#endif /* GPA_H */
