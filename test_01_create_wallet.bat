@echo off

SET test_name=test_01_create_wallet


rem clean log file for actual results
del %test_name%.actual > nul 2>&1
rem clean log file for expected results
del %test_name%.expected > nul 2>&1

rem ============================ TEST 0 ========================================
(
echo Example #0
echo [TEST: output]
moneytracker.exe create my.wallet 1000
echo [TEST: file]
type my.wallet
echo ... end ...
echo.
) >> %test_name%.actual 2>>&1

(
echo Example #0
echo [TEST: output]
echo my.wallet created with the initial amount of +1000.00 RON
echo [TEST: file]
echo +1000.00 RON
echo ... end ...
echo.
) >> %test_name%.expected 2>>&1

rem ============================ TEST 1 ========================================
(
echo Example #1
echo [TEST: output]
moneytracker create other.wallet +200
echo [TEST: file]
type other.wallet
echo ... end ...
echo.
) >> %test_name%.actual 2>>&1

(
echo Example #1
echo [TEST: output]
echo other.wallet created with the initial amount of +200.00 RON
echo [TEST: file]
echo +200.00 RON
echo ... end ...
echo.
) >> %test_name%.expected 2>>&1

rem ============================ TEST 2 ========================================
(
echo Example #2
echo [TEST: output]
moneytracker create yetother -1021.23
echo [TEST: file]
type yetother
echo ... end ...
echo.
) >> %test_name%.actual 2>>&1

(
echo Example #2
echo [TEST: output]
echo yetother created with the initial amount of -1021.23 RON
echo [TEST: file]
echo -1021.23 RON
echo ... end ...
echo.
) >> %test_name%.expected 2>>&1

rem ============================ TEST 3 ========================================
(
echo Example #3
echo [TEST: output]
moneytracker create yetother not_number
echo [TEST: file]
type yetother
echo ... end ...
echo.
) >> %test_name%.actual 2>>&1

(
echo Example #3
echo [TEST: output]
echo error: wallet yetother already exists!
echo [TEST: file]
echo -1021.23 RON
echo ... end ...
echo.
) >> %test_name%.expected 2>>&1

rem ============================ TEST 4 ========================================
set TEST_FOLDER_CREATED=no

if not exist "C:\somedir\" (
    mkdir C:\somedir
    set TEST_FOLDER_CREATED=yes
)

(
echo Example #4
echo [TEST: output]
moneytracker create C:\somedir\some.wallet 22.125
echo [TEST: file]
type C:\somedir\some.wallet
echo ... end ...
echo.
) >> %test_name%.actual 2>>&1

(
echo Example #4
echo [TEST: output]
echo C:\somedir\some.wallet created with the initial amount of +22.13 RON
echo [TEST: file]
echo +22.13 RON
echo ... end ...
echo.
) >> %test_name%.expected 2>>&1

del C:\somedir\some.wallet
if %TEST_FOLDER_CREATED%==yes (
    rmdir /S /Q C:\somedir
)

rem ============================ TEST 5 ========================================
(
echo Example #5
echo [TEST: output]
moneytracker create noinitial.wallet
echo [TEST: file]
type noinitial.wallet
echo ... end ...
echo.
) >> %test_name%.actual 2>>&1

(
echo Example #5
echo [TEST: output]
echo noinitial.wallet created with the initial amount of +00.00 RON
echo [TEST: file]
echo +00.00 RON
echo ... end ...
echo.
) >> %test_name%.expected 2>>&1

rem ============================ TEST 6 ========================================
(
echo Example #6
echo [TEST: output]
moneytracker create wrongdec.wallet 12,24
echo [TEST: file]
type wrongdec.wallet
echo ... end ...
echo.
) >> %test_name%.actual 2>>&1

(
echo Example #6
echo [TEST: output]
echo error: 12,24 is not a valid initial ammount.
echo Creating wrongdec.wallet aborted.
echo [TEST: file]
echo The system cannot find the file specified.
echo ... end ...
echo.
) >> %test_name%.expected 2>>&1

rem ============================ TEST 7 ========================================
(
echo Example #7
echo [TEST: output]
moneytracker create leading0.wallet -00012.24
echo [TEST: file]
type leading0.wallet
echo ... end ...
echo.
) >> %test_name%.actual 2>>&1

(
echo Example #7
echo [TEST: output]
echo leading0.wallet created with the initial amount of -12.24 RON
echo [TEST: file]
echo -12.24 RON
echo ... end ...
echo.
) >> %test_name%.expected 2>>&1

rem ============================ TEST 8 ========================================
(
echo Example #8
echo [TEST: output]
moneytracker create
echo ... end ...
echo.
) >> %test_name%.actual 2>>&1

(
echo Example #8
echo [TEST: output]
echo error: at least filename should be specified.
echo ... end ...
echo.
) >> %test_name%.expected 2>>&1

rem ============================ TEST 9 ========================================
(
echo Example #9
echo [TEST: output]
moneytracker create C:\path\not\existing\my.wallet 111
echo [TEST: file]
type C:\path\not\existing\my.wallet
echo ... end ...
echo.
) >> %test_name%.actual 2>>&1

(
echo Example #9
echo [TEST: output]
echo error: could not create C:\path\not\existing\my.wallet
echo [TEST: file]
echo The system cannot find the path specified.
echo ... end ...
echo.
) >> %test_name%.expected 2>>&1

rem ============================ TEARDOWN ======================================
del my.wallet >> %test_name%.actual 2>>&1
del other.wallet >> %test_name%.actual 2>>&1
del yetother >> %test_name%.actual 2>>&1
rem del C:\learn\some.wallet >> %test_name%.actual 2>>&1
del noinitial.wallet >> %test_name%.actual 2>>&1
del leading0.wallet >> %test_name%.actual 2>>&1

rem this should have no output if everything works as expected
rem use diff unified format, and redirect output for later use
diff -u %test_name%.expected %test_name%.actual > %test_name%.diff

if %errorlevel% EQU 1 (
  echo [  FAILED] see %test_name%.diff
) else (
  echo [  PASSED] see %test_name%.diff
)

@echo on
@exit /b

