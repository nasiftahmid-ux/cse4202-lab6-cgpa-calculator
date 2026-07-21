#include <stdio.h>
#include "gpa.h"

GpaResult computeGPA(CourseResult results[], int count) {
    GpaResult gpa;
    gpa.courseCount  = count;
    gpa.totalCredits = 0.0;
    gpa.weightedSum  = 0.0;
    gpa.cgpa         = 0.0;

    if (count <= 0) {
        return gpa;
    }

    for (int i = 0; i < count; i++) {
        gpa.totalCredits += results[i].course.credit;
        gpa.weightedSum  += results[i].gradePoint * results[i].course.credit;
    }

    if (gpa.totalCredits > 0.0) {
        gpa.cgpa = gpa.weightedSum / gpa.totalCredits;
    }

    return gpa;
}

void viewGPA(GpaResult gpa) {
    printf("Courses      : %d\n",    gpa.courseCount);
    printf("Total Credits: %.1f\n",  gpa.totalCredits);
    printf("Weighted Sum : %.2f\n",  gpa.weightedSum);
    printf("CGPA         : %.2f\n",  gpa.cgpa);
}
