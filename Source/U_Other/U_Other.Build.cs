// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class U_Other : ModuleRules
{
	public U_Other(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"U_Other",
			"U_Other/Variant_Platforming",
			"U_Other/Variant_Platforming/Animation",
			"U_Other/Variant_Combat",
			"U_Other/Variant_Combat/AI",
			"U_Other/Variant_Combat/Animation",
			"U_Other/Variant_Combat/Gameplay",
			"U_Other/Variant_Combat/Interfaces",
			"U_Other/Variant_Combat/UI",
			"U_Other/Variant_SideScrolling",
			"U_Other/Variant_SideScrolling/AI",
			"U_Other/Variant_SideScrolling/Gameplay",
			"U_Other/Variant_SideScrolling/Interfaces",
			"U_Other/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
