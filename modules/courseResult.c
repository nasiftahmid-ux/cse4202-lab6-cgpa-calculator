#include <stdio.h>
#include <string.h>
#include "courseResult.h"

static void getGrade(double marks, char grade[]) {
    if      (marks >= 90.0) strcpy(grade, "A+");
    else if (marks >= 85.0) strcpy(grade, "A");
    else if (marks >= 80.0) strcpy(grade, "A-");
    else if (marks >= 75.0) strcpy(grade, "B+");
    else if (marks >= 70.0) strcpy(grade, "B");
    else if (marks >= 65.0) strcpy(grade, "B-");
    else if (marks >= 60.0) strcpy(grade, "C+");
    else if (marks >= 55.0) strcpy(grade, "C");
    else if (marks >= 50.0) strcpy(grade, "D");
    else                    strcpy(grade, "F");
}

static double getGradePoint(double marks) {
    if      (marks >= 90.0) return 4.00;
    else if (marks >= 85.0) return 3.75;
    else if (marks >= 80.0) return 3.50;
    else if (marks >= 75.0) return 3.25;
    else if (marks >= 70.0) return 3.00;
    else if (marks >= 65.0) return 2.75;
    else if (marks >= 60.0) return 2.50;
    else if (marks >= 55.0) return 2.25;
    else if (marks >= 50.0) return 2.00;
    else                    return 0.00;
}

CourseResult createCourseResult(Course course, double marks) {
    CourseResult cr;
    cr.course       = course;
    cr.marks        = marks;
    cr.isIncomplete = 0;   /* default: complete  */
    cr.semester     = 1;   /* default: semester 1 (Feature 005) */
    getGrade(marks, cr.grade);
    cr.gradePoint   = getGradePoint(marks);
    return cr;
}

void markIncomplete(CourseResult *cr) {
    cr->isIncomplete = 1;
}

/* Feature 005 */
void setSemester(CourseResult *cr, int semester) {
    cr->semester = semester;
}

void viewCourseResult(CourseResult cr) {
    printf("Code       : %s\n",   cr.course.code);
    printf("Name       : %s\n",   cr.course.name);
    printf("Credit     : %.1f\n", cr.course.credit);
    printf("Semester   : %d\n",   cr.semester);
    if (cr.isIncomplete) {
        printf("Status     : Incomplete (excluded from CGPA)\n");
    } else {
        printf("Marks      : %.2f\n", cr.marks);
        printf("Grade      : %s\n",   cr.grade);
        printf("Grade Point: %.2f\n", cr.gradePoint);
    }
}
