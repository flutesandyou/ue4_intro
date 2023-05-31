using UnrealBuildTool;

public class MyFirstModule : ModuleRules
{
    public MyFirstModule(ReadOnlyTargetRules TargetRules) : base(TargetRules)
    {
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject" });

    }
}
