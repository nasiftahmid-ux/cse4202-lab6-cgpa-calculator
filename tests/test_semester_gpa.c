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

/* ── fixtures ────────────────────────────────────────────────────────────── */
/*
 * Semester 1:
 *   CSE 4202  3cr  A   3.75  → weighted 11.25
 *   MAT 4201  2cr  B   3.00  → weighted  6.00
 *   S1 total: 5cr, 17.25, GPA = 3.45
 *
 * Semester 2:
 *   PHY 4201  3cr  A+  4.00  → weighted 12.00
 *   HUM 4201  2cr  B-  2.75  → weighted  5.50
 *   S2 total: 5cr, 17.50, GPA = 3.50
 *
 * Overall: 10cr, 34.75, CGPA = 3.475
 */
static void buildFixture(CourseResult out[4]) {
    Course c1 = createCourse("CSE 4202", "Structured Programming II",   3.0);
    Course c2 = createCourse("MAT 4201", "Engineering Mathematics III",  2.0);
    Course c3 = createCourse("PHY 4201", "Physics I",                    3.0);
    Course c4 = createCourse("HUM 4201", "Engineering Ethics",           2.0);
    out[0] = createCourseResult(c1, 87.5); /* semester 1 */
    out[1] = createCourseResult(c2, 72.0); /* semester 1 */
    out[2] = createCourseResult(c3, 91.0); setSemester(&out[2], 2);
    out[3] = createCourseResult(c4, 65.0); setSemester(&out[3], 2);
}

/* ── tests ───────────────────────────────────────────────────────────────── */

static int testDefaultSemester(void) {
    Course c = createCourse("C1", "Test", 3.0);
    CourseResult cr = createCourseResult(c, 80.0);
    return cr.semester == 1;
}

static int testSetSemester(void) {
    Course c = createCourse("C1", "Test", 3.0);
    CourseResult cr = createCourseResult(c, 80.0);
    setSemester(&cr, 3);
    return cr.semester == 3;
}

/* Semester 1 GPA = 17.25 / 5.0 = 3.45 */
static int testSemester1GPA(void) {
    CourseResult r[4];
    buildFixture(r);
    GpaResult gpa = computeSemesterGPA(r, 4, 1);
    return dEq(gpa.cgpa, 17.25 / 5.0)
        && dEq(gpa.totalCredits, 5.0)
        && gpa.courseCount == 2;
}

/* Semester 2 GPA = 17.50 / 5.0 = 3.50 */
static int testSemester2GPA(void) {
    CourseResult r[4];
    buildFixture(r);
    GpaResult gpa = computeSemesterGPA(r, 4, 2);
    return dEq(gpa.cgpa, 17.50 / 5.0)
        && dEq(gpa.totalCredits, 5.0)
        && gpa.courseCount == 2;
}

/* Querying a semester with no courses → GPA = 0, courseCount = 0 */
static int testEmptySemester(void) {
    CourseResult r[4];
    buildFixture(r);
    GpaResult gpa = computeSemesterGPA(r, 4, 9);
    return dEq(gpa.cgpa, 0.0)
        && gpa.courseCount == 0;
}

/* Incomplete courses in a semester are excluded from that semester's GPA */
static int testSemesterWithIncomplete(void) {
    Course c1 = createCourse("C1", "A", 3.0);
    Course c2 = createCourse("C2", "B", 2.0);
    CourseResult r[2];
    r[0] = createCourseResult(c1, 90.0); /* A+ 4.00 x 3 = 12 */
    r[1] = createCourseResult(c2, 0.0);
    markIncomplete(&r[1]);
    /* both in semester 1 (default) */

    GpaResult gpa = computeSemesterGPA(r, 2, 1);
    return dEq(gpa.cgpa, 4.00)
        && gpa.courseCount     == 2
        && gpa.incompleteCount == 1
        && dEq(gpa.totalCredits, 3.0);
}

/* computeGPA (overall) still sees all semesters */
static int testOverallGPA(void) {
    CourseResult r[4];
    buildFixture(r);
    GpaResult gpa = computeGPA(r, 4);
    return dEq(gpa.cgpa, 34.75 / 10.0)
        && gpa.courseCount == 4;
}

/* ── main ────────────────────────────────────────────────────────────────── */
int main(void) {
    printf("Semester GPA module tests\n");
    printf("─────────────────────────────────────\n");
    check("Default semester = 1",                         testDefaultSemester());
    check("setSemester changes field correctly",          testSetSemester());
    check("Semester 1 GPA = 3.45",                        testSemester1GPA());
    check("Semester 2 GPA = 3.50",                        testSemester2GPA());
    check("Empty semester → GPA = 0, courseCount = 0",    testEmptySemester());
    check("Incomplete excluded within semester",          testSemesterWithIncomplete());
    check("Overall computeGPA spans all semesters",       testOverallGPA());
    printf("─────────────────────────────────────\n");
    printf("Passed %d/%d tests\n", passed, total);
    return (passed == total) ? 0 : 1;
}
