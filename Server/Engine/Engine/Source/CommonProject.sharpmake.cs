using System.IO;
using Sharpmake;

[module:Include("Utils.cs")]

public abstract class CommonProject : Project
{
    protected CommonProject() : base(typeof(EngineTarget))
    {
        Name = GetType().Name;

        IsFileNameToLower = false;
        IsTargetFileNameToLower = false;

        SourceRootPath = @"[project.RootPath]";
        SourceFilesExtensions.Add(".cs");
        //SourceFilesCompileExtensions.Add(".ixx");

        AddTargets(new EngineTarget(
                ELaunchType.Editor | ELaunchType.Client | ELaunchType.Server,
                Platform.win64,
                DevEnv.vs2022,
                Optimization.Debug | Optimization.Release
        ));
    }

    [Configure]
    public virtual void ConfigureAll(Configuration conf, EngineTarget target)
    {
        Utils.MakeConfiturationNameDefine(conf, target);
        conf.DumpDependencyGraph = true;

        // conf.Output = Configuration.OutputType.Exe;
        conf.Output = Configuration.OutputType.Dll;
        //conf.Output = Configuration.OutputType.Lib;
        conf.Options.Add(Options.Vc.General.CharacterSet.Unicode);
        conf.Options.Add(Options.Vc.Compiler.JumboBuild.Enable);
        conf.Options.Add(Options.Vc.Compiler.CppLanguageStandard.CPP20);
        //conf.Options.Add(Options.Vc.Compiler.CppLanguageStandard.Latest);
        if (target.Optimization == Optimization.Debug)
        {
            conf.Options.Add(Options.Vc.Compiler.Inline.Default);

            // Visual Studio 핫리로드 대응
            conf.Options.Add(Options.Vc.Linker.Incremental.Enable);
            conf.Options.Add(Options.Vc.General.DebugInformation.ProgramDatabaseEnC);
            conf.Options.Add(Options.Vc.Compiler.FunctionLevelLinking.Enable);
        }

        // RTTI
        conf.Options.Add(Options.Vc.Compiler.RTTI.Enable);

        conf.ProjectFileName = "[project.Name]";

        // Debug
        {
            conf.VcxprojUserFile = new Configuration.VcxprojUserFileSettings();
            conf.VcxprojUserFile.LocalDebuggerWorkingDirectory = "$(OutputPath)";
        }

        // Path
        {
            conf.ProjectPath = Utils.GetProjectDir();

            string SolutionDir = Utils.GetSolutionDir();
            conf.TargetPath = SolutionDir + @"/Binaries/[target.Optimization]";
            conf.IntermediatePath = SolutionDir + @"/Intermediate/Build/[project.Name]";

            // Include
            {
                //conf.IncludePrivatePaths.Add("[project.SourceRootPath]");
                conf.IncludePrivatePaths.Add(conf.ProjectPath);

                string HeaderParserTargetDir = SolutionDir + @"/Intermediate/HeaderParser/HeaderParserGenerated/[project.Name]";
                conf.IncludePaths.Add(HeaderParserTargetDir);
                conf.IncludePaths.Add(@"[project.SourceRootPath]");
                conf.IncludePaths.Add(@"[project.SourceRootPath]\Public");
            }
        }

        // Runtime Library
        {
            if (target.Optimization == Optimization.Debug)
                conf.Options.Add(Options.Vc.Compiler.RuntimeLibrary.MultiThreadedDebugDLL);
            else
                conf.Options.Add(Options.Vc.Compiler.RuntimeLibrary.MultiThreadedDLL);
        }
        //conf.EventPreBuild.Add("msbuild EngineConfig.vcxproj /p:platform=x64 /p:configuration=\"Debug Client\"");
        //conf.EventPreBuild.Add("msbuild UserConfig.vcxproj /p:platform=x64 /p:configuration=\"Debug Client\"");
        string EngineDir = Utils.GetEngineDir();
        conf.EventPreBuild.Add(@"cmd /c """ + EngineDir + @"\Engine\Source\Programs\HeaderParser\HeaderParser.bat"" $(SolutionDir) [project.Name] [project.SourceRootPath] " + EngineDir);

        // if not set, no precompile option will be used.
        //conf.PrecompHeader = "stdafx.h";
        //conf.PrecompSource = "stdafx.cpp";

        conf.CustomProperties.Add("CustomOptimizationProperty", $"Custom-{target.Optimization}");
    }
}