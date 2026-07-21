#!/usr/bin/env bash
# test.sh — Run all test suites (Bash / Linux / Git Bash on Windows)
# Usage: bash tests/test.sh   OR   chmod +x tests/test.sh && tests/test.sh

FLAGS="-Wall -std=c11 -Imodules"

declare -a TEST_FILES=(
    "tests/test_course.c"
    "tests/test_course_result.c"
    "tests/test_gpa.c"
)

declare -A TEST_MODULES=(
    ["tests/test_course.c"]="modules/course.c"
    ["tests/test_course_result.c"]="modules/course.c modules/courseResult.c"
    ["tests/test_gpa.c"]="modules/course.c modules/courseResult.c modules/gpa.c"
)

total_suites=0
passed_suites=0

echo ""
echo "═══════════════════════════════════"
echo "  CGPA Calculator — Test Runner   "
echo "═══════════════════════════════════"

for test_file in "${TEST_FILES[@]}"; do
    total_suites=$((total_suites + 1))
    suite_name=$(basename "${test_file}" .c)
    bin="./${suite_name}"

    echo ""
    echo "▶ ${suite_name}"

    modules="${TEST_MODULES[$test_file]}"
    gcc ${modules} ${test_file} ${FLAGS} -o ${bin}

    if [ $? -ne 0 ]; then
        echo "  [COMPILE ERROR] ${test_file}"
        continue
    fi

    ${bin}
    if [ $? -eq 0 ]; then
        passed_suites=$((passed_suites + 1))
        echo "  Suite PASSED"
    else
        echo "  Suite FAILED"
    fi

    rm -f "${bin}"
done

echo ""
echo "═══════════════════════════════════"
echo "  Results: ${passed_suites}/${total_suites} suites passed"
echo "═══════════════════════════════════"
echo ""

[ "${passed_suites}" -eq "${total_suites}" ]
