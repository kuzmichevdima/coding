cp ../gen_py/gen_py.py gen_py.py
cp st_py/st_py.py st_py.py
cp st_c/Debug/st_c.exe st_c.exe

@echo off
SET /a a = 1
:label
echo test number %a%
set /a a = %a% + 1	
gen_py.py 5000 10000 100000 > input.txt
echo test generated
st_py.py < input.txt > output_py.txt
echo python solution: done
st_c.exe <input.txt > output_c.txt
echo c solution: done
diff output_py.txt output_c.txt
if errorlevel 1 goto fail
goto label

:fail
echo fail