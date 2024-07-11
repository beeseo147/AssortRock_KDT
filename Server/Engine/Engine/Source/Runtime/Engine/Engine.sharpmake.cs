// Copyright (c) Ubisoft. All Rights Reserved.
// Licensed under the Apache 2.0 License. See LICENSE.md in the project root for license information.
using System;
using System.IO;
using Sharpmake;

[Generate]
public class Engine : CommonProject
{
    public Engine() { }

    public override void ConfigureAll(Configuration conf, EngineTarget target)
    {
        base.ConfigureAll(conf, target);
        conf.SolutionFolder = @"Engine/Source/Runtime";
        conf.AddPublicDependency<Core>(target);

        //conf.AddPublicDependency<Engine>(target);
        //conf.AddPublicDependency<EngineSettings>(target);
        //if (target.LaunchType == ELaunchType.Editor)
        //{
        //    conf.AddPublicDependency<EngineEd>(target);
        //}
    }
}