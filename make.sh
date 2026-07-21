#!/usr/bin/env bash
# make.sh — Build the CGPA Calculator (Bash / Linux / Git Bash on Windows)
# Usage: bash make.sh   OR   chmod +x make.sh && ./make.sh

OUTPUT="calculator"
SOURCES="main.c modules/course.c modules/courseResult.c modules/courseList.c modules/gpa.c modules/student.c modules/studentList.c"
FLAGS="-Wall -Wextra -std=c11 -Imodules"

echo "Building CGPA Calculator..."

gcc $SOURCES $FLAGS -o $OUTPUT

if [ $? -eq 0 ]; then
    echo "Build successful!  ->  ./$OUTPUT"
else
    echo "Build FAILED."
    exit 1
fi
