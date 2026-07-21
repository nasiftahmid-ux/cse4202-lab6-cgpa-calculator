#include <stdio.h>
#include <string.h>
#include "../modules/course.h"
#include "../modules/courseResult.h"

/* ── helpers ─────────────────────────────────────────────────────────────── */

static int passed = 0;
static int total  = 0;

static void check(const char *name, int result) {
    total++;
    if (result) {
        passed++;
        printf("  [PASS] %s\n", name);
    } else {
        printf("  [FAIL] %s\n", name);
    }
}

/* ── boundary tests ──────────────────────────────────────────────────────── */

static Course dummyCourse(void) {
    return createCourse("TST 0000", "Test Course", 3.0);
}

static int testGradeAPlus(void) {
    CourseResult cr = createCourseResult(dummyCourse(), 90.0);
    return strcmp(cr.grade, "A+") == 0 && cr.gradePoint == 4.00;
}

static int testGradeA(void) {
    CourseResult cr = createCourseResult(dummyCourse(), 87.0);
    return strcmp(cr.grade, "A") == 0 && cr.gradePoint == 3.75;
}

static int testGradeAMinus(void) {
    CourseResult cr = createCourseResult(dummyCourse(), 82.5);
    return strcmp(cr.grade, "A-") == 0 && cr.gradePoint == 3.50;
}

static int testGradeBPlus(void) {
    CourseResult cr = createCourseResult(dummyCourse(), 75.0);
    return strcmp(cr.grade, "B+") == 0 && cr.gradePoint == 3.25;
}

static int testGradeB(void) {
    CourseResult cr = createCourseResult(dummyCourse(), 72.0);
    return strcmp(cr.grade, "B") == 0 && cr.gradePoint == 3.00;
}

static int testGradeBMinus(void) {
    CourseResult cr = createCourseResult(dummyCourse(), 65.0);
    return strcmp(cr.grade, "B-") == 0 && cr.gradePoint == 2.75;
}

static int testGradeCPlus(void) {
    CourseResult cr = createCourseResult(dummyCourse(), 62.0);
    return strcmp(cr.grade, "C+") == 0 && cr.gradePoint == 2.50;
}

static int testGradeC(void) {
    CourseResult cr = createCourseResult(dummyCourse(), 57.0);
    return strcmp(cr.grade, "C") == 0 && cr.gradePoint == 2.25;
}

static int testGradeD(void) {
    CourseResult cr = createCourseResult(dummyCourse(), 50.0);
    return strcmp(cr.grade, "D") == 0 && cr.gradePoint == 2.00;
}

static int testGradeF(void) {
    CourseResult cr = createCourseResult(dummyCourse(), 49.9);
    return strcmp(cr.grade, "F") == 0 && cr.gradePoint == 0.00;
}

static int testGradeFAtZero(void) {
    CourseResult cr = createCourseResult(dummyCourse(), 0.0);
    return strcmp(cr.grade, "F") == 0 && cr.gradePoint == 0.00;
}

static int testGradeAPlusAt100(void) {
    CourseResult cr = createCourseResult(dummyCourse(), 100.0);
    return strcmp(cr.grade, "A+") == 0 && cr.gradePoint == 4.00;
}

static int testMarksStored(void) {
    CourseResult cr = createCourseResult(dummyCourse(), 78.5);
    return cr.marks == 78.5;
}

static int testCoursePassedThrough(void) {
    Course c = createCourse("CSE 4202", "SP II", 3.0);
    CourseResult cr = createCourseResult(c, 91.0);
    return strcmp(cr.course.code, "CSE 4202") == 0
        && strcmp(cr.course.name, "SP II")     == 0
        && cr.course.credit == 3.0;
}

/* ── main ────────────────────────────────────────────────────────────────── */

int main(void) {
    printf("CourseResult module tests\n");
    printf("─────────────────────────────────────\n");

    check("Grade A+ (marks=90.0)",          testGradeAPlus());
    check("Grade A  (marks=87.0)",           testGradeA());
    check("Grade A- (marks=82.5)",           testGradeAMinus());
    check("Grade B+ (marks=75.0)",           testGradeBPlus());
    check("Grade B  (marks=72.0)",           testGradeB());
    check("Grade B- (marks=65.0)",           testGradeBMinus());
    check("Grade C+ (marks=62.0)",           testGradeCPlus());
    check("Grade C  (marks=57.0)",           testGradeC());
    check("Grade D  (marks=50.0)",           testGradeD());
    check("Grade F  (marks=49.9 boundary)", testGradeF());
    check("Grade F  (marks=0.0)",            testGradeFAtZero());
    check("Grade A+ (marks=100.0 max)",     testGradeAPlusAt100());
    check("Marks value stored correctly",   testMarksStored());
    check("Course data passed through",     testCoursePassedThrough());

    printf("─────────────────────────────────────\n");
    printf("Passed %d/%d tests\n", passed, total);

    return (passed == total) ? 0 : 1;
}
