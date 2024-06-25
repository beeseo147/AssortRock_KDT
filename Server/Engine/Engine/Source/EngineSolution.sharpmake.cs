using System;
using System.IO;
using Sharpmake;

[module: Include("%EngineDir%/Engine/Source/Console/EngineConsole.sharpmake.cs")]
[module: Include("Utils.cs")]

[Generate]
public class EngineSolution : Solution
{
    public EngineSolution() : base(typeof(EngineTarget))
    {
        IsFileNameToLower = false;

        AddTargets(new EngineTarget(
            // ELaunchType.Editor | ELaunchType.Client | ELaunchType.Server
            ELaunchType.Server,
            Platform.win64,
            DevEnv.vs2022,
            Optimization.Debug | Optimization.Release));
    }

    [Configure]
    public void ConfigureAll(Solution.Configuration conf, EngineTarget target)
    {
        Utils.MakeConfiturationNameDefine(conf, target);

        conf.SolutionFileName = "Engine";
        conf.SolutionPath = Utils.GetSolutionDir();
        string ProjectFilesDir = conf.SolutionPath + @"\Intermediate\ProjectFiles";
        Environment.SetEnvironmentVariable("ProjectFilesDir", ProjectFilesDir);

        // Add Projects
        {
            conf.AddProject<EngineConsole>(target);
        }
    }
}