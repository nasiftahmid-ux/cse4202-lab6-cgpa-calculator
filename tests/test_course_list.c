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

/* Empty list on creation */
static int testCreateEmpty(void) {
    CourseList list = createCourseList();
    int ok = (list.count == 0 && list.capacity == COURSE_LIST_INITIAL_CAPACITY
              && list.items != NULL);
    freeCourseList(&list);
    return ok;
}

/* Single add */
static int testAddOne(void) {
    CourseList list = createCourseList();
    Course c = createCourse("C1", "Test", 3.0);
    CourseResult cr = createCourseResult(c, 90.0);
    addCourseResult(&list, cr);
    int ok = (list.count == 1);
    freeCourseList(&list);
    return ok;
}

/* getCourseResult retrieves correct item */
static int testGetItem(void) {
    CourseList list = createCourseList();
    Course c = createCourse("CSE 4202", "SP II", 3.0);
    CourseResult cr = createCourseResult(c, 87.5);
    addCourseResult(&list, cr);
    CourseResult got = getCourseResult(&list, 0);
    int ok = (got.gradePoint == 3.75);
    freeCourseList(&list);
    return ok;
}

/* Dynamic growth: add more than initial capacity */
static int testDynamicGrowth(void) {
    CourseList list = createCourseList();
    Course c = createCourse("C1", "Test", 1.0);
    for (int i = 0; i < 10; i++) {
        CourseResult cr = createCourseResult(c, 90.0);
        addCourseResult(&list, cr);
    }
    int ok = (list.count == 10 && list.capacity >= 10);
    freeCourseList(&list);
    return ok;
}

/* freeCourseList nulls the pointer and resets fields */
static int testFree(void) {
    CourseList list = createCourseList();
    freeCourseList(&list);
    return (list.items == NULL && list.count == 0 && list.capacity == 0);
}

/*
 * computeGPAFromList:
 *   A (3.75 x 3) + B (3.00 x 2) + A+ (4.00 x 3) = 29.25 / 8 = 3.65625
 */
static int testComputeGPAFromList(void) {
    CourseList list = createCourseList();
    Course c1 = createCourse("C1", "Course A", 3.0);
    Course c2 = createCourse("C2", "Course B", 2.0);
    Course c3 = createCourse("C3", "Course C", 3.0);
    addCourseResult(&list, createCourseResult(c1, 87.5));
    addCourseResult(&list, createCourseResult(c2, 72.0));
    addCourseResult(&list, createCourseResult(c3, 91.0));
    GpaResult gpa = computeGPAFromList(&list);
    int ok = dEq(gpa.cgpa, 29.25 / 8.0)
          && dEq(gpa.totalCredits, 8.0)
          && gpa.courseCount == 3;
    freeCourseList(&list);
    return ok;
}

/* Incomplete items in list are still excluded */
static int testListWithIncomplete(void) {
    CourseList list = createCourseList();
    Course c1 = createCourse("C1", "A", 3.0);
    Course c2 = createCourse("C2", "B", 2.0);
    CourseResult cr1 = createCourseResult(c1, 90.0);
    CourseResult cr2 = createCourseResult(c2, 0.0);
    markIncomplete(&cr2);
    addCourseResult(&list, cr1);
    addCourseResult(&list, cr2);
    GpaResult gpa = computeGPAFromList(&list);
    int ok = dEq(gpa.cgpa, 4.00) && gpa.incompleteCount == 1;
    freeCourseList(&list);
    return ok;
}

int main(void) {
    printf("Dynamic Course List module tests\n");
    printf("─────────────────────────────────────\n");
    check("createCourseList returns empty list",        testCreateEmpty());
    check("addCourseResult increments count",           testAddOne());
    check("getCourseResult returns correct item",       testGetItem());
    check("Dynamic growth beyond initial capacity",     testDynamicGrowth());
    check("freeCourseList nulls pointer and resets",    testFree());
    check("computeGPAFromList correct CGPA",            testComputeGPAFromList());
    check("Incomplete items excluded in list GPA",      testListWithIncomplete());
    printf("─────────────────────────────────────\n");
    printf("Passed %d/%d tests\n", passed, total);
    return (passed == total) ? 0 : 1;
}
