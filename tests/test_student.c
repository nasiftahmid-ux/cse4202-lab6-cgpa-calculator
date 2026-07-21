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

int main(void) {
    printf("Student module tests\n");
    printf("─────────────────────────────────────\n");
    check("Create student initializes id/name and GPA", testCreateStudentInitializesState());
    check("Add course and compute student CGPA", testAddCourseAndComputeStudentGPA());
    check("Student list append and access", testStudentListAppendAndAccess());
    printf("─────────────────────────────────────\n");
    printf("Passed %d/%d tests\n", passed, total);
    return (passed == total) ? 0 : 1;
}
