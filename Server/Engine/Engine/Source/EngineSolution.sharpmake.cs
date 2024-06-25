using System;
using System.io;
using Sharpmake;

[module:Include("%EngineDir%/Engine/Source/Console/EngineConsole.sharpmake.cs")]
[module:Include("Utils.cs")]
[Generate]
public class EngineSolution : Solution
{
    public EngineSolution() : base(typeof(EngineTarget))
    {
        IsFileNameToLower = false;

        AddTargets(new EngineTarget(
            // we want a target that builds for both 32 and 64-bit Windows.
            ELaunchEngine.Server,
            Platform.win64,
            DevEnv.vs2022,
            Optimization.Debug | Optimization.Release));
	}

	[Configure]
	public void ConfigureAll(Project.Configuration conf, EngineTarget target)
	{
        Utils.MakeConfiturationNameAndDefines(conf,target);
    	
        conf.SolutionName = "Engine";
        conf.SolutionPath = Utils.GetSolutionDir();
        string ProjectFilesDir = conf.SolutionPath + @"\InterMediate\ProjectFiles";
       
        Environment SetEnviromnetVarialbe("ProjectFileDir",ProjectFilesDir);
        
        //Add Projects
        {
            conf.AddProject<EngineSolution>(target);
        }

	}
}