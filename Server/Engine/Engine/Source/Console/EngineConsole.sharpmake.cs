using System.IO;
using Sharpmake;

[Generate]
public class EngineConsole : CommonProject
{
    public EngineConsole() { }
    public override void ConfigureAll(Configuration conf, EngineTarget target)
    {
        base.ConfigureAll(conf, target);
        conf.SolutionFolder = "Engine";
        conf.Output = Configuration.OutputType.Exe;

        conf.AddPublicDependency<Launch>(target);
        conf.EventPreBuild.Add("msbuild EngineConfig.vcxproj /p:platform=x64 /p:configuration=\"Debug Client\"");
    }
}
