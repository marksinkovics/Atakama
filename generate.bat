@echo off
setlocal

CALL :ARG-PARSER %*

if "%ARG_HELP%" == "1" (
    echo Usage: .\generate.bat
    echo Parameters:
    echo     /clean - clean the build folder
    echo     /open -  open the project in Visual Studio
    goto :EOF
)

if "%ARG_CLEAN%" == "1" (
    echo "Clean build folder"
    rmdir /s /q .\build
)

echo "Generate Visual Studio project"
cmake -S . -B build/visualstudio -G "Visual Studio 17 2022"

if "%ARG_OPEN%" == "1" (
    echo "Open project"
    start .\build\visualstudio\Atakama.sln
)

::*********************************************************
:: Parse commandline arguments into sane variables
:: Based on: https://stackoverflow.com/a/61552059
::*********************************************************
:ARG-PARSER
    ::Loop until two consecutive empty args
    :loopargs
        IF "%~1%~2" EQU "" GOTO :EOF

        set "arg1=%~1" 
        set "arg2=%~2"
        shift

        ::Allow either / or -
        set "tst1=%arg1:-=/%"
        if "%arg1%" NEQ "" (
            set "tst1=%tst1:~0,1%"
        ) ELSE (
            set "tst1="
        )

        set "tst2=%arg2:-=/%"
        if "%arg2%" NEQ "" (
            set "tst2=%tst2:~0,1%"
        ) ELSE (
            set "tst2="
        )


        ::Capture assignments (eg. /foo bar)
        IF "%tst1%" EQU "/"  IF "%tst2%" NEQ "/" IF "%tst2%" NEQ "" (
            set "ARG_%arg1:~1%=%arg2%"
            GOTO loopargs
        )

        ::Capture flags (eg. /foo)
        IF "%tst1%" EQU "/" (
            set "ARG_%arg1:~1%=1"
            GOTO loopargs
        )
    goto loopargs
GOTO :EOF