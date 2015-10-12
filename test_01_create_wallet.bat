@echo off

rem build application
mingw32-make moneytracker
mkdir C:\learn
rem clean log file for actual results
type nul > test_01_create_wallet.log

echo Example #0 >> test_01_create_wallet.log
echo [TEST: output] >> test_01_create_wallet.log
moneytracker.exe create my.wallet 1000 >> test_01_create_wallet.log 2>>&1
echo [TEST: file] >> test_01_create_wallet.log
type my.wallet >> test_01_create_wallet.log 2>>&1
(echo ... end ... & echo.) >> test_01_create_wallet.log

echo Example #1 >> test_01_create_wallet.log
echo [TEST: output] >> test_01_create_wallet.log
moneytracker.exe create other.wallet +200 >> test_01_create_wallet.log 2>>&1
echo [TEST: file] >> test_01_create_wallet.log
type other.wallet >> test_01_create_wallet.log 2>>&1
(echo ... end ... & echo.) >> test_01_create_wallet.log

echo Example #2 >> test_01_create_wallet.log
echo [TEST: output] >> test_01_create_wallet.log
moneytracker.exe create yetother -1021.23 >> test_01_create_wallet.log 2>>&1
echo [TEST: file] >> test_01_create_wallet.log
type yetother >> test_01_create_wallet.log 2>>&1
(echo ... end ... & echo.) >> test_01_create_wallet.log

echo Example #3 >> test_01_create_wallet.log
echo [TEST: output] >> test_01_create_wallet.log
moneytracker.exe create yetother not_number >> test_01_create_wallet.log 2>>&1
echo [TEST: file] >> test_01_create_wallet.log
type yetother >> test_01_create_wallet.log 2>>&1
(echo ... end ... & echo.) >> test_01_create_wallet.log

echo Example #4 >> test_01_create_wallet.log
echo [TEST: output] >> test_01_create_wallet.log
moneytracker.exe create C:\learn\some.wallet 22.125 >> test_01_create_wallet.log 2>>&1
echo [TEST: file] >> test_01_create_wallet.log
type C:\learn\some.wallet >> test_01_create_wallet.log 2>>&1
(echo ... end ... & echo.) >> test_01_create_wallet.log

echo Example #5 >> test_01_create_wallet.log
echo [TEST: output] >> test_01_create_wallet.log
moneytracker.exe create noinitial.wallet >> test_01_create_wallet.log 2>>&1
echo [TEST: file] >> test_01_create_wallet.log
type noinitial.wallet >> test_01_create_wallet.log 2>>&1
(echo ... end ... & echo.) >> test_01_create_wallet.log

echo Example #6 >> test_01_create_wallet.log
echo [TEST: output] >> test_01_create_wallet.log
moneytracker.exe create wrongdec.wallet 12,24 >> test_01_create_wallet.log 2>>&1
echo [TEST: file] >> test_01_create_wallet.log
type wrongdec.wallet >> test_01_create_wallet.log 2>>&1
(echo ... end ... & echo.) >> test_01_create_wallet.log

echo Example #7 >> test_01_create_wallet.log
echo [TEST: output] >> test_01_create_wallet.log
moneytracker.exe create leading0.wallet -00012.24 >> test_01_create_wallet.log 2>>&1
echo [TEST: file] >> test_01_create_wallet.log
type leading0.wallet >> test_01_create_wallet.log 2>>&1
(echo ... end ... & echo.) >> test_01_create_wallet.log

echo Example #8 >> test_01_create_wallet.log
echo [TEST: output] >> test_01_create_wallet.log
moneytracker.exe create >> test_01_create_wallet.log 2>>&1
(echo ... end ... & echo.) >> test_01_create_wallet.log

del my.wallet >> test_01_create_wallet.log 2>>&1
del other.wallet >> test_01_create_wallet.log 2>>&1
del yetother >> test_01_create_wallet.log 2>>&1
del C:\learn\some.wallet >> test_01_create_wallet.log 2>>&1
del noinitial.wallet >> test_01_create_wallet.log 2>>&1
del wrongdec.wallet >> test_01_create_wallet.log 2>>&1
del leading0.wallet >> test_01_create_wallet.log 2>>&1

rem this should have no output if everything works as expected
git diff test_01_create_wallet.log

@echo on
