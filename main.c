#include <stdio.h>
#include "modules/course.h"

int main() {
    printf("In IUT, CGPA Matters!\n\n");

    Course c1 = createCourse("CSE 4202", "Structured Programming II", 3.0);
    viewCourse(c1);

    return 0;
}