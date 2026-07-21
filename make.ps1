# make.ps1 — Build the CGPA Calculator (PowerShell / Windows)
# Usage: .\make.ps1

$Output    = "calculator.exe"
$Sources   = @(
    "main.c",
    "modules\course.c",
    "modules\courseResult.c",
    "modules\courseList.c",
    "modules\gpa.c",
    "modules\student.c",
    "modules\studentList.c"
)
$Flags     = @("-Wall", "-Wextra", "-std=c11", "-Imodules")

Write-Host "Building CGPA Calculator..." -ForegroundColor Cyan

$cmd = "gcc " + ($Sources -join " ") + " " + ($Flags -join " ") + " -o $Output"
Invoke-Expression $cmd

if ($LASTEXITCODE -eq 0) {
    Write-Host "Build successful!  ->  .\$Output" -ForegroundColor Green
} else {
    Write-Host "Build FAILED." -ForegroundColor Red
    exit 1
}
