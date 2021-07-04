@REM ---------------------------------------------------------------------------------------------
@REM Vectrex C Windows Batch Make Script
@REM Peer Johannsen
@REM contact: vectrex@pforzheim-university.de
@REM ---------------------------------------------------------------------------------------------
@REM some windows batch stuff

@echo off
setlocal enableextensions enabledelayedexpansion

@REM ---------------------------------------------------------------------------------------------
@REM user edit: configure make script
@REM set options to either "yes" or "no"

@REM ENABLE_PREPROCESSING			save output files of the C preprocessor (*.i) separately
@REM ENABLE_C_DEBUGGING				do not pass macro NDEBUG to gcc6809, activate assert() in C
@REM ENABLE_C_OPTIMIZATION			set gcc6809 to either optimization level -O0 or -O2
@REM ENABLE_ASSEMBLY_OPTIMIZATION	activate assembly peephole postprocessing optimization

set ENABLE_PREPROCESSING=yes
set ENABLE_C_DEBUGGING=yes
set ENABLE_C_OPTIMIZATION=no
set ENABLE_ASSEMBLY_OPTIMIZATION=no

set C_OPTIMIZATION_LEVEL=-O2

@REM ---------------------------------------------------------------------------------------------
@REM configure gcc6809, do not edit

set GCC=..\..\gcc6809

set AS6808=as6809.exe
set ASLINK=aslink.exe

set GCC_FLAGS_C=-std=gnu99 -D __INLINE_RUM=0
set GCC_FLAGS_GENERAL=-quiet -fno-time-report
set GCC_FLAGS_6809=-fomit-frame-pointer -fno-toplevel-reorder -mint8 -msoft-reg-count=0 -funit-at-a-time

REM -fno-zero-initialized-in-bss

set GCC_FLAGS_OPTIMIZE=-fno-ipa-reference -ftree-ter
set GCC_FLAGS_WARN=-W -Werror -Wall -Wextra -Wlogical-op -Wdisabled-optimization -Wmissing-noreturn -Wpadded -Wredundant-decls -Winline  -Wstrict-overflow=5 -Wconversion -Winit-self -Wswitch-default -Wswitch-enum -Wstrict-aliasing=0

@REM settings for some stricter warnings
@REM -Wstrict-prototypes -Wold-style-definition -Wtraditional-conversion

@REM ---------------------------------------------------------------------------------------------
@REM more configurations, do not edit

if [%ENABLE_C_DEBUGGING%]==[no] (
	REM set GCC_FLAGS_WARN=%GCC_FLAGS_WARN% -Wunreachable-code
	set GCC_FLAGS_C=%GCC_FLAGS_C% -D NDEBUG
)

set GCC_FLAGS= %GCC_FLAGS_GENERAL% %GCC_FLAGS_C% %GCC_FLAGS_6809% %GCC_FLAGS_WARN% %GCC_FLAGS_OPTIMIZE% 
set GCC_INC=-I %GCC%\vectrex\include\system -I %GCC%\vectrex\include\lib -I .\source -I .\source\lib

for /d %%D in (.\source\lib\*) do (
	set GCC_INC=!GCC_INC! -I .\source\lib\%%~nxD
)

echo GCC_INC is %GCC_INC%

set LINK_PATH=-k %GCC%\vectrex\lib\system\ -k %GCC%\vectrex\lib\lib\ -k .\build\lib\
set LINK_LIBS=-l rum.lib -l gcc.lib -l libgcc.lib -l assert.lib
set LINK_STATIC=%GCC%\vectrex\lib\system\static\*.rel

@REM ---------------------------------------------------------------------------------------------
@REM and even more configurations, do not edit

set TARGET=%1
if [%TARGET%] == [] (
	set TARGET=build
)
set OPT=%2
if [%OPT%] == [] (
	if [%ENABLE_C_OPTIMIZATION%] == [yes] (
		set OPT=%C_OPTIMIZATION_LEVEL%
	) else (
		set OPT=-O0
	)
)

@REM ---------------------------------------------------------------------------------------------
@REM call main target, do not edit

call :main %TARGET% %OPT%
exit /B %ERRORLEVEL%

@REM ---------------------------------------------------------------------------------------------
@REM auxiliary subprocedures, do not edit

:find_source_files - path pattern
    set source_paths=
    set source_files=
	set files=
    for /r "%~1" %%P in ("%~2") do (
        set source_paths=!source_paths! "%%~fP"
        set source_files=!source_files! "%%~nP%%~xP"
		set files=!files! "%%~nP"
    )
goto :eof

:separator
	echo *************************************************************************
exit /B 0

:line
	echo -------------------------------------------------------------------------
exit /B 0

:remove - FILE
	set FILE=%1
	if exist %FILE% (
		echo removing %FILE%
		del %FILE% 
	)
exit /B 0

:wipe - FOLDER
	set FOLDER=%1
	call :remove .\%FOLDER%\*.i
	call :remove .\%FOLDER%\*.s
	call :remove .\%FOLDER%\*.lst
	call :remove .\%FOLDER%\*.rel
	call :remove .\%FOLDER%\*.rst
	call :remove .\%FOLDER%\*.hlr
	call :remove .\%FOLDER%\*.map
	call :remove .\%FOLDER%\*.s19
	call :remove .\%FOLDER%\*.bin
exit /B 0

:getFilesize - FILE
	set fileSize=%~z1
exit /B

:copy - PROJECT
	set PROJECT=%1
	echo copying...
	copy .\build\%PROJECT%.bin C:\temp\%PROJECT%.bin || exit \b
exit /B 0

@REM ---------------------------------------------------------------------------------------------
@REM make target subprocedures, do not edit

:clean
	call :wipe bin
	call :wipe build
	call :wipe build\rel
	rmdir /s /q build\lib
	mkdir build\lib
	rmdir /s /q build\src
	mkdir build\src
exit /B 0

:preprocess - SOURCE DEST GCC_OPT
	setlocal enableextensions enabledelayedexpansion
	set FILE=%~n1
	set SOURCE=%1
	set DEST=%2
	set GCC_OPT=-E %~3
	echo preprocessing %FILE%.c
	%GCC%\bin\gcc6809.exe %GCC_INC% %GCC_FLAGS% %GCC_OPT% -o %DEST%\%FILE%.i %SOURCE% || exit \b
exit /B 0

:compile - REL_FILE REL_DEST GCC_OPT REL_PATH
	setlocal enableextensions enabledelayedexpansion
	set CFILE=%1
	set CDEST=%2
	set COPT=%3
	set CPATH=%4
	if not [%CPATH%]==[] (
		if not exist %CDEST%\%CPATH% (
			echo creating directory %CDEST%\%CPATH%
			mkdir %CDEST%\%CPATH%
		)
	)
	if [%ENABLE_PREPROCESSING%]==[yes] (
		echo preprocessing %CPATH%%CFILE%.c
		%GCC%\bin\gcc6809.exe %GCC_INC% %GCC_FLAGS% %COPT% -E -o %CDEST%\%CPATH%%CFILE%.i source\%CPATH%%CFILE%.c || exit \b
	)
	echo compiling %CPATH%%CFILE%.c
	%GCC%\bin\gcc6809.exe %GCC_INC% %GCC_FLAGS% %COPT% -o %CDEST%\%CPATH%%CFILE%.s source\%CPATH%%CFILE%.c || exit \b
exit /B 0

:optimize - FILE FOLDER
	setlocal enableextensions enabledelayedexpansion
	set FILE=%1
	set FOLDER=%2
	%GCC%\optimize\rxrepl --no-backup --return-count -f .\%FOLDER%\%FILE%.s -a  --options %GCC%\optimize\rules_optimize.txt
	echo %ERRORLEVEL% line(s) optimized in %FILE%.s
exit /B %ERRORLEVEL%

:assemble - SOURCE DEST FILE PATH PREF
	set FROM=%1
	set DEST=%2
	set FILE=%3
	set PATH=%4
	set PREF=%5
	if not [%PREF%]==[] (
		set PREF=!PREF:/=_!
		set PREF=!PREF:\=_!
	)
	echo assembling %PATH%%FILE%.s
	%GCC%\bin\%AS6808% -x -f -p -l -o -g .\%DEST%\%PREF%%FILE%.rel .\%FROM%\%PATH%%FILE%.s || exit \b
exit /B 0

:link - PROJECT FILES
	setlocal enabledelayedexpansion
	set PROJECT=%1
	set FILES=empty
	set RFILES=empty
	for %%F in (.\build\rel\*.rel) do (
		if !FILES!==empty (
			set FILES=%%~nF.rel
		) else (
			set FILES=!FILES! %%~nF.rel
		)
		if !RFILES!==empty (
			set RFILES=.\build\rel\%%~nF.rel
		) else (
			set RFILES=!RFILES! .\build\rel\%%~nF.rel
		)
	)
	set LFILES=empty
	for %%F in (%GCC%\vectrex\lib\system\static\*.rel) do (
		if !LFILES!==empty (
			set LFILES=%GCC%\vectrex\lib\system\static\%%~nF.rel
		) else (
			set LFILES=!LFILES! %GCC%\vectrex\lib\system\static\%%~nF.rel
		)
	)

	echo linking !FILES!
	@REM call :separator
	@REM echo lfiles !LFILES!
	@REM call :separator
	@REM echo rfiles !RFILES!
	@REM call :separator

	for %%F in (.\build\lib\*.lib) do (
		set LINK_LIBS=-l %%~nF.lib !LINK_LIBS!
	)
	echo with libraries !LINK_LIBS!
	%GCC%\bin\%ASLINK% -n -m -x -u -w -s %LINK_PATH% %LINK_LIBS% .\build\%PROJECT%.s19 !LFILES! !RFILES! 1>nul || exit \b

	@REM if aslink can handle wild cards, then the following (much easier) call is sufficient:
	@REM %GCC%\bin\%ASLINK% -m -u -w -s -k %GCC%\vectrex\lib\system\ -k  %GCC%\vectrex\lib\lib\ -l rum.lib -l gcc.lib -l libgcc.lib -l assert.lib .\build\%PROJECT%.s19 %GCC%\vectrex\lib\system\static\*.rel .\build\rel\*.rel

exit /B 0

:build - PROJECT
	set PROJECT=%1
	%GCC%\bin\srec2bin.exe -q .\build\%PROJECT%_rom.s19 .\build\%PROJECT%_rom.bin || exit \b
	call :getFilesize .\build\%PROJECT%_rom.bin
	@REM echo rom size is !fileSize! bytes
	if exist .\build\%PROJECT%_ram.s19 (
		%GCC%\bin\srec2bin.exe -q -o -0xc880 .\build\%PROJECT%_ram.s19 .\build\%PROJECT%_ram.bin || exit \b
		call :getFilesize .\build\%PROJECT%_ram.bin
		@REM @echo ram size is !fileSize! bytes
	)
	
	%GCC%\bin\findstr "\.cartridge" build\%PROJECT%.map
	%GCC%\bin\findstr "\.text" build\%PROJECT%.map
	%GCC%\bin\findstr "\.data" build\%PROJECT%.map
	%GCC%\bin\findstr "\.bss" build\%PROJECT%.map

	call :separator

	echo building %PROJECT%.bin
	if exist .\build\%PROJECT%_ram.bin (
		@copy /b .\build\%PROJECT%_rom.bin+.\build\%PROJECT%_ram.bin .\bin\%PROJECT%.bin 1>nul || exit \b
	) else (
		@copy /b .\build\%PROJECT%_rom.bin .\bin\%PROJECT%.bin 1>nul || exit \b
	)
	@REM @copy /b .\bin\%PROJECT%.bin .\flash\files 1>nul || exit \b
	call :getFilesize .\bin\%PROJECT%.bin
	@echo bin size is !fileSize! bytes
exit /B 0

@REM ---------------------------------------------------------------------------------------------
@REM make target procedures, do not edit

:make_clean - PROJECT
	set PROJECT=%1
	call :separator
	echo cleaning project %PROJECT% ...
	call :clean
exit /B 0

:make_compile - PROJECT OPT
	setlocal enableextensions enabledelayedexpansion
	set PROJECT=%1
	set OPT=%2
	call :make_clean %PROJECT% %OPT%
	call :separator
	echo compiling project %PROJECT% ...
	for /R source %%F in (*.c) do (
		call :line
		set DRIVE=%%~dF
		set ABS_PATH=!DRIVE!%%~pF
		set REL_PATH=!ABS_PATH:%CD%\source\=!
		set ABS_FILE=%%~nF
		set REL_FILE=!ABS_FILE:%CD%\source\=!
		call :compile !REL_FILE! build\src %OPT% !REL_PATH! 
	)
	if [%ENABLE_ASSEMBLY_OPTIMIZATION%]==[yes] (
		set ASS_OPT=0
		call :separator
		echo optimizing project %PROJECT% ...
		call :line
		for /R build\src %%F in (*.s) do (
			set DRIVE=%%~dF
			set ABS_PATH=!DRIVE!%%~pF
			set REL_PATH=!ABS_PATH:%CD%\build\src\=!
			set ABS_FILE=%%~nF
			set REL_FILE=!ABS_FILE:%CD%\build\src\=!
			call :optimize !REL_PATH!!REL_FILE! build\src
			set /a "ASS_OPT=!ASS_OPT! + !ERRORLEVEL!"
		)
		call :line
		if !ASS_OPT! == 1 (
			echo !ASS_OPT! line optimized in all files
		) else (
			echo !ASS_OPT! lines optimized in all files
		)
	)
exit /B 0

:make_assemble - PROJECT OPT
	set PROJECT=%1
	set OPT=%2
	call :make_compile %PROJECT% %OPT%
	if exist build/src/lib (
		call :separator
		echo assembling libraries of project %PROJECT% ...
		rmdir /s /q build\lib
		@move build/src/lib build 1>nul || exit \b
		REM @copy .\source\lib\*.lib .\build\lib 1>nul || exit \b
		call :separator
		for /R build/lib %%F in (*.s) do (
			call :line
			set DRIVE=%%~dF
			set ABS_PATH=!DRIVE!%%~pF
			set REL_PATH=!ABS_PATH:%CD%\build\lib\=!
			set ABS_FILE=%%~nF
			set REL_FILE=!ABS_FILE:%CD%\build\lib\=!
			call :assemble build/lib build/lib/!REL_PATH! !REL_FILE! !REL_PATH! 

			if not [!REL_PATH!]==[] (
				set REL_PATH=!REL_PATH:/=!
				set REL_PATH=!REL_PATH:\=!
			)
			echo \!REL_PATH!\!REL_FILE!.rel >> .\build\lib\!REL_PATH!.lib
		)
	)
	call :separator
	echo assembling source of project %PROJECT% ...
	for /R build/src %%F in (*.s) do (
		call :line
		set DRIVE=%%~dF
		set ABS_PATH=!DRIVE!%%~pF
		set REL_PATH=!ABS_PATH:%CD%\build\src\=!
		set ABS_FILE=%%~nF
		set REL_FILE=!ABS_FILE:%CD%\build\src\=!
		call :assemble build/src build/rel !REL_FILE! !REL_PATH! !REL_PATH!
	)
exit /B 0

:make_link - PROJECT OPT
	set PROJECT=%1
	set OPT=%2
	call :make_assemble %PROJECT% %OPT%
	call :separator
	echo linking project %PROJECT% ...
	call :link %PROJECT%
exit /B 0

:make_build - PROJECT OPT
	set PROJECT=%1
	set OPT=%2
	call :make_link %PROJECT% %OPT%
	call :separator
	echo building project %PROJECT% ...
	call :build %PROJECT%
exit /B 0

@REM ---------------------------------------------------------------------------------------------
@REM epxerimental linting script for ccpcheck

:make_lint - PROJECT
	set PROJECT=%1
	set FILES=
	call :separator
	echo linting project %PROJECT% ...
	start /B /W C:\Programme\Cppcheck\cppcheck -j 1 --quiet -D CPPCHECK --platform=vectrex --language=c --std=c99 --template=gcc --enable=all --suppress=arithOperationsOnVoidPointer --suppress=unusedLabel -I %GCC%\vectrex\include\system -I %GCC%\vectrex\include\lib .\source
	REM start /B /W C:\Programme\Cppcheck\cppcheck -j 1 --quiet -D CPPCHECK -D INLINE_RUM=0 --platform=vectrex --language=c --std=c99 --enable=warning,style,performance,portability,information,unusedFunction,missingInclude --template=gcc --suppress=arithOperationsOnVoidPointer --suppress=unusedLabel -I %GCC%\vectrex\include\system -I %GCC%\vectrex\include\lib %GCC%\vectrex\source .\source
	REM start /B /W C:\Programme\Cppcheck\cppcheck --std=c99 --quiet -j 1 -D CPPCHECK -D INLINE_RUM=0 --platform=vectrex --enable=all --template=gcc --suppress=arithOperationsOnVoidPointer -I %GCC%\vectrex\include\system -I %GCC%\vectrex\include\lib .\source
	REM start /B /W C:\Programme\Cppcheck\cppcheck -j 1 -D INLINE_RUM=0 --platform=vectrex --language=c --enable=unusedFunction --std=c99 --template=gcc --suppress=arithOperationsOnVoidPointer -I %GCC%\vectrex\include\system -I %GCC%\vectrex\include\lib .\source\level.c
	REM FOR /L %%I IN (1,1,99999) DO REM adapt delay loop if output is interleaved
exit /B 0

@REM ---------------------------------------------------------------------------------------------
@REM run script for ParaJVE

:make_run - PROJECT
	set PROJECT=%1
	call :separator
	@del ..\..\ParaJVE\project\project.bin
	@copy .\bin\%PROJECT%.bin ..\..\ParaJVE\project\project.bin 1>nul || exit \b
	@del ..\..\ParaJVE\project\project.png
	@copy .\overlay\%PROJECT%.png ..\..\ParaJVE\project\project.png 1>nul
	@del ..\..\ParaJVE\project\project.pdf
	@copy .\manual\%PROJECT%.pdf ..\..\ParaJVE\project\project.pdf 1>nul
	echo running project %PROJECT% ...
	start "%PROJECT%" /D ..\..\ParaJVE ParaJVE.exe -game="PROJECT" -config="project/configuration.xml"
exit /B 0

@REM ---------------------------------------------------------------------------------------------
@REM make targets, do not edit

:make - TARGET PROJECT OPT
	set TARGET=%1
	set PROJECT=%2
	set "OPT=%3"
	@if %TARGET% == clean (
		@call :make_clean %PROJECT%
	) else if %TARGET% == preprocess (
		@call :make_preprocess %PROJECT% %OPT%
	) else if %TARGET% == compile (
		@call :make_compile %PROJECT% %OPT%
	) else if %TARGET% == optimize (
		@call :make_optimize %PROJECT% %OPT%
	) else if %TARGET% == assemble (
		@call :make_assemble %PROJECT% %OPT%
	) else if %TARGET% == link (
		@call :make_link %PROJECT% %OPT%
	) else if %TARGET% == build (
		@call :make_build %PROJECT% %OPT%
	) else if %TARGET% == lint (
		@call :make_lint %PROJECT%
	) else if %TARGET% == run (
		@call :make_run %PROJECT%
	) else (
		@echo ERROR - unknown target: clean, preprocess, compile, optimize, assemble, link, build, lint, run
		@exit /B 1
	)
	call :separator
	echo done
	call :separator
exit /B 0

@REM ---------------------------------------------------------------------------------------------
@REM main procedure, do not edit

:main - TARGET OPT
	set TARGET=%1
	if [%TARGET%] == [] (
		set TARGET=build
	)
	set OPT=%2
	if [%OPT%] == [] (
		set "OPT=-O0"
	)
	set PROJECT=
	for %%i in (.) do @set PROJECT=%%~ni
	if [%PROJECT%] == [] (
		@echo ERROR - could not determine project name
		@exit /B 1		
	) else (
		call :make %TARGET% %PROJECT% %OPT%
	)
exit /B 0

@REM ---------------------------------------------------------------------------------------------

