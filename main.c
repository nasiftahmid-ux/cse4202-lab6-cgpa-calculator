#include <stdio.h>
#include "modules/course.h"
#include "modules/courseResult.h"
#include "modules/courseList.h"
#include "modules/gpa.h"

int main() {
    printf("In IUT, CGPA Matters!\n");
    printf("=====================================\n\n");

    /* ── Build transcript using dynamic CourseList (Feature 006) ─── */
    printf("--- Transcript (Dynamic Course List) ---\n\n");

    CourseList transcript = createCourseList();

    /* Semester 1 */
    Course c1 = createCourse("CSE 4202", "Structured Programming II",   3.0);
    Course c2 = createCourse("MAT 4201", "Engineering Mathematics III",  2.0);
    CourseResult cr1 = createCourseResult(c1, 87.5);
    CourseResult cr2 = createCourseResult(c2, 72.0);
    addCourseResult(&transcript, cr1);
    addCourseResult(&transcript, cr2);

    /* Semester 2 */
    Course c3 = createCourse("PHY 4201", "Physics I",          3.0);
    Course c4 = createCourse("HUM 4201", "Engineering Ethics", 2.0);
    CourseResult cr3 = createCourseResult(c3, 91.0); setSemester(&cr3, 2);
    CourseResult cr4 = createCourseResult(c4, 65.0); setSemester(&cr4, 2);
    addCourseResult(&transcript, cr3);
    addCourseResult(&transcript, cr4);

    /* Semester 2 — incomplete */
    Course c5 = createCourse("CSE 4204", "Operating Systems", 3.0);
    CourseResult cr5 = createCourseResult(c5, 0.0); setSemester(&cr5, 2);
    markIncomplete(&cr5);
    addCourseResult(&transcript, cr5);

    viewCourseList(&transcript);

    /* ── Features 003+004: Overall CGPA ──────────────────────────── */
    printf("\n--- Overall CGPA ---\n");
    GpaResult overall = computeGPAFromList(&transcript);
    viewGPA(overall);

    /* ── Feature 005: Per-semester GPA ───────────────────────────── */
    printf("\n--- Semester 1 GPA ---\n");
    GpaResult s1 = computeSemesterGPA(transcript.items, transcript.count, 1);
    viewSemesterGPA(s1, 1);

    printf("\n--- Semester 2 GPA ---\n");
    GpaResult s2 = computeSemesterGPA(transcript.items, transcript.count, 2);
    viewSemesterGPA(s2, 2);

    freeCourseList(&transcript);
    return 0;
}