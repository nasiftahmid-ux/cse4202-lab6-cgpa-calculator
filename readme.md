# In IUT, CGPA Matters

A modular C project for calculating CGPA, developed for **CSE 4202: Structured Programming II** at IUT.

## Project Structure

```
.
├── main.c                        # Entry point — interactive console menu
├── make.ps1                      # Build script (Windows / PowerShell)
├── make.sh                       # Build script (Linux / Git Bash)
├── features.txt                  # Feature dependency tree (rows removed as merged)
├── .gitattributes                # Enforces LF line endings repo-wide
├── modules/
│   ├── course.h / course.c             # Feature 001 — Course data type
│   ├── courseResult.h / .c             # Feature 002/004/005 — result, incomplete, semester
│   ├── courseList.h / .c               # Feature 006 — dynamic course list (add/edit/delete/view)
│   ├── gpa.h / .c                      # Feature 003/005/007/008 — CGPA, semester GPA,
│   │                                    #   required GPA, expected CGPA
│   ├── student.h / .c                  # Feature 009 — a single student's transcript
│   └── studentList.h / .c              # Feature 009/010 — roster + ranking
└── tests/
    ├── test.ps1 / test.sh          # Test runners (Windows / Linux)
    ├── test_course.c
    ├── test_course_result.c
    ├── test_gpa.c
    ├── test_incomplete.c
    ├── test_semester_gpa.c
    ├── test_course_list.c
    ├── test_required_gpa.c
    ├── test_expected_gpa.c
    └── test_student.c
```

## Build

**Windows (PowerShell):**
```powershell
.\make.ps1
.\calculator.exe
```

**Linux / Git Bash:**
```bash
bash make.sh
./calculator
```

## Run Tests

**Windows (PowerShell):**
```powershell
.\tests\test.ps1
```

**Linux / Git Bash:**
```bash
bash tests/test.sh
```

## Using the Calculator

Running `calculator` (or `calculator.exe`) opens an interactive menu:

```
1. Add Course Result
2. Edit Course Result
3. Delete Course Result
4. View Marksheet
5. Required GPA Calculator
6. Expected CGPA Calculator
7. Student Ranking Demo
8. Exit
```

A `CourseResult` in this project owns its `Course` directly (rather than
pointing into a separate array), so course and course-result management
collapse into a single set of operations. **View Marksheet** shows the
full course table, each semester's GPA, and the overall CGPA. **Required**
and **Expected** GPA prompt for their own inputs against your live course
list. **Student Ranking Demo** is a small self-contained sample of the
multi-student/ranking modules (009/010) — the lab manual treats wiring
those into this menu as an optional extension rather than required
checkpoint code.

## IUT Grading Scale

| Grade | Points | Marks Range     |
|-------|--------|-----------------|
| A+    | 4.00   | ≥ 90            |
| A     | 3.75   | 85 – 89.99      |
| A-    | 3.50   | 80 – 84.99      |
| B+    | 3.25   | 75 – 79.99      |
| B     | 3.00   | 70 – 74.99      |
| B-    | 2.75   | 65 – 69.99      |
| C+    | 2.50   | 60 – 64.99      |
| C     | 2.25   | 55 – 59.99      |
| D     | 2.00   | 50 – 54.99      |
| F     | 0.00   | < 50            |

**CGPA Formula:** `CGPA = Σ(gradePoint × credit) / Σ(credit)`

Incomplete courses are excluded from CGPA until graded (Feature 004).

## Feature Progress

| # | Feature | Status |
|---|---------|--------|
| 001 | Course module | ✅ Done |
| 002 | CourseResult module | ✅ Done |
| 003 | CGPA Calculator | ✅ Done |
| 004 | Incomplete Courses | ✅ Done |
| 005 | Semester GPA | ✅ Done |
| 006 | Dynamic Course List | ✅ Done |
| 007 | Required GPA | ✅ Done |
| 008 | Expected CGPA | ✅ Done |
| 009 | Multiple Students | ✅ Done |
| 010 | Student Ranking | ✅ Done |

All 10 features are merged into `dev`. See `git log --oneline --all --graph`
for the full branch/merge history, or `features.txt` for the current
(now-empty) dependency tracker.

## Git Workflow

Each feature branch follows the **4-commit rule**:
1. **Declare** — create the `.h` header file
2. **Define** — implement the `.c` source file
3. **Test** — write test suite in `tests/`, update build/test scripts
4. **Front-end** — integrate into `main.c` and verify console output
