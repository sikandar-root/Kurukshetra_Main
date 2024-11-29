// Copyright 2024 Gdy Development, Inc. All Rights Reserved.


using UnrealBuildTool;

public class EasyFixAndroidPermission : ModuleRules
{
	public EasyFixAndroidPermission(ReadOnlyTargetRules Target) : base(Target)
	{

        if (Target.Platform == UnrealTargetPlatform.Android)
        {
            PrivateDependencyModuleNames.AddRange(new string[] { "Launch" });

            string manifestFile = System.IO.Path.Combine(ModuleDirectory, "AndroidSanitizePermissions_UPL.xml");
            AdditionalPropertiesForReceipt.Add("AndroidPlugin", manifestFile);
        }


        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
                "AndroidPermission"
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
