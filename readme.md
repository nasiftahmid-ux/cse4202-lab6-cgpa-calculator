# In IUT, CGPA Matters

A modular C project for calculating CGPA, developed for **CSE 4202: Structured Programming II** at IUT.

## Project Structure

```
.
├── main.c                      # Entry point
├── make.ps1                    # Build script (Windows / PowerShell)
├── make.sh                     # Build script (Linux / Git Bash)
├── feature.txt                 # Feature dependency tree
├── modules/
│   ├── course.h / course.c     # Feature 001 — Course data type
│   └── courseResult.h / .c     # Feature 002 — Course result & IUT grading
└── tests/
    ├── test.ps1                # Test runner (Windows / PowerShell)
    ├── test.sh                 # Test runner (Linux / Git Bash)
    ├── test_course.c           # Tests for Course module
    └── test_course_result.c    # Tests for CourseResult module
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

## Feature Progress

| # | Feature | Status | Branch |
|---|---------|--------|--------|
| 001 | Course module | ✅ Done | `feature001` → `dev` |
| 002 | CourseResult module | ✅ Done | `feature002` → `dev` |
| 003 | CGPA Calculator | ⏳ Next | `feature003` |
| 004 | Incomplete Courses | ⏳ Planned | `feature004` |
| 005 | Semester GPA | ⏳ Planned | `feature005` |
| 006 | Dynamic Course List | ⏳ Planned | `feature006` |
| 007 | Required GPA | ⏳ Planned | `feature007` |
| 008 | Expected CGPA | ⏳ Planned | `feature008` |
| 009 | Multiple Students | ⏳ Planned | `feature009` |
| 010 | Student Ranking | ⏳ Planned | `feature010` |

## Git Workflow

Each feature branch follows the **4-commit rule**:
1. **Declare** — create the `.h` header file
2. **Define** — implement the `.c` source file
3. **Test** — write test suite in `tests/`, update build/test scripts
4. **Front-end** — integrate into `main.c` and verify console output