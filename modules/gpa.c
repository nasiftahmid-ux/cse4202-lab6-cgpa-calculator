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

/* Feature 006 ─────────────────────────────────────────────────────────── */
GpaResult computeGPAFromList(CourseList *list) {
    return computeGPA(list->items, list->count);
}

/* Feature 007 ─────────────────────────────────────────────────────────── */
RequiredGpaResult computeRequiredGPA(GpaResult current,
                                     double remainingCredits,
                                     double targetCGPA) {
    RequiredGpaResult result;
    result.targetCGPA       = targetCGPA;
    result.remainingCredits = remainingCredits;
    result.requiredGPA      = 0.0;
    result.isAchievable     = 0;

    if (remainingCredits <= 0.0) {
        result.requiredGPA  = -1.0; /* undefined */
        return result;
    }

    double totalAfter      = current.totalCredits + remainingCredits;
    result.requiredGPA     = (targetCGPA * totalAfter - current.weightedSum)
                             / remainingCredits;
    result.isAchievable    = (result.requiredGPA <= 4.00);
    return result;
}

void viewRequiredGPA(RequiredGpaResult result) {
    printf("Target CGPA       : %.2f\n", result.targetCGPA);
    printf("Remaining Credits : %.1f\n", result.remainingCredits);
    if (result.requiredGPA <= 0.0)
        printf("Required GPA      : Already guaranteed\n");
    else
        printf("Required GPA      : %.2f\n", result.requiredGPA);
    printf("Achievable        : %s\n",
           result.isAchievable ? "Yes" : "No (requires > 4.00)");
}

/* Feature 008 ─────────────────────────────────────────────────────────── */
GpaResult computeExpectedGPA(CourseList *completed, CourseList *upcoming) {
    int total = completed->count + upcoming->count;

    if (total == 0) {
        GpaResult empty = {0, 0, 0.0, 0.0, 0.0};
        return empty;
    }

    CourseResult *merged = (CourseResult *)malloc(total * sizeof(CourseResult));
    if (!merged) {
        fprintf(stderr, "Error: failed to allocate for expected GPA\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < completed->count; i++)
        merged[i] = completed->items[i];
    for (int i = 0; i < upcoming->count; i++)
        merged[completed->count + i] = upcoming->items[i];

    GpaResult result = computeGPA(merged, total);
    free(merged);
    return result;
}

void viewExpectedGPA(GpaResult expected) {
    printf("Projected Courses : %d\n",   expected.courseCount);
    printf("Projected Credits : %.1f\n", expected.totalCredits);
    printf("Projected Sum     : %.2f\n", expected.weightedSum);
    printf("Expected CGPA     : %.2f\n", expected.cgpa);
}

