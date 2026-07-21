#include <stdio.h>
#include <math.h>
#include <string.h>
#include "../modules/course.h"
#include "../modules/courseResult.h"
#include "../modules/courseList.h"
#include "../modules/gpa.h"
#include "../modules/student.h"
#include "../modules/studentList.h"

static int passed = 0;
static int total = 0;
#define EPSILON 1e-9

static int dEq(double a, double b) {
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

static int testCreateStudentInitializesState(void) {
    Student student = createStudent("S001", "Alice");
    return strcmp(student.id, "S001") == 0
        && strcmp(student.name, "Alice") == 0
        && student.courseList.count == 0
        && dEq(student.gpa.cgpa, 0.0);
}

static int testAddCourseAndComputeStudentGPA(void) {
    Student student = createStudent("S002", "Bob");
    Course c1 = createCourse("CSE 4202", "Structured Programming II", 3.0);
    Course c2 = createCourse("MAT 4201", "Engineering Mathematics III", 2.0);
    addCourseToStudent(&student, createCourseResult(c1, 87.5));
    addCourseToStudent(&student, createCourseResult(c2, 72.0));
    computeStudentGPA(&student);

    return student.courseList.count == 2
        && dEq(student.gpa.cgpa, 17.25 / 5.0)
        && dEq(student.gpa.totalCredits, 5.0);
}

static int testStudentListAppendAndAccess(void) {
    StudentList list = createStudentList();
    Student s1 = createStudent("S001", "Alice");
    Student s2 = createStudent("S002", "Bob");
    addStudent(&list, s1);
    addStudent(&list, s2);
    Student *got = getStudent(&list, 1);

    int ok = list.count == 2 && strcmp(got->name, "Bob") == 0;
    freeStudentList(&list);
    return ok;
}

static int testRankingSortsByHighestCGPA(void) {
    StudentList list = createStudentList();
    Student s1 = createStudent("S001", "Alice");
    Student s2 = createStudent("S002", "Bob");
    Student s3 = createStudent("S003", "Cara");

    Course c1 = createCourse("C1", "A", 3.0);
    Course c2 = createCourse("C2", "B", 2.0);
    Course c3 = createCourse("C3", "C", 3.0);

    addCourseToStudent(&s1, createCourseResult(c1, 90.0));
    addCourseToStudent(&s1, createCourseResult(c2, 60.0));
    computeStudentGPA(&s1);

    addCourseToStudent(&s2, createCourseResult(c1, 80.0));
    addCourseToStudent(&s2, createCourseResult(c2, 70.0));
    computeStudentGPA(&s2);

    addCourseToStudent(&s3, createCourseResult(c3, 95.0));
    computeStudentGPA(&s3);

    addStudent(&list, s1);
    addStudent(&list, s2);
    addStudent(&list, s3);

    rankStudentsByCGPA(&list);

    Student *top = getStudent(&list, 0);
    int ok = strcmp(top->name, "Cara") == 0 && top->gpa.cgpa >= getStudent(&list, 1)->gpa.cgpa;
    freeStudentList(&list);
    return ok;
}

static int testRankingIsStableOnTies(void) {
    StudentList list = createStudentList();
    Student s1 = createStudent("S001", "Alice");
    Student s2 = createStudent("S002", "Bob");
    Course c1 = createCourse("C1", "A", 3.0);

    /* Same marks -> same CGPA -> tie */
    addCourseToStudent(&s1, createCourseResult(c1, 80.0));
    computeStudentGPA(&s1);
    addCourseToStudent(&s2, createCourseResult(c1, 80.0));
    computeStudentGPA(&s2);

    addStudent(&list, s1); /* inserted first */
    addStudent(&list, s2); /* inserted second */
    rankStudentsByCGPA(&list);

    /* On a tie, original insertion order (Alice before Bob) must hold */
    int ok = strcmp(getStudent(&list, 0)->name, "Alice") == 0
           && strcmp(getStudent(&list, 1)->name, "Bob") == 0;
    freeStudentList(&list);
    return ok;
}

static int testRankingHandlesSingleAndEmptyList(void) {
    StudentList empty = createStudentList();
    rankStudentsByCGPA(&empty); /* must not crash on count == 0 */
    int emptyOk = empty.count == 0;
    freeStudentList(&empty);

    StudentList single = createStudentList();
    Student s = createStudent("S001", "Alice");
    addStudent(&single, s);
    rankStudentsByCGPA(&single); /* must not crash on count == 1 */
    int singleOk = single.count == 1 && strcmp(getStudent(&single, 0)->name, "Alice") == 0;
    freeStudentList(&single);

    return emptyOk && singleOk;
}

int main(void) {
    printf("Student module tests\n");
    printf("─────────────────────────────────────\n");
    check("Create student initializes id/name and GPA", testCreateStudentInitializesState());
    check("Add course and compute student CGPA", testAddCourseAndComputeStudentGPA());
    check("Student list append and access", testStudentListAppendAndAccess());
    check("Ranking sorts students by highest CGPA", testRankingSortsByHighestCGPA());
    check("Ranking is stable on CGPA ties", testRankingIsStableOnTies());
    check("Ranking handles single/empty lists safely", testRankingHandlesSingleAndEmptyList());
    printf("─────────────────────────────────────\n");
    printf("Passed %d/%d tests\n", passed, total);
    return (passed == total) ? 0 : 1;
}
