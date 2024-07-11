// Copyright (c) Ubisoft. All Rights Reserved.
// Licensed under the Apache 2.0 License. See LICENSE.md in the project root for license information.
using System;
using System.IO;
using System.Collections.Generic;
using Sharpmake;

[module: Include(@"Utils.cs")]

public abstract class UserProject : CommonProject
{
    protected UserProject() { }

    public override void ConfigureAll(Configuration conf, EngineTarget target)
    {
        base.ConfigureAll(conf, target);
        conf.EventPreBuild.Add("msbuild UserConfig.vcxproj /p:platform=x64 /p:configuration=\"Debug Client\"");

        conf.TargetPath += @"/Project"; // Do not edit TargetPath
        conf.SolutionFolder = @"Game";
        conf.AddPublicDependency<Engine>(target);
    }
}