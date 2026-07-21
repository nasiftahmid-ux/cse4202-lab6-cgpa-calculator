#include <stdio.h>
#include "gpa.h"

GpaResult computeGPA(CourseResult results[], int count) {
    GpaResult gpa;
    gpa.courseCount     = count;
    gpa.incompleteCount = 0;
    gpa.totalCredits    = 0.0;
    gpa.weightedSum     = 0.0;
    gpa.cgpa            = 0.0;

    if (count <= 0) return gpa;

    for (int i = 0; i < count; i++) {
        if (results[i].isIncomplete) {
            gpa.incompleteCount++;
            continue;
        }
        gpa.totalCredits += results[i].course.credit;
        gpa.weightedSum  += results[i].gradePoint * results[i].course.credit;
    }

    if (gpa.totalCredits > 0.0) {
        gpa.cgpa = gpa.weightedSum / gpa.totalCredits;
    }

    return gpa;
}

void viewGPA(GpaResult gpa) {
    printf("Courses      : %d\n",   gpa.courseCount);
    printf("Completed    : %d\n",   gpa.courseCount - gpa.incompleteCount);
    printf("Incomplete   : %d\n",   gpa.incompleteCount);
    printf("Total Credits: %.1f\n", gpa.totalCredits);
    printf("Weighted Sum : %.2f\n", gpa.weightedSum);
    printf("CGPA         : %.2f\n", gpa.cgpa);
}

/* Feature 005 ─────────────────────────────────────────────────────────── */

/*
 * computeSemesterGPA
 * ------------------
 * Filters results[] to those matching `semester`, then computes
 * weighted GPA using the same incomplete-exclusion logic as computeGPA.
 */
GpaResult computeSemesterGPA(CourseResult results[], int count, int semester) {
    GpaResult gpa;
    gpa.courseCount     = 0;
    gpa.incompleteCount = 0;
    gpa.totalCredits    = 0.0;
    gpa.weightedSum     = 0.0;
    gpa.cgpa            = 0.0;

    for (int i = 0; i < count; i++) {
        if (results[i].semester != semester) continue;
        gpa.courseCount++;
        if (results[i].isIncomplete) {
            gpa.incompleteCount++;
            continue;
        }
        gpa.totalCredits += results[i].course.credit;
        gpa.weightedSum  += results[i].gradePoint * results[i].course.credit;
    }

    if (gpa.totalCredits > 0.0) {
        gpa.cgpa = gpa.weightedSum / gpa.totalCredits;
    }

    return gpa;
}

void viewSemesterGPA(GpaResult gpa, int semester) {
    printf("Semester     : %d\n",   semester);
    printf("Courses      : %d\n",   gpa.courseCount);
    printf("Total Credits: %.1f\n", gpa.totalCredits);
    printf("Weighted Sum : %.2f\n", gpa.weightedSum);
    printf("GPA          : %.2f\n", gpa.cgpa);
}
