// Copyright (c) 2020 Nineva Studios

using UnrealBuildTool;
using System.Collections.Generic;
using System.IO;
using System;

#if UE_5_0_OR_LATER
using EpicGames.Core;

#else
using Tools.DotNETCommon;
#endif

public class GooglePlayGoodies : ModuleRules
{
	public GooglePlayGoodies(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new[] { "Core" });
		PrivateDependencyModuleNames.AddRange(new[] { "CoreUObject", "Engine", "Projects" });

		CheckConflictingPlugins(Target);

		var PluginPath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);

		if (Target.Platform == UnrealTargetPlatform.Android)
		{
			PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "Private/Android"));
			PublicDependencyModuleNames.Add("Launch");

			AdditionalPropertiesForReceipt.Add("AndroidPlugin",
				Path.Combine(PluginPath, "GooglePlayGoodies_Android_UPL.xml"));
		}
	}

	private void CheckConflictingPlugins(ReadOnlyTargetRules Target)
	{
		Console.WriteLine("Engine Directory:" + EngineDirectory);

		var pluginList = new List<PluginInfo>();
		pluginList.AddRange(
			Plugins.ReadProjectPlugins(new DirectoryReference(EngineDirectory)));

		if (Target.ProjectFile != null)
		{
			Console.WriteLine("Project Directory:" + Target.ProjectFile.Directory);
			pluginList.AddRange(Plugins.ReadEnginePlugins(Target.ProjectFile.Directory));
		}

		if (Target.Platform != UnrealTargetPlatform.Android)
		{
			return;
		}

		ProjectDescriptor projectDescriptor = null;
		if (Target.ProjectFile != null)
		{
			projectDescriptor = ProjectDescriptor.FromFile(Target.ProjectFile);
		}

		const string onlineSubsystemPluginName = "OnlineSubsystemGooglePlay";

		foreach (var plugin in pluginList)
		{
			if (plugin.Name != onlineSubsystemPluginName)
			{
				continue;
			}

			if (Plugins.IsPluginEnabledForTarget(plugin, projectDescriptor, Target.Platform, Target.Configuration,
				    Target.Type))
			{
				Log.TraceWarning(
					"Google Play Goodies plugin is incompatible with UE4 built-in Online Subsystem. Please, disable the " +
					onlineSubsystemPluginName + " plugin.");
			}
		}
	}
}