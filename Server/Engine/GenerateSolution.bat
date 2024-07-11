@echo off
echo %1

REM EngineDir은 EngineSolution.sharpmake.cs에서 사용 됩니다.
set EngineDir=%cd%
IF NOT "%~1"=="" set "EngineDir=%~1"
echo EngineDir은 %EngineDir%

REM TargetCS는 sharpmake에 진입점이 될 cs파일의 경로입니다.
set TargetCS=%EngineDir%\Engine\Source\EngineMain.sharpmake.cs
IF NOT "%~2"=="" set TargetCS="%2"
echo TargetCS는 %TargetCS%

REM SharpMakeSolutionDir은 최종 Sln 파일이 만들어질 위치가 됩니다.
REM SharpMakeSolutionDir은 EngineSolution.sharpmake.cs에서 사용 됩니다.
set SharpMakeSolutionDir=%cd%
IF NOT "%~3"=="" set SharpMakeSolutionDir="%3"
echo SharpMakeSolutionDir은 %SharpMakeSolutionDir%

"%EngineDir%\Engine\Source\Programs\Sharpmake\Sharpmake.Application\bin\Release\net6.0\Sharpmake.Application.exe" /sources(@'%TargetCS%') /verbose