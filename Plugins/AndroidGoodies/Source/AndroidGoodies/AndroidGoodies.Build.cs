// Copyright (c) 2018 Nineva Studios

using System.IO;
using UnrealBuildTool;

public class AndroidGoodies : ModuleRules
{
	public AndroidGoodies(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PrivateDependencyModuleNames.Add("Projects");

		PublicIncludePaths.AddRange(new[] { Path.Combine(ModuleDirectory, "Public") });
		PrivateIncludePaths.AddRange(new[] { Path.Combine(ModuleDirectory, "Private") });

		PublicDependencyModuleNames.AddRange(new[] { "Engine", "Core", "CoreUObject" });

		if (Target.Platform == UnrealTargetPlatform.Android)
		{
			PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "Private/Android"));
			PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "Private/Notifications/Android"));

			PublicDependencyModuleNames.AddRange(new[] { "Launch" });
			var pluginPath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);

			AdditionalPropertiesForReceipt.Add("AndroidPlugin", Path.Combine(pluginPath, "AndroidGoodies_UPL.xml"));
		}
	}
}