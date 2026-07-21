#include <stdio.h>
#include "modules/course.h"
#include "modules/courseResult.h"
#include "modules/gpa.h"

int main() {
    printf("In IUT, CGPA Matters!\n");
    printf("=====================================\n\n");

    /* ── Feature 001 & 002: Course / CourseResult demo ───────────── */
    printf("--- Course & Course Result ---\n");
    Course c1 = createCourse("CSE 4202", "Structured Programming II", 3.0);
    CourseResult cr1 = createCourseResult(c1, 87.5);
    viewCourseResult(cr1);

    /* ── Build transcript (5 courses, 2 semesters) ───────────────── */
    Course c2 = createCourse("MAT 4201", "Engineering Mathematics III", 2.0);
    Course c3 = createCourse("PHY 4201", "Physics I",                   3.0);
    Course c4 = createCourse("HUM 4201", "Engineering Ethics",          2.0);
    Course c5 = createCourse("CSE 4204", "Operating Systems",           3.0);

    CourseResult results[5];
    /* Semester 1 */
    results[0] = createCourseResult(c1, 87.5);
    results[1] = createCourseResult(c2, 72.0);
    /* Semester 2 */
    results[2] = createCourseResult(c3, 91.0); setSemester(&results[2], 2);
    results[3] = createCourseResult(c4, 65.0); setSemester(&results[3], 2);
    /* Semester 2 — incomplete */
    results[4] = createCourseResult(c5, 0.0);  setSemester(&results[4], 2);
    markIncomplete(&results[4]);

    /* ── Feature 003 & 004: CGPA (incomplete excluded) ───────────── */
    printf("\n--- Overall CGPA (incomplete excluded) ---\n");
    printf("\n%-10s %-30s %4s %7s %4s %4s\n",
           "Code", "Name", "Sem", "Marks", "Gr", "GP");
    printf("%-10s %-30s %4s %7s %4s %4s\n",
           "----------","------------------------------","----","-------","----","----");
    for (int i = 0; i < 5; i++) {
        if (results[i].isIncomplete)
            printf("%-10s %-30s %4d %7s %4s %4s\n",
                   results[i].course.code, results[i].course.name,
                   results[i].semester, "---", "INC", "---");
        else
            printf("%-10s %-30s %4d %7.2f %4s %4.2f\n",
                   results[i].course.code, results[i].course.name,
                   results[i].semester, results[i].marks,
                   results[i].grade, results[i].gradePoint);
    }
    printf("\n");
    GpaResult overall = computeGPA(results, 5);
    viewGPA(overall);

    /* ── Feature 005: Per-semester GPA ───────────────────────────── */
    printf("\n--- Semester 1 GPA ---\n");
    GpaResult s1 = computeSemesterGPA(results, 5, 1);
    viewSemesterGPA(s1, 1);

    printf("\n--- Semester 2 GPA (incomplete excluded) ---\n");
    GpaResult s2 = computeSemesterGPA(results, 5, 2);
    viewSemesterGPA(s2, 2);

    return 0;
}