using System;
using System.io;
using Sharpmake;

public class Utils
{
    //GenerateSolution.bat 에서 지정됩니다.
    public static string GetEngineDir()
    {
        return Environment.GetEnvironmentVariable("EngineDir");
    }
    //GenerateSolution.bat 에서 지정됩니다.
    public static string GetSolutionDir()
    {
        return Environment.GetEnvironmentVariable("SharpeMakeSolutionDir");
    }
    //EngineSolution.ConfigureAll 에서 지정됩니다.
    public static string GetProjectDir()
    {
        return Environment.GetEnvironmentVariable("ProjectFileDir");
    }
    public static void MakeConfiturationNameAndDefines(Project.Configuration conf,EngineTarget target)
    {
        if(target.Name == "Release"){conf.Name == "Development";}

        {
            if(target.LaunchType == ELaunchType.Editor)
            {
                conf.Name += " Editor";
            }
            else if(target.LaunchType == ELaunchType.Client)
            {
                conf.Name += " Client"
            }
            else if(target.LaunchType == ELaunchType.Server)
            {
                conf.Name += " Server"
            }
        }
       
        {
            conf.Define.Add("SOLUTION_NAME=\"$(SolutionName\"");
            if(target.Name == "Release")
            {
                conf.Define.Add("WITH_DEBUG=0");
            }
            else
            {
                conf.Define.Add("WITH_DEBUG=1");
            }

            if(target.LaunchType == ELaunchType.Editor)
            {
                conf.Define.Add("WITH_DEBUG=1");
            }
            else
            {
                conf.Define.Add("WITH_DEBUG=0");
            }

            if(target.LaunchType == ELaunchType.Client)
            {
                conf.Define.Add("Client=1");
            }
            else
            {
                conf.Define.Add("Client=0");
            }
            if(target.LaunchType == ELaunchType.Server)
            {
                conf.Define.Add("Server=1");
            }
            else
            {
                conf.Define.Add("Server=0");
            }
        }

    }
}