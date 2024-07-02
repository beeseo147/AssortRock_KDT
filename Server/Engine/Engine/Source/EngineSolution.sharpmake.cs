using System;
using System.IO;
using Sharpmake;

[module: Include("%EngineDir%/Engine/Source/CommonProject.sharpmake.cs")]
[module: Include("%EngineDir%/Engine/Source/Console/EngineConsole.sharpmake.cs")]
[module: Include("%EngineDir%/Engine/Source/Runtime/**/*.sharpmake.cs")]
[module: Include("Utils.cs")]

[Generate]
public class EngineSolution : Solution
{
    public EngineSolution() : base(typeof(EngineTarget))
    {
        IsFileNameToLower = false;
		Name = "Engine";

        AddTargets(new EngineTarget(
            ELaunchType.Editor | ELaunchType.Client | ELaunchType.Server,
            Platform.win64,
            DevEnv.vs2022,
            Optimization.Debug | Optimization.Release));
    }

    [Configure()]
    public virtual void ConfigureAll(Configuration conf, EngineTarget target)
    {
        Utils.MakeConfiturationNameDefine(conf, target);

        conf.SolutionFileName = "Engine";
        conf.SolutionPath = Utils.GetSolutionDir();
        string ProjectFilesDir = conf.SolutionPath + @"\Intermediate\ProjectFiles";
        Environment.SetEnvironmentVariable("ProjectFilesDir", ProjectFilesDir);

        // Add Projects
        {
            // dll
            conf.AddProject<Core>(target);
            conf.AddProject<Engine>(target);
            conf.AddProject<Launch>(target);

            // exe
            conf.AddProject<EngineConsole>(target);
        }
    }
}