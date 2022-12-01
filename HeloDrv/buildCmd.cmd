@echo off
set BUILD_TYPE=%~1
shift
set BUILD_ARG=%~1

if "%BUILD_TYPE%" == "Debug" (
    set DDK_BUILD_TYPE=chk
) else (
    set DDK_BUILD_TYPE=fre
)
 
if "%BUILD_ARG%"=="-rebuild" (set BUILD_OPTS=/c /Z)
 
if "%BUILD_ARG%" == "-clean" (
    rd /s /q obj%DDK_BUILD_TYPE%_w7_x86\ 2>NUL:
    del /s /q build%DDK_BUILD_TYPE%_w7_x86.* 2>NUL:
) else (
    echo %~dp0
    pushd .
    call F:\WinDDK\7600.16385.1\bin\setenv.bat F:\WinDDK\7600.16385.1\ %DDK_BUILD_TYPE% x64 WIN7 no_oacr
    popd
    build %BUILD_OPTS%
)