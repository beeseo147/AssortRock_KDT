using System.IO;
using Sharpmake;

[module: Include("%EngineDir%/Engine/Source/CommonProject.sharpmake.cs")]

[Generate]
public class EngineConsole : CommonProject
{
    public override void ConfigureAll(Configuration conf, EngineTarget target)
    {
        base.ConfigureAll(conf, target);
        conf.SolutionFolder = "Engine";
        conf.Output = Configuration.OutputType.Exe;

        //conf.AddPublicDependency<Launch>(target);
        //conf.EventPreBuild.Add("msbuild EngineConfig.vcxproj /p:platform=x64 /p:configuration=\"Debug Client\"");
    }
}