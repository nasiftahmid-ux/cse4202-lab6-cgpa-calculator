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

/* ── fixtures ────────────────────────────────────────────────────────────── */
/*
 * Completed: A (3.75×3) + B (3.00×2) = 17.25 / 5cr = 3.45
 * Upcoming:  A+ (4.00×3) + A- (3.50×2) = 19.00 / 5cr
 * Combined:  36.25 / 10cr = 3.625
 */
static CourseList makeCompleted(void) {
    CourseList list = createCourseList();
    Course c1 = createCourse("C1", "Course A", 3.0);
    Course c2 = createCourse("C2", "Course B", 2.0);
    addCourseResult(&list, createCourseResult(c1, 87.5)); /* A  3.75 */
    addCourseResult(&list, createCourseResult(c2, 72.0)); /* B  3.00 */
    return list;
}

static CourseList makeUpcoming(void) {
    CourseList list = createCourseList();
    Course c3 = createCourse("C3", "Course C", 3.0);
    Course c4 = createCourse("C4", "Course D", 2.0);
    addCourseResult(&list, createCourseResult(c3, 91.0)); /* A+ 4.00 */
    addCourseResult(&list, createCourseResult(c4, 82.0)); /* A- 3.50 */
    return list;
}

/* ── tests ───────────────────────────────────────────────────────────────── */

/* Both empty → CGPA = 0 */
static int testBothEmpty(void) {
    CourseList c = createCourseList();
    CourseList u = createCourseList();
    GpaResult r = computeExpectedGPA(&c, &u);
    int ok = dEq(r.cgpa, 0.0) && r.courseCount == 0;
    freeCourseList(&c);
    freeCourseList(&u);
    return ok;
}

/* No upcoming → same as current */
static int testNoUpcoming(void) {
    CourseList completed = makeCompleted();
    CourseList upcoming  = createCourseList();
    GpaResult expected   = computeExpectedGPA(&completed, &upcoming);
    GpaResult current    = computeGPAFromList(&completed);
    int ok = dEq(expected.cgpa, current.cgpa);
    freeCourseList(&completed);
    freeCourseList(&upcoming);
    return ok;
}

/* No completed → same as upcoming GPA */
static int testNoCompleted(void) {
    CourseList completed = createCourseList();
    CourseList upcoming  = makeUpcoming();
    GpaResult expected   = computeExpectedGPA(&completed, &upcoming);
    GpaResult upGpa      = computeGPAFromList(&upcoming);
    int ok = dEq(expected.cgpa, upGpa.cgpa);
    freeCourseList(&completed);
    freeCourseList(&upcoming);
    return ok;
}

/* Combined: 36.25 / 10 = 3.625 */
static int testCombinedGPA(void) {
    CourseList completed = makeCompleted();
    CourseList upcoming  = makeUpcoming();
    GpaResult expected   = computeExpectedGPA(&completed, &upcoming);
    /* 3.75*3 + 3.00*2 + 4.00*3 + 3.50*2 = 11.25+6+12+7 = 36.25 */
    int ok = dEq(expected.cgpa, 36.25 / 10.0)
          && expected.courseCount == 4
          && dEq(expected.totalCredits, 10.0);
    freeCourseList(&completed);
    freeCourseList(&upcoming);
    return ok;
}

/* High upcoming marks improve CGPA */
static int testUpcomingImproves(void) {
    CourseList completed = makeCompleted(); /* cgpa = 3.45 */
    CourseList upcoming  = makeUpcoming();  /* A+, A- */
    GpaResult current    = computeGPAFromList(&completed);
    GpaResult expected   = computeExpectedGPA(&completed, &upcoming);
    int ok = expected.cgpa > current.cgpa;
    freeCourseList(&completed);
    freeCourseList(&upcoming);
    return ok;
}

/* Low upcoming marks worsen CGPA */
static int testUpcomingWorsens(void) {
    CourseList completed = makeCompleted(); /* cgpa = 3.45 */
    CourseList upcoming  = createCourseList();
    Course c = createCourse("CX", "Fail", 3.0);
    addCourseResult(&upcoming, createCourseResult(c, 20.0)); /* F 0.00 */
    GpaResult current  = computeGPAFromList(&completed);
    GpaResult expected = computeExpectedGPA(&completed, &upcoming);
    int ok = expected.cgpa < current.cgpa;
    freeCourseList(&completed);
    freeCourseList(&upcoming);
    return ok;
}

int main(void) {
    printf("Expected CGPA module tests\n");
    printf("─────────────────────────────────────\n");
    check("Both empty → CGPA = 0",                        testBothEmpty());
    check("No upcoming → same as current CGPA",           testNoUpcoming());
    check("No completed → same as upcoming GPA",          testNoCompleted());
    check("Combined: 36.25 / 10 = 3.625",                 testCombinedGPA());
    check("High upcoming marks improve projected CGPA",   testUpcomingImproves());
    check("Low upcoming marks worsen projected CGPA",     testUpcomingWorsens());
    printf("─────────────────────────────────────\n");
    printf("Passed %d/%d tests\n", passed, total);
    return (passed == total) ? 0 : 1;
}
