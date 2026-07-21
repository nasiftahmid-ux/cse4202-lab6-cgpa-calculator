#include <stdio.h>
#include "modules/course.h"
#include "modules/courseResult.h"
#include "modules/gpa.h"

int main() {
    printf("In IUT, CGPA Matters!\n");
    printf("=====================================\n\n");

    /* ── Feature 001: Course module ──────────────────────────────── */
    printf("--- Course ---\n");
    Course c1 = createCourse("CSE 4202", "Structured Programming II", 3.0);
    viewCourse(c1);

    printf("\n");

    /* ── Feature 002: CourseResult module ────────────────────────── */
    printf("--- Course Result ---\n");
    CourseResult cr1 = createCourseResult(c1, 87.5);
    viewCourseResult(cr1);

    printf("\n");

    /* ── Feature 003: CGPA Calculator ────────────────────────────── */
    printf("--- CGPA Calculation ---\n");
    Course c2 = createCourse("MAT 4201", "Engineering Mathematics III", 2.0);
    Course c3 = createCourse("PHY 4201", "Physics I", 3.0);
    Course c4 = createCourse("HUM 4201", "Engineering Ethics", 2.0);

    CourseResult results[5];
    results[0] = createCourseResult(c1, 87.5); /* A   3.75 x 3 = 11.25 */
    results[1] = createCourseResult(c2, 72.0); /* B   3.00 x 2 =  6.00 */
    results[2] = createCourseResult(c3, 91.0); /* A+  4.00 x 3 = 12.00 */
    results[3] = createCourseResult(c4, 65.0); /* B-  2.75 x 2 =  5.50 */

    printf("\n%-10s %-34s %6s %7s %4s %6s\n",
           "Code", "Name", "Credit", "Marks", "Gr", "GP");
    printf("%-10s %-34s %6s %7s %4s %6s\n",
           "----------","----------------------------------","------","-------","----","------");

    for (int i = 0; i < 4; i++) {
        printf("%-10s %-34s %6.1f %7.2f %4s %6.2f\n",
               results[i].course.code, results[i].course.name,
               results[i].course.credit, results[i].marks,
               results[i].grade, results[i].gradePoint);
    }
    printf("\n");
    GpaResult gpa1 = computeGPA(results, 4);
    viewGPA(gpa1);

    /* ── Feature 004: Incomplete Course ──────────────────────────── */
    printf("\n--- Incomplete Course Handling ---\n");
    Course c5 = createCourse("CSE 4204", "Operating Systems", 3.0);
    results[4] = createCourseResult(c5, 0.0);
    markIncomplete(&results[4]);

    printf("\n%-10s %-34s %6s %12s\n", "Code", "Name", "Credit", "Status");
    printf("%-10s %-34s %6s %12s\n","----------","----------------------------------","------","------------");
    for (int i = 0; i < 5; i++) {
        printf("%-10s %-34s %6.1f %12s\n",
               results[i].course.code, results[i].course.name,
               results[i].course.credit,
               results[i].isIncomplete ? "Incomplete" : results[i].grade);
    }

    printf("\nCGPA (excluding incomplete):\n");
    GpaResult gpa2 = computeGPA(results, 5);
    viewGPA(gpa2);

    return 0;
}