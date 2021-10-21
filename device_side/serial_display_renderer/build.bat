@echo off
REM simple build script

REM get developer command prompt context
CALL "C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\Common7\Tools\VsDevCmd.bat"

REM in my case debug simply means to print the instrumentation logs
IF "%2" == "log" (SET log="/DSHOULD_LOG") ELSE (SET log=)

SET include_dir=deps/include
SET lib_dir=deps/lib

set libs=sfml-main.lib sfml-graphics.lib sfml-system.lib sfml-window.lib

SET build_folder=build
SET out_file=%build_folder%/display.exe

IF NOT EXIST "%build_folder%" MKDIR %build_folder%

SET src= main.cpp ^
Serial.cpp

REM call VC++ compiler
IF "%1" == "debug" (
    cl %log% /I "%include_dir%" /EHsc /Zi /Fd"%build_folder%/" /MT %src% /Fo"%build_folder%/" /link /DEBUG /LIBPATH:"%lib_dir%" %libs% /out:%out_file%
) ELSE (
    cl %log% /I "%include_dir%" /EHsc /MT %src% /Fo"%build_folder%/" /link /LIBPATH:"%lib_dir%" %libs% /out:%out_file%
)

IF errorlevel 1 (
    ECHO compilation failed
) ELSE (
    REM run the resulting game
    REM START %out_file%
)
