@echo off
set /a a=0
:label
set /a a = %a% + 1

set /a t1 = %a% / 10
set /a t2 = %a% - %t1% * 10
set "f=%t1%%t2%"
::echo %f%
set "r=%f%.a"
::echo %r%
if not exist %r% goto finish
echo TEST %a%
a_1.exe < %f% > output.txt
::echo output:
type output.txt
echo.
type %r%
fc output.txt %r%
if errorlevel 1 goto fail

::echo OK test %a%
echo OK
echo.
goto label
:fail
echo FAILED test %a%
:finish
echo testing completed
