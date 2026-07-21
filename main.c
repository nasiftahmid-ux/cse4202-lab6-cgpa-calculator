#include <stdio.h>
#include "modules/course.h"
#include "modules/courseResult.h"

int main() {
    printf("In IUT, CGPA Matters!\n");
    printf("=====================================\n\n");

    /* ── Feature 001: Course module demo ─────────────────────────── */
    printf("--- Course ---\n");
    Course c1 = createCourse("CSE 4202", "Structured Programming II", 3.0);
    viewCourse(c1);

    printf("\n");

    /* ── Feature 002: CourseResult module demo ───────────────────── */
    printf("--- Course Result ---\n");
    CourseResult cr1 = createCourseResult(c1, 87.5);
    viewCourseResult(cr1);

    printf("\n");

    /* Second example: a failing grade */
    printf("--- Course Result (Fail case) ---\n");
    Course c2 = createCourse("MAT 4201", "Engineering Mathematics III", 2.0);
    CourseResult cr2 = createCourseResult(c2, 45.0);
    viewCourseResult(cr2);

    return 0;
}