#include <stdio.h>
#include <math.h>
#include "../modules/course.h"
#include "../modules/courseResult.h"
#include "../modules/gpa.h"

/* ── helpers ─────────────────────────────────────────────────────────────── */
static int passed = 0;
static int total  = 0;

#define EPSILON 1e-9
static int dEq(double a, double b) { return fabs(a - b) < EPSILON; }

static void check(const char *name, int result) {
    total++;
    if (result) { passed++; printf("  [PASS] %s\n", name); }
    else                    printf("  [FAIL] %s\n", name);
}

/* ── tests ───────────────────────────────────────────────────────────────── */

/* Default isIncomplete must be 0 */
static int testDefaultComplete(void) {
    Course c = createCourse("TST 001", "Test", 3.0);
    CourseResult cr = createCourseResult(c, 80.0);
    return cr.isIncomplete == 0;
}

/* markIncomplete sets the flag */
static int testMarkIncomplete(void) {
    Course c = createCourse("TST 002", "Test", 3.0);
    CourseResult cr = createCourseResult(c, 80.0);
    markIncomplete(&cr);
    return cr.isIncomplete == 1;
}

/*
 * One incomplete course excluded from CGPA.
 * Complete: A (3.75 × 3cr) + B (3.00 × 2cr) = 17.25 / 5cr = 3.45
 * Incomplete: 3cr course — NOT counted.
 */
static int testIncompleteExcluded(void) {
    Course c1 = createCourse("C1", "Course A", 3.0);
    Course c2 = createCourse("C2", "Course B", 2.0);
    Course c3 = createCourse("C3", "Incomplete Course", 3.0);

    CourseResult results[3];
    results[0] = createCourseResult(c1, 87.5); /* A  3.75 */
    results[1] = createCourseResult(c2, 72.0); /* B  3.00 */
    results[2] = createCourseResult(c3, 0.0);
    markIncomplete(&results[2]);

    GpaResult gpa = computeGPA(results, 3);

    return dEq(gpa.cgpa, 17.25 / 5.0)
        && dEq(gpa.totalCredits, 5.0)
        && dEq(gpa.weightedSum, 17.25)
        && gpa.incompleteCount == 1
        && gpa.courseCount     == 3;
}

/* All incomplete → CGPA = 0, no credits counted */
static int testAllIncomplete(void) {
    Course c1 = createCourse("C1", "Course A", 3.0);
    Course c2 = createCourse("C2", "Course B", 2.0);
    CourseResult results[2];
    results[0] = createCourseResult(c1, 0.0);
    results[1] = createCourseResult(c2, 0.0);
    markIncomplete(&results[0]);
    markIncomplete(&results[1]);

    GpaResult gpa = computeGPA(results, 2);

    return dEq(gpa.cgpa, 0.0)
        && dEq(gpa.totalCredits, 0.0)
        && gpa.incompleteCount == 2
        && gpa.courseCount     == 2;
}

/* All complete — incompleteCount must stay 0 */
static int testNoIncomplete(void) {
    Course c = createCourse("C1", "Course A", 3.0);
    CourseResult results[1];
    results[0] = createCourseResult(c, 91.0); /* A+ 4.00 */
    GpaResult gpa = computeGPA(results, 1);
    return gpa.incompleteCount == 0
        && dEq(gpa.cgpa, 4.00);
}

/* Multiple incomplete courses tracked correctly */
static int testMultipleIncomplete(void) {
    Course c1 = createCourse("C1", "A", 3.0);
    Course c2 = createCourse("C2", "B", 2.0);
    Course c3 = createCourse("C3", "C", 1.0);
    CourseResult results[3];
    results[0] = createCourseResult(c1, 90.0); /* A+ 4.00 × 3 = 12 */
    results[1] = createCourseResult(c2, 0.0);
    results[2] = createCourseResult(c3, 0.0);
    markIncomplete(&results[1]);
    markIncomplete(&results[2]);

    GpaResult gpa = computeGPA(results, 3);
    return gpa.incompleteCount == 2
        && dEq(gpa.totalCredits, 3.0)
        && dEq(gpa.cgpa, 4.00);
}

/* ── main ────────────────────────────────────────────────────────────────── */
int main(void) {
    printf("Incomplete Courses module tests\n");
    printf("─────────────────────────────────────\n");
    check("Default isIncomplete = 0",                  testDefaultComplete());
    check("markIncomplete sets isIncomplete = 1",       testMarkIncomplete());
    check("Incomplete course excluded from CGPA",       testIncompleteExcluded());
    check("All incomplete → CGPA = 0",                 testAllIncomplete());
    check("No incomplete → incompleteCount = 0",       testNoIncomplete());
    check("Multiple incomplete tracked correctly",     testMultipleIncomplete());
    printf("─────────────────────────────────────\n");
    printf("Passed %d/%d tests\n", passed, total);
    return (passed == total) ? 0 : 1;
}
