#include <stdio.h>
#include "modules/course.h"
#include "modules/courseResult.h"
#include "modules/courseList.h"
#include "modules/gpa.h"

int main() {
    printf("In IUT, CGPA Matters!\n");
    printf("=====================================\n\n");

    /* ── Build transcript ────────────────────────────────────────── */
    CourseList transcript = createCourseList();

    Course c1 = createCourse("CSE 4202", "Structured Programming II",   3.0);
    Course c2 = createCourse("MAT 4201", "Engineering Mathematics III",  2.0);
    Course c3 = createCourse("PHY 4201", "Physics I",                    3.0);
    Course c4 = createCourse("HUM 4201", "Engineering Ethics",           2.0);

    CourseResult cr1 = createCourseResult(c1, 87.5);
    CourseResult cr2 = createCourseResult(c2, 72.0);
    CourseResult cr3 = createCourseResult(c3, 91.0); setSemester(&cr3, 2);
    CourseResult cr4 = createCourseResult(c4, 65.0); setSemester(&cr4, 2);

    addCourseResult(&transcript, cr1);
    addCourseResult(&transcript, cr2);
    addCourseResult(&transcript, cr3);
    addCourseResult(&transcript, cr4);

    printf("--- Current Transcript ---\n\n");
    viewCourseList(&transcript);

    GpaResult current = computeGPAFromList(&transcript);
    printf("\n--- Current CGPA ---\n");
    viewGPA(current);

    /* ── Feature 005: Per-semester GPA ───────────────────────────── */
    printf("\n--- Semester 1 GPA ---\n");
    viewSemesterGPA(computeSemesterGPA(transcript.items, transcript.count, 1), 1);
    printf("\n--- Semester 2 GPA ---\n");
    viewSemesterGPA(computeSemesterGPA(transcript.items, transcript.count, 2), 2);

    /* ── Feature 007: Required GPA ───────────────────────────────── */
    printf("\n--- Required GPA Calculator ---\n");
    printf("\nTo achieve CGPA 3.75 with 10 remaining credits:\n");
    RequiredGpaResult req1 = computeRequiredGPA(current, 10.0, 3.75);
    viewRequiredGPA(req1);

    printf("\nTo achieve CGPA 3.75 with 6 remaining credits:\n");
    RequiredGpaResult req2 = computeRequiredGPA(current, 6.0, 3.75);
    viewRequiredGPA(req2);

    printf("\nTo achieve CGPA 3.00 with 5 remaining credits (easy target):\n");
    RequiredGpaResult req3 = computeRequiredGPA(current, 5.0, 3.00);
    viewRequiredGPA(req3);

    freeCourseList(&transcript);
    return 0;
}