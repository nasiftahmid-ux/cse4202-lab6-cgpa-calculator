# test.ps1 — Run all test suites (PowerShell / Windows)
# Usage: .\test.ps1
#
# Each test file is compiled with the required module sources, then executed.
# A non-zero exit code from any test binary is treated as a failure.

$ModuleSources = @("modules\course.c", "modules\courseResult.c")
$Flags         = @("-Wall", "-std=c11", "-Imodules")

$Tests = @(
    @{ File = "tests\test_course.c";        Bin = "test_course.exe";        Modules = @("modules\course.c") },
    @{ File = "tests\test_course_result.c"; Bin = "test_course_result.exe"; Modules = @("modules\course.c", "modules\courseResult.c") },
    @{ File = "tests\test_gpa.c";           Bin = "test_gpa.exe";           Modules = @("modules\course.c", "modules\courseResult.c", "modules\gpa.c") }
)

$totalSuites  = 0
$passedSuites = 0

Write-Host ""
Write-Host "═══════════════════════════════════" -ForegroundColor Cyan
Write-Host "  CGPA Calculator — Test Runner    " -ForegroundColor Cyan
Write-Host "═══════════════════════════════════" -ForegroundColor Cyan

foreach ($t in $Tests) {
    $totalSuites++
    $suiteName = [System.IO.Path]::GetFileNameWithoutExtension($t.File)
    Write-Host ""
    Write-Host "▶ $suiteName" -ForegroundColor Yellow

    # Compile
    $sources = ($t.Modules + @($t.File)) -join " "
    $cmd = "gcc $sources $($Flags -join ' ') -o $($t.Bin)"
    Invoke-Expression $cmd

    if ($LASTEXITCODE -ne 0) {
        Write-Host "  [COMPILE ERROR] $($t.File)" -ForegroundColor Red
        continue
    }

    # Run
    & ".\$($t.Bin)"
    if ($LASTEXITCODE -eq 0) {
        $passedSuites++
        Write-Host "  Suite PASSED" -ForegroundColor Green
    } else {
        Write-Host "  Suite FAILED" -ForegroundColor Red
    }

    # Cleanup binary
    Remove-Item -Force $t.Bin -ErrorAction SilentlyContinue
}

Write-Host ""
Write-Host "═══════════════════════════════════" -ForegroundColor Cyan
Write-Host "  Results: $passedSuites/$totalSuites suites passed" -ForegroundColor $(if ($passedSuites -eq $totalSuites) { "Green" } else { "Red" })
Write-Host "═══════════════════════════════════" -ForegroundColor Cyan
Write-Host ""

if ($passedSuites -ne $totalSuites) { exit 1 }
