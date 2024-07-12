// Copyright (c) Ubisoft. All Rights Reserved.
// Licensed under the Apache 2.0 License. See LICENSE.md in the project root for license information.
using System;
using System.IO;
using Sharpmake;

[module: Include(@"%EngineDir%/Engine/Source/UserProject.sharpmake.cs")]

[Generate]
public class ServerProject : UserProject
{
    public ServerProject()
    {
        Name = "ServerProject";
    }

    public override void ConfigureAll(Configuration conf, EngineTarget target)
    {
        base.ConfigureAll(conf, target);

        if (target.LaunchType == ELaunchType.Server)
        {
            conf.AddPublicDependency<Network>(target);
        }
    }
}