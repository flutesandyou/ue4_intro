// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Intro : ModuleRules
{
	public Intro(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "MyFirstModule", "PhysXVehicles" });

        PrivateIncludePaths.AddRange(
		new string[] {
			"Intro", "Intro/Actors",
			// ... add other private include paths required here ...
			}
		);
    }
}
