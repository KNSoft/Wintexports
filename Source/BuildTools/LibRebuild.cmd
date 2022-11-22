REM LibRebuild.cmd
REM Rebuild library (archive) tool
REM Usage:
REM     LibRebuild.cmd LibDir LstDir
REM         LibDir: Source library file directory
REM         LstDir: Directory contains *.lst file to specify object files to Exporting
REM     New library will output in LstDir, has same name with LstDir
REM Copyright: KNSoft.org - Wintexports project

ECHO Exporting object files ...
FOR %%i in (%~2\*.lst) DO (
    FOR /F %%j in (%%i) DO (
        Lib.exe /NOLOGO %%~ni /EXTRACT:%%j /OUT:%~2\%%~nxj
        IF %ERRORLEVEL% NEQ 0 (
            EXIT /B %ERRORLEVEL%
        )
    )
)

Lib.exe /NOLOGO /OUT:%~2\%~n2.lib "%~2\*.obj"
EXIT /B %ERRORLEVEL%