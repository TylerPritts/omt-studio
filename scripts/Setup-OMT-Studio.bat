@echo off

pushd ..
vendor\bin\premake\Windows\premake5.exe --file=Build-OMT-Studio.lua vs2022
popd
pause
