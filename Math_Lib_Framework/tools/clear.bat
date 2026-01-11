cls
@echo off
IF EXIST ..\build rmdir /s /q ..\build
IF EXIST ..\bin rmdir /s /q ..\bin

IF EXIST ..\build\ML_vs2022.sln del /F ..\build\ML_vs2022.sln
