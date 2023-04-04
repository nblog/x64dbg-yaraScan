@echo off


cd %~dp0


set GHPROXY=https://ghproxy.com/
set GIT=%GHPROXY%https://github.com/avast/retdec/

setlocal enabledelayedexpansion

set YARACPP[0]=yara_detector
set YARACPP[1]=yara_match
set YARACPP[2]=yara_meta
set YARACPP[3]=yara_rule


:: HEAD FILE
mkdir retdec\yaracpp && for /l %%i in (0, 1, 3) do ( curl -L %GIT%blob/master/include/retdec/yaracpp/!YARACPP[%%i]!.h?raw=true -o retdec\yaracpp\!YARACPP[%%i]!.h )

:: SRC FILE
mkdir yaracpp && for /l %%i in (0, 1, 3) do ( curl -L %GIT%blob/master/src/yaracpp/!YARACPP[%%i]!.cpp?raw=true -o yaracpp\!YARACPP[%%i]!.cpp )