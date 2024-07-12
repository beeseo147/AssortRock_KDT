// Copyright (c) Ubisoft. All Rights Reserved.
// Licensed under the Apache 2.0 License. See LICENSE.md in the project root for license information.
using System;
using System.IO;
using Sharpmake;

[module: Include(@"%EngineDir%/Engine/Source/EngineSolution.sharpmake.cs")]
[module: Include(@"./**/*.sharpmake.cs")]
[module: Include(@"./*.sharpmake.cs")]
[module: Include(@"../Config/*.sharpmake.cs")]

[Generate]
public class GameSolution : EngineSolution
{
    public override void ConfigureAll(Configuration conf, EngineTarget target)
    {
        base.ConfigureAll(conf, target);
        conf.SolutionFileName = "Server";

        // Add Projects
        {
            conf.AddProject<ServerProject>(target);
            conf.AddProject<UserConfig>(target);
        }
    }
}

public static class Main
{
    [Sharpmake.Main]
    public static void SharpmakeMain(Arguments arguments)
    {
        KitsRootPaths.SetUseKitsRootForDevEnv(DevEnv.vs2022, KitsRootEnum.KitsRoot10, Options.Vc.General.WindowsTargetPlatformVersion.Latest);
        arguments.Generate<GameSolution>();
    }
}