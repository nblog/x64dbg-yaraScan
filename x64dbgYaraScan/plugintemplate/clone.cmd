@echo off


cd %~dp0

:: x64dbg version
set snapshot=snapshot_2023-08-01_14-50

set GIT=https://github.com/x64dbg/PluginTemplate/

setlocal enabledelayedexpansion

set PLUGIN[0]=plugin
set PLUGIN[1]=pluginmain

:: plugintemplate
for /l %%i in (0, 1, 1) do ( curl -L %GIT%blob/main/src/!PLUGIN[%%i]!.h?raw=true -o !PLUGIN[%%i]!.h && curl -L %GIT%blob/main/src/!PLUGIN[%%i]!.cpp?raw=true -o !PLUGIN[%%i]!.cpp )


:: pluginsdk
curl -L https://github.com/x64dbg/x64dbg/releases/download/snapshot/%snapshot%.zip -o x64dbg.zip
tar -xf x64dbg.zip pluginsdk/
del /Q x64dbg.zip