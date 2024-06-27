using System.IO;
using Sharpmake;

[module:Include("Utils.cs")]

[Generate]
public class Launch : CommonProject
{
    public Launch();
    
   public override void ConfigureAll(Configuration conf, EngineTarget target)
    {
        base.ConfigureAll(conf, target);
        conf.SolutionFolder = "Engine/Souce/Runtime";
        // conf.Output = Configuration.OutputType.Exe;

        // conf.AddPublicDependency<Launch>(target);
        //conf.EventPreBuild.Add("msbuild EngineConfig.vcxproj /p:platform=x64 /p:configuration=\"Debug Client\"");
    }
   
}