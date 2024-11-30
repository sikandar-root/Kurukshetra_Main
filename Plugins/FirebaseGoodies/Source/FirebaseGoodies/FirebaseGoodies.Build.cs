// Copyright (c) 2022 Nineva Studios

using System.IO;
using UnrealBuildTool;

#if UE_5_0_OR_LATER
using EpicGames.Core;

#else
using Tools.DotNETCommon;
#endif

public class FirebaseGoodies : ModuleRules
{
	public FirebaseGoodies(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(new[] { Path.Combine(ModuleDirectory, "Public") });
		PrivateIncludePaths.AddRange(new[] { Path.Combine(ModuleDirectory, "Private") });

		PublicDependencyModuleNames.AddRange(new[] { "Core" });

		PrivateDependencyModuleNames.AddRange(
			new[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"XmlParser",
				"Json",
				"Projects"
			}
		);

		var EnableEditorSupport = false;

		if (Target.ProjectFile != null)
		{
			var ProjectPath = Path.GetDirectoryName(Target.ProjectFile.ToString());
			var Ini = ConfigCache.ReadHierarchy(ConfigHierarchyType.Engine, new DirectoryReference(ProjectPath), Target.Platform);

			bool TempBool;
			if (Ini.TryGetValue("/Script/FirebaseGoodies.FirebaseGoodiesSettings", "bEnableEditorSupport", out TempBool))
				EnableEditorSupport = TempBool;

			// if (Target.Platform == UnrealTargetPlatform.Mac && Target.Version.MajorVersion >= 5)
			// 	EnableEditorSupport = false;

			PublicDefinitions.Add("FG_ENABLE_EDITOR_SUPPORT=" + (EnableEditorSupport ? "1" : "0"));
			if (EnableEditorSupport)
			{
				PublicDefinitions.Add("FIREBASE_PLATFORM_ANDROID=0");
				PublicDefinitions.Add("FIREBASE_PLATFORM_IOS=0");
				PublicDefinitions.Add("FIREBASE_PLATFORM_TVOS=0");
			}
		}

		if (Target.Platform == UnrealTargetPlatform.Mac && EnableEditorSupport)
		{
			HandleCommonDesktop(Target);
			HandleOsX(Target);
		}

		if (Target.Platform == UnrealTargetPlatform.Win64 && EnableEditorSupport)
		{
			HandleCommonDesktop(Target);
			HandleWindows(Target);
		}

		if (Target.Platform == UnrealTargetPlatform.Android)
		{
			HandleAndroid(Target);
		}

		if (Target.Platform == UnrealTargetPlatform.IOS)
		{
			HandleIos(Target);
		}
	}

	void HandleCommonDesktop(ReadOnlyTargetRules Target)
	{
		PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "../ThirdParty", Target.Platform.ToString(), "includes"));

		PublicDefinitions.Add("INTERNAL_EXPERIMENTAL");

		PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "Private/Desktop"));
		PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "Private/RemoteConfig/Desktop"));
		PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "Private/Database/Desktop"));
		PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "Private/Auth/Desktop"));
	}

	void HandleWindows(ReadOnlyTargetRules Target)
	{
		LoadThirdPartyLibrary("firebase_app", Target);
		LoadThirdPartyLibrary("firebase_analytics", Target);
		LoadThirdPartyLibrary("firebase_auth", Target);
		LoadThirdPartyLibrary("firebase_database", Target);
		LoadThirdPartyLibrary("firebase_dynamic_links", Target);
		LoadThirdPartyLibrary("firebase_functions", Target);
		LoadThirdPartyLibrary("firebase_firestore", Target);
		LoadThirdPartyLibrary("firebase_installations", Target);
		LoadThirdPartyLibrary("firebase_messaging", Target);
		LoadThirdPartyLibrary("firebase_remote_config", Target);
		LoadThirdPartyLibrary("firebase_storage", Target);

		PublicSystemLibraries.Add("crypt32.lib");
		PublicSystemLibraries.Add("advapi32.lib");
		PublicSystemLibraries.Add("ws2_32.lib");
		PublicSystemLibraries.Add("rpcrt4.lib");
		PublicSystemLibraries.Add("ole32.lib");
		PublicSystemLibraries.Add("shell32.lib");
		PublicSystemLibraries.Add("dbghelp.lib");
		PublicSystemLibraries.Add("bcrypt.lib");
		PublicSystemLibraries.Add("iphlpapi.lib");
		PublicSystemLibraries.Add("psapi.lib");
		PublicSystemLibraries.Add("userenv.lib");
		PublicSystemLibraries.Add("icu.lib");
	}

	void HandleOsX(ReadOnlyTargetRules Target)
	{
		LoadThirdPartyLibrary("libfirebase_app", Target);
		LoadThirdPartyLibrary("libfirebase_analytics", Target);
		LoadThirdPartyLibrary("libfirebase_auth", Target);
		LoadThirdPartyLibrary("libfirebase_database", Target);
		LoadThirdPartyLibrary("libfirebase_dynamic_links", Target);
		LoadThirdPartyLibrary("libfirebase_functions", Target);
		LoadThirdPartyLibrary("libfirebase_firestore", Target);
		LoadThirdPartyLibrary("libfirebase_installations", Target);
		LoadThirdPartyLibrary("libfirebase_messaging", Target);
		LoadThirdPartyLibrary("libfirebase_remote_config", Target);
		LoadThirdPartyLibrary("libfirebase_storage", Target);

		PublicFrameworks.AddRange(
			new[]
			{
				"CoreFoundation",
				"Foundation",
				"Security",
				"SystemConfiguration",
				"GSS",
				"Kerberos",
			}
		);
	}

	void HandleIos(ReadOnlyTargetRules Target)
	{
		// Swift support
		var SDKROOT = Utils.RunLocalProcessAndReturnStdOut("/usr/bin/xcrun", "--sdk iphoneos --show-sdk-path");
		PublicSystemLibraryPaths.Add(SDKROOT + "/usr/lib/swift");
		PublicSystemLibraryPaths.Add(SDKROOT + "../../../../../../Toolchains/XcodeDefault.xctoolchain/usr/lib/swift/iphoneos");
		PublicSystemLibraryPaths.Add(SDKROOT + "../../../../../../Toolchains/XcodeDefault.xctoolchain/usr/lib/swift-5.0/iphoneos");
		PublicSystemLibraryPaths.Add(SDKROOT + "../../../../../../Toolchains/XcodeDefault.xctoolchain/usr/lib/swift-5.5/iphoneos");

		PublicFrameworks.AddRange(
			new[]
			{
				"LocalAuthentication",
				"SafariServices",
				"AuthenticationServices",
				"SystemConfiguration",
				"UserNotifications"
			}
		);

		var firebaseFrameworks = new[]
		{
			"FBLPromises",
			"FirebaseAnalytics",
			"FirebaseCore",
			"FirebaseCoreInternal",
			"FirebaseInstallations",
			"GoogleAppMeasurement",
			"GoogleAppMeasurementIdentitySupport",
			"GoogleUtilities",
			"nanopb",
			"FirebaseAppCheckInterop",
			"FirebaseAuth",
			"GTMSessionFetcher",
			"RecaptchaInterop",
			"FirebaseCoreExtension",
			"FirebaseCrashlytics",
			"FirebaseRemoteConfigInterop",
			"FirebaseSessions",
			"GoogleDataTransport",
			"Promises",
			"FirebaseDatabase",
			"FirebaseSharedSwift",
			"leveldb",
			"FirebaseStorage",
			"FirebaseFirestore",
			"FirebaseFirestoreInternal",
			"absl",
			"grpc",
			"grpcpp",
			"openssl_grpc",
			"FirebaseAuthInterop",
			"FirebaseFunctions",
			"FirebaseMessagingInterop",
			"FirebaseMessaging",
			"FirebaseABTesting",
			"FirebaseRemoteConfig",
			"FirebaseRemoteConfig",
			"AppAuth",
			"AppCheckCore",
			"GTMAppAuth",
			"GoogleSignIn",
			"FirebaseDynamicLinks",
		};

		foreach (var firebaseFramework in firebaseFrameworks)
		{
			AddIosFramework(firebaseFramework);
		}

		AddIosFramework("GTMSessionFetcher", "GTMSessionFetcher_Core_Privacy");

		PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "Private/IOS"));
		PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "Private/RemoteConfig/IOS"));
		PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "Private/Database/IOS"));
		PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "Private/Auth/IOS"));

		var EnableDynamicLinksForIos = false;

		if (Target.ProjectFile != null)
		{
			var ProjectPath = Path.GetDirectoryName(Target.ProjectFile.ToString());
			var Ini = ConfigCache.ReadHierarchy(ConfigHierarchyType.Engine, new DirectoryReference(ProjectPath), Target.Platform);

			bool TempBool;
			if (Ini.TryGetValue("/Script/FirebaseGoodies.FirebaseGoodiesSettings", "EnableDynamicLinksForIos", out TempBool))
				EnableDynamicLinksForIos = TempBool;
		}

		PublicDefinitions.Add("DYNAMIC_LINKS_IOS=" + (EnableDynamicLinksForIos ? "1" : "0"));

		PublicDependencyModuleNames.AddRange(new[] { "Launch" });
		PrivateDependencyModuleNames.AddRange(new[] { "Launch" });
		var PluginPath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);

		AdditionalPropertiesForReceipt.Add("IOSPlugin", Path.Combine(PluginPath, "FirebaseGoodies_IOS_UPL.xml"));
	}

	void AddIosFramework(string name, string bundle = null)
	{
		var frameworkPath = $"../ThirdParty/IOS/{name}.embeddedframework.zip";
		if (bundle == null)
		{
			PublicAdditionalFrameworks.Add(new Framework(name, frameworkPath));
		}
		else
		{
			PublicAdditionalFrameworks.Add(new Framework(name, frameworkPath, $"{name}.framework/Resources/{bundle}.bundle"));
		}
	}

	void HandleAndroid(ReadOnlyTargetRules Target)
	{
		PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "Private/Android"));
		PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "Private/RemoteConfig/Android"));
		PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "Private/Database/Android"));
		PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "Private/Auth/Android"));

		PublicDependencyModuleNames.AddRange(new[] { "Launch" });
		PrivateDependencyModuleNames.AddRange(new[] { "Launch" });
		var PluginPath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);

		AdditionalPropertiesForReceipt.Add("AndroidPlugin", Path.Combine(PluginPath, "FirebaseGoodies_Android_UPL.xml"));
	}

	public void LoadThirdPartyLibrary(string libname, ReadOnlyTargetRules Target)
	{
		var StaticLibExtension = string.Empty;

		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			StaticLibExtension = ".lib";
		}

		if (Target.Platform == UnrealTargetPlatform.Mac)
		{
			StaticLibExtension = ".a";
		}

		var ThirdPartyPath = Path.Combine(ModuleDirectory, "../ThirdParty", Target.Platform.ToString());
		var LibrariesPath = Path.Combine(ThirdPartyPath, "libraries");

		// Link static library (desktop only)
		if (Target.Platform == UnrealTargetPlatform.Win64 || Target.Platform == UnrealTargetPlatform.Mac)
		{
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, libname + StaticLibExtension));
		}
	}
}