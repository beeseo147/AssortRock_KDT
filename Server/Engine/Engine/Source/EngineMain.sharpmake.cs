using System;
using System.IO;
using Sharpmake;

[module:Include("EngineSolution.sharpmake.cs")]

public static class Main
{
    [Sharpmake.Main]
    public static void SharpmakeMain(Sharpmake.Arguments arguments)
    {
        arguments.Generate<EngineSolution>();
    }
}