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
        if (results[i].isIncomplete) {      /* Feature 004: skip incomplete */
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
