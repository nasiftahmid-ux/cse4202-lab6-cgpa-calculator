#include <stdio.h>
#include <math.h>
#include "../modules/course.h"
#include "../modules/courseResult.h"
#include "../modules/gpa.h"

/* ── helpers ─────────────────────────────────────────────────────────────── */

static int passed = 0;
static int total  = 0;

/* Allow floating-point comparison with a tiny epsilon */
#define EPSILON 1e-9
static int doubleEq(double a, double b) {
    return fabs(a - b) < EPSILON;
}

static void check(const char *name, int result) {
    total++;
    if (result) {
        passed++;
        printf("  [PASS] %s\n", name);
    } else {
        printf("  [FAIL] %s\n", name);
    }
}

/* ── fixtures ────────────────────────────────────────────────────────────── */

/*
 * Fixture A — Three courses:
 *   CSE 4202 : 3.0 cr, marks=87.5  → A  (3.75) → weighted = 11.25
 *   MAT 4201 : 2.0 cr, marks=72.0  → B  (3.00) → weighted =  6.00
 *   PHY 4201 : 3.0 cr, marks=91.0  → A+ (4.00) → weighted = 12.00
 *   -----------------------------------------------
 *   total credits = 8.0
 *   weightedSum   = 29.25
 *   CGPA          = 29.25 / 8.0 = 3.65625
 */
static void buildFixtureA(CourseResult out[], int *count) {
    Course c1 = createCourse("CSE 4202", "Structured Programming II", 3.0);
    Course c2 = createCourse("MAT 4201", "Engineering Mathematics III", 2.0);
    Course c3 = createCourse("PHY 4201", "Physics I", 3.0);
    out[0] = createCourseResult(c1, 87.5);
    out[1] = createCourseResult(c2, 72.0);
    out[2] = createCourseResult(c3, 91.0);
    *count = 3;
}

/*
 * Fixture B — Single perfect course:
 *   ENG 0001 : 1.0 cr, marks=100.0 → A+ (4.00)
 *   CGPA = 4.00
 */
static void buildFixtureB(CourseResult out[], int *count) {
    Course c = createCourse("ENG 0001", "English", 1.0);
    out[0] = createCourseResult(c, 100.0);
    *count = 1;
}

/*
 * Fixture C — One pass, one fail:
 *   CSE 0001 : 3.0 cr, marks=90.0  → A+ (4.00) → weighted = 12.00
 *   CSE 0002 : 2.0 cr, marks=40.0  → F  (0.00) → weighted =  0.00
 *   CGPA = 12.00 / 5.0 = 2.40
 */
static void buildFixtureC(CourseResult out[], int *count) {
    Course c1 = createCourse("CSE 0001", "Course A", 3.0);
    Course c2 = createCourse("CSE 0002", "Course B", 2.0);
    out[0] = createCourseResult(c1, 90.0);
    out[1] = createCourseResult(c2, 40.0);
    *count = 2;
}

/* ── tests ───────────────────────────────────────────────────────────────── */

static int testEmptyArrayCgpa(void) {
    CourseResult dummy[1];
    GpaResult gpa = computeGPA(dummy, 0);
    return doubleEq(gpa.cgpa, 0.0)
        && doubleEq(gpa.totalCredits, 0.0)
        && doubleEq(gpa.weightedSum,  0.0)
        && gpa.courseCount == 0;
}

static int testSinglePerfectCourse(void) {
    CourseResult results[1];
    int count;
    buildFixtureB(results, &count);
    GpaResult gpa = computeGPA(results, count);
    return doubleEq(gpa.cgpa, 4.00)
        && doubleEq(gpa.totalCredits, 1.0)
        && gpa.courseCount == 1;
}

static int testThreeCourseCgpa(void) {
    CourseResult results[3];
    int count;
    buildFixtureA(results, &count);
    GpaResult gpa = computeGPA(results, count);
    /* Expected CGPA = 29.25 / 8.0 = 3.65625 */
    return doubleEq(gpa.cgpa, 29.25 / 8.0)
        && doubleEq(gpa.totalCredits, 8.0)
        && doubleEq(gpa.weightedSum,  29.25)
        && gpa.courseCount == 3;
}

static int testPassFailMix(void) {
    CourseResult results[2];
    int count;
    buildFixtureC(results, &count);
    GpaResult gpa = computeGPA(results, count);
    /* Expected CGPA = 12.00 / 5.0 = 2.40 */
    return doubleEq(gpa.cgpa, 2.40)
        && doubleEq(gpa.totalCredits, 5.0)
        && doubleEq(gpa.weightedSum,  12.0);
}

static int testAllFail(void) {
    Course c1 = createCourse("X 001", "Course X", 3.0);
    Course c2 = createCourse("X 002", "Course Y", 2.0);
    CourseResult results[2];
    results[0] = createCourseResult(c1, 10.0); /* F */
    results[1] = createCourseResult(c2, 0.0);  /* F */
    GpaResult gpa = computeGPA(results, 2);
    return doubleEq(gpa.cgpa, 0.00)
        && doubleEq(gpa.weightedSum, 0.0)
        && doubleEq(gpa.totalCredits, 5.0);
}

static int testAllPerfect(void) {
    Course c1 = createCourse("A 001", "Course A", 3.0);
    Course c2 = createCourse("A 002", "Course B", 3.0);
    Course c3 = createCourse("A 003", "Course C", 3.0);
    CourseResult results[3];
    results[0] = createCourseResult(c1, 95.0); /* A+ */
    results[1] = createCourseResult(c2, 91.0); /* A+ */
    results[2] = createCourseResult(c3, 90.0); /* A+ */
    GpaResult gpa = computeGPA(results, 3);
    return doubleEq(gpa.cgpa, 4.00)
        && doubleEq(gpa.totalCredits, 9.0)
        && doubleEq(gpa.weightedSum,  36.0);
}

static int testCourseCountStored(void) {
    CourseResult results[3];
    int count;
    buildFixtureA(results, &count);
    GpaResult gpa = computeGPA(results, count);
    return gpa.courseCount == 3;
}

/* ── main ────────────────────────────────────────────────────────────────── */

int main(void) {
    printf("GPA module tests\n");
    printf("─────────────────────────────────────\n");

    check("Empty array → CGPA = 0.00",                   testEmptyArrayCgpa());
    check("Single perfect course → CGPA = 4.00",         testSinglePerfectCourse());
    check("Three courses weighted CGPA (3.65625)",        testThreeCourseCgpa());
    check("Pass/Fail mix → CGPA = 2.40",                  testPassFailMix());
    check("All failed courses → CGPA = 0.00",            testAllFail());
    check("All perfect courses → CGPA = 4.00",           testAllPerfect());
    check("courseCount field stored correctly",           testCourseCountStored());

    printf("─────────────────────────────────────\n");
    printf("Passed %d/%d tests\n", passed, total);

    return (passed == total) ? 0 : 1;
}
