#include <stdio.h>
#include <math.h>
#include "../modules/course.h"
#include "../modules/courseResult.h"
#include "../modules/courseList.h"
#include "../modules/gpa.h"

static int passed = 0;
static int total  = 0;
#define EPSILON 1e-9
static int dEq(double a, double b) { return fabs(a - b) < EPSILON; }
static void check(const char *name, int result) {
    total++;
    if (result) { passed++; printf("  [PASS] %s\n", name); }
    else                    printf("  [FAIL] %s\n", name);
}

/*
 * Helper: build a GpaResult manually to avoid CourseList dependency.
 *   current: totalCredits=10, weightedSum=35.0, cgpa=3.50
 */
static GpaResult makeCurrentGPA(void) {
    GpaResult gpa;
    gpa.courseCount     = 4;
    gpa.incompleteCount = 0;
    gpa.totalCredits    = 10.0;
    gpa.weightedSum     = 35.0;
    gpa.cgpa            = 3.50;
    return gpa;
}

/*
 * Achievable case:
 *   total after = 10 + 10 = 20
 *   requiredGPA = (3.75 * 20 - 35) / 10 = (75 - 35) / 10 = 4.00  ← achievable
 */
static int testAchievableExact(void) {
    GpaResult cur = makeCurrentGPA();
    RequiredGpaResult r = computeRequiredGPA(cur, 10.0, 3.75);
    return dEq(r.requiredGPA, 4.00) && r.isAchievable == 1;
}

/*
 * Not achievable:
 *   total after = 10 + 6 = 16
 *   requiredGPA = (3.75 * 16 - 35) / 6 = (60 - 35) / 6 = 4.1667  → NOT achievable
 */
static int testNotAchievable(void) {
    GpaResult cur = makeCurrentGPA();
    RequiredGpaResult r = computeRequiredGPA(cur, 6.0, 3.75);
    return (r.requiredGPA > 4.00) && r.isAchievable == 0;
}

/*
 * Already guaranteed:
 *   current CGPA = 4.00, target = 3.50, remaining = 5cr
 *   requiredGPA = (3.50 * (9 + 5) - 36) / 5 = (49 - 36) / 5 = 2.60
 *   → well within reach
 */
static int testAlreadyAboveTarget(void) {
    GpaResult cur;
    cur.courseCount = 3; cur.incompleteCount = 0;
    cur.totalCredits = 9.0; cur.weightedSum = 36.0; cur.cgpa = 4.00;
    RequiredGpaResult r = computeRequiredGPA(cur, 5.0, 3.50);
    return dEq(r.requiredGPA, 2.60) && r.isAchievable == 1;
}

/* Zero remaining credits → undefined (-1) */
static int testZeroRemaining(void) {
    GpaResult cur = makeCurrentGPA();
    RequiredGpaResult r = computeRequiredGPA(cur, 0.0, 3.75);
    return dEq(r.requiredGPA, -1.0);
}

/* Fields are stored correctly */
static int testFieldsStored(void) {
    GpaResult cur = makeCurrentGPA();
    RequiredGpaResult r = computeRequiredGPA(cur, 8.0, 3.60);
    return dEq(r.targetCGPA, 3.60) && dEq(r.remainingCredits, 8.0);
}

/*
 * Negative requiredGPA (target so low it's already guaranteed):
 *   current: totalCredits=10, weightedSum=40 (CGPA=4.00)
 *   remaining=5, target=2.00
 *   requiredGPA = (2.00 * 15 - 40) / 5 = (30 - 40) / 5 = -2.00
 *   → isAchievable = 1 (since -2.00 <= 4.00)
 */
static int testNegativeRequired(void) {
    GpaResult cur;
    cur.courseCount = 3; cur.incompleteCount = 0;
    cur.totalCredits = 10.0; cur.weightedSum = 40.0; cur.cgpa = 4.00;
    RequiredGpaResult r = computeRequiredGPA(cur, 5.0, 2.00);
    return (r.requiredGPA < 0.0) && r.isAchievable == 1;
}

int main(void) {
    printf("Required GPA module tests\n");
    printf("─────────────────────────────────────\n");
    check("Achievable: requiredGPA = 4.00",              testAchievableExact());
    check("Not achievable: requiredGPA > 4.00",          testNotAchievable());
    check("Already above target: requiredGPA = 2.60",    testAlreadyAboveTarget());
    check("Zero remaining credits → -1 (undefined)",    testZeroRemaining());
    check("Fields targetCGPA/remainingCredits stored",   testFieldsStored());
    check("Negative requiredGPA → isAchievable = 1",     testNegativeRequired());
    printf("─────────────────────────────────────\n");
    printf("Passed %d/%d tests\n", passed, total);
    return (passed == total) ? 0 : 1;
}
