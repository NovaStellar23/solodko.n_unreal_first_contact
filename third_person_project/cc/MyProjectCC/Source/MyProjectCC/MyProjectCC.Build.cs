// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MyProjectCC : ModuleRules
{
	public MyProjectCC(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
