#include <stdio.h>
#include "modules/course.h"
#include "modules/courseResult.h"
#include "modules/courseList.h"
#include "modules/gpa.h"

int main() {
    printf("In IUT, CGPA Matters!\n");
    printf("=====================================\n\n");

    /* ── Completed courses ───────────────────────────────────────── */
    CourseList completed = createCourseList();
    Course c1 = createCourse("CSE 4202", "Structured Programming II",   3.0);
    Course c2 = createCourse("MAT 4201", "Engineering Mathematics III",  2.0);
    Course c3 = createCourse("PHY 4201", "Physics I",                    3.0);
    Course c4 = createCourse("HUM 4201", "Engineering Ethics",           2.0);
    CourseResult cr3 = createCourseResult(c3, 91.0); setSemester(&cr3, 2);
    CourseResult cr4 = createCourseResult(c4, 65.0); setSemester(&cr4, 2);
    addCourseResult(&completed, createCourseResult(c1, 87.5));
    addCourseResult(&completed, createCourseResult(c2, 72.0));
    addCourseResult(&completed, cr3);
    addCourseResult(&completed, cr4);

    printf("--- Completed Courses ---\n\n");
    viewCourseList(&completed);
    GpaResult current = computeGPAFromList(&completed);
    printf("\nCurrent CGPA: %.2f  (Credits: %.0f)\n",
           current.cgpa, current.totalCredits);

    /* ── Feature 007: Required GPA ───────────────────────────────── */
    printf("\n--- Required GPA to Achieve 3.75 (10 remaining credits) ---\n");
    RequiredGpaResult req = computeRequiredGPA(current, 10.0, 3.75);
    viewRequiredGPA(req);

    /* ── Feature 008: Expected CGPA ──────────────────────────────── */
    printf("\n--- Expected CGPA Calculator ---\n");
    CourseList upcoming = createCourseList();
    Course c5 = createCourse("CSE 4206", "Database Systems",    3.0);
    Course c6 = createCourse("CSE 4208", "Computer Networks",   3.0);
    Course c7 = createCourse("MAT 4203", "Numerical Methods",   2.0);
    /* Optimistic scenario: A+, A, B+ */
    addCourseResult(&upcoming, createCourseResult(c5, 92.0)); /* A+ 4.00 */
    addCourseResult(&upcoming, createCourseResult(c6, 86.0)); /* A  3.75 */
    addCourseResult(&upcoming, createCourseResult(c7, 76.0)); /* B+ 3.25 */

    printf("\nUpcoming courses (expected marks):\n\n");
    viewCourseList(&upcoming);
    printf("\nProjected result if these marks are achieved:\n");
    GpaResult projected = computeExpectedGPA(&completed, &upcoming);
    viewExpectedGPA(projected);

    freeCourseList(&completed);
    freeCourseList(&upcoming);
    return 0;
}