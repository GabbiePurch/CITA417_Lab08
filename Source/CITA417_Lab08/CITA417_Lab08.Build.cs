// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CITA417_Lab08 : ModuleRules
{
	public CITA417_Lab08(ReadOnlyTargetRules Target) : base(Target)
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
			"CITA417_Lab08",
			"CITA417_Lab08/Variant_Platforming",
			"CITA417_Lab08/Variant_Platforming/Animation",
			"CITA417_Lab08/Variant_Combat",
			"CITA417_Lab08/Variant_Combat/AI",
			"CITA417_Lab08/Variant_Combat/Animation",
			"CITA417_Lab08/Variant_Combat/Gameplay",
			"CITA417_Lab08/Variant_Combat/Interfaces",
			"CITA417_Lab08/Variant_Combat/UI",
			"CITA417_Lab08/Variant_SideScrolling",
			"CITA417_Lab08/Variant_SideScrolling/AI",
			"CITA417_Lab08/Variant_SideScrolling/Gameplay",
			"CITA417_Lab08/Variant_SideScrolling/Interfaces",
			"CITA417_Lab08/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
