#include <stdio.h>
#include "modules/course.h"
#include "modules/courseResult.h"
#include "modules/courseList.h"
#include "modules/gpa.h"
#include "modules/student.h"
#include "modules/studentList.h"

/*
 * Interactive console menu (Feature 006 style).
 *
 * Course and CourseResult are fused in this project's design (a
 * CourseResult owns its Course directly, rather than pointing into a
 * separate array), so "Add/Edit/Delete/View Course" and
 * "Add/Edit/Delete/View Course Result" from the lab manual collapse
 * into a single set of course-result operations here.
 */

static void showMenu(void) {
    printf("\n=====================================\n");
    printf("        CGPA Calculator Menu\n");
    printf("=====================================\n");
    printf("1. Add Course Result\n");
    printf("2. Edit Course Result\n");
    printf("3. Delete Course Result\n");
    printf("4. View Marksheet\n");
    printf("5. Required GPA Calculator\n");
    printf("6. Expected CGPA Calculator\n");
    printf("7. Student Ranking Demo\n");
    printf("8. Exit\n");
    printf("Enter Choice: ");
}

/* Reads one CourseResult's fields from stdin. */
static CourseResult readCourseResultFromInput(void) {
    char code[16];
    char name[100];
    double credit;
    int semester;
    int completedChoice;

    printf("Course Code: ");
    scanf("%15s", code);
    printf("Course Name: ");
    scanf(" %99[^\n]", name);
    printf("Credit: ");
    scanf("%lf", &credit);
    printf("Semester: ");
    scanf("%d", &semester);

    Course course = createCourse(code, name, credit);

    printf("Completed?\n  1. Yes\n  2. No (incomplete)\n Enter Choice: ");
    scanf("%d", &completedChoice);

    CourseResult cr;
    if (completedChoice == 2) {
        cr = createCourseResult(course, 0.0);
        markIncomplete(&cr);
    } else {
        double marks;
        printf("Marks (0-100): ");
        scanf("%lf", &marks);
        cr = createCourseResult(course, marks);
    }
    setSemester(&cr, semester);
    return cr;
}

static void addCourseResultMenu(CourseList *list) {
    printf("\n--- Add Course Result ---\n");
    CourseResult cr = readCourseResultFromInput();
    addCourseResult(list, cr);
    printf("Added. This course is now #%d in the list.\n", list->count);
}

static void editCourseResultMenu(CourseList *list) {
    if (list->count == 0) {
        printf("\nNo course results yet -- nothing to edit.\n");
        return;
    }
    printf("\n--- Edit Course Result ---\n");
    viewCourseList(list);
    int index;
    printf("\nCourse Result Number to edit: ");
    scanf("%d", &index);
    CourseResult cr = readCourseResultFromInput();
    editCourseResultAt(list, index, cr);
}

static void deleteCourseResultMenu(CourseList *list) {
    if (list->count == 0) {
        printf("\nNo course results yet -- nothing to delete.\n");
        return;
    }
    printf("\n--- Delete Course Result ---\n");
    viewCourseList(list);
    int index;
    printf("\nCourse Result Number to delete: ");
    scanf("%d", &index);
    deleteCourseResultAt(list, index);
    printf("Deleted.\n");
}

static void viewMarksheetMenu(CourseList *list) {
    printf("\n--- Marksheet ---\n\n");
    if (list->count == 0) {
        printf("No course results yet.\n");
        return;
    }
    viewCourseList(list);

    printf("\n");
    for (int semester = 1; semester <= 8; semester++) {
        GpaResult semGpa = computeSemesterGPA(list->items, list->count, semester);
        if (semGpa.courseCount > 0) {
            printf("Semester %d GPA: %.2f\n", semester, semGpa.cgpa);
        }
    }

    GpaResult overall = computeGPAFromList(list);
    printf("\nOverall CGPA: %.2f  (Credits: %.1f)\n",
           overall.cgpa, overall.totalCredits);
}

static void requiredGpaMenu(CourseList *list) {
    printf("\n--- Required GPA Calculator ---\n");
    GpaResult current = computeGPAFromList(list);
    printf("Current CGPA: %.2f (Credits so far: %.1f)\n",
           current.cgpa, current.totalCredits);

    double targetCGPA, remainingCredits;
    printf("Target CGPA: ");
    scanf("%lf", &targetCGPA);
    printf("Remaining credits: ");
    scanf("%lf", &remainingCredits);

    RequiredGpaResult required = computeRequiredGPA(current, remainingCredits, targetCGPA);
    viewRequiredGPA(required);
}

static void expectedGpaMenu(CourseList *list) {
    printf("\n--- Expected CGPA Calculator ---\n");
    int upcomingCount;
    printf("How many upcoming courses? ");
    scanf("%d", &upcomingCount);

    CourseList upcoming = createCourseList();
    for (int i = 0; i < upcomingCount; i++) {
        printf("\nUpcoming course #%d\n", i + 1);
        char code[16], name[100];
        double credit, expectedMarks;
        printf("Course Code: ");
        scanf("%15s", code);
        printf("Course Name: ");
        scanf(" %99[^\n]", name);
        printf("Credit: ");
        scanf("%lf", &credit);
        printf("Expected Marks (0-100): ");
        scanf("%lf", &expectedMarks);
        Course course = createCourse(code, name, credit);
        addCourseResult(&upcoming, createCourseResult(course, expectedMarks));
    }

    printf("\nProjected result if these marks are achieved:\n");
    GpaResult projected = computeExpectedGPA(list, &upcoming);
    viewExpectedGPA(projected);

    freeCourseList(&upcoming);
}

/*
 * Multi-student ranking demo (Features 009/010).
 * The lab manual explicitly treats wiring the student module into the
 * interactive menu as an optional extension, not required checkpoint
 * code -- so this stays a small self-contained sample, same spirit as
 * the manual's own hardcoded main.c demos for those features.
 */
static void studentRankingDemoMenu(void) {
    printf("\n--- Student Ranking Demo ---\n");
    StudentList students = createStudentList();

    Student alice = createStudent("S001", "Alice");
    Student bob   = createStudent("S002", "Bob");
    Student cara  = createStudent("S003", "Cara");

    addCourseToStudent(&alice, createCourseResult(createCourse("CSE 4202", "Structured Programming II", 3.0), 90.0));
    addCourseToStudent(&alice, createCourseResult(createCourse("MAT 4201", "Engineering Mathematics III", 2.0), 60.0));
    computeStudentGPA(&alice);

    addCourseToStudent(&bob, createCourseResult(createCourse("CSE 4202", "Structured Programming II", 3.0), 80.0));
    addCourseToStudent(&bob, createCourseResult(createCourse("MAT 4201", "Engineering Mathematics III", 2.0), 70.0));
    computeStudentGPA(&bob);

    addCourseToStudent(&cara, createCourseResult(createCourse("PHY 4201", "Physics I", 3.0), 95.0));
    computeStudentGPA(&cara);

    addStudent(&students, alice);
    addStudent(&students, bob);
    addStudent(&students, cara);
    viewStudentList(&students);

    rankStudentsByCGPA(&students);
    printf("\nRanked:\n");
    viewRankingTable(&students);

    freeStudentList(&students);
}

int main(void) {
    printf("In IUT, CGPA Matters!\n");

    CourseList courses = createCourseList();
    int choice = 0;

    while (choice != 8) {
        showMenu();
        if (scanf("%d", &choice) != 1) break;

        switch (choice) {
            case 1: addCourseResultMenu(&courses);      break;
            case 2: editCourseResultMenu(&courses);     break;
            case 3: deleteCourseResultMenu(&courses);   break;
            case 4: viewMarksheetMenu(&courses);        break;
            case 5: requiredGpaMenu(&courses);          break;
            case 6: expectedGpaMenu(&courses);          break;
            case 7: studentRankingDemoMenu();           break;
            case 8: printf("\nGoodbye!\n");             break;
            default: printf("\nInvalid choice.\n");     break;
        }
    }

    freeCourseList(&courses);
    return 0;
}
