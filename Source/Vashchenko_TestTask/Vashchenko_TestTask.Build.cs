// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Vashchenko_TestTask : ModuleRules
{
	public Vashchenko_TestTask(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
