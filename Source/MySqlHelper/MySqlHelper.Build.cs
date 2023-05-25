// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class MySqlHelper : ModuleRules
{
	public MySqlHelper(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		string thirdPartyPath = Path.Combine(ModuleDirectory, "../ThirdParty");
		string mysqlxPath = Path.Combine(thirdPartyPath, "MySqlX");
		
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		// add include 
		PrivateIncludePaths.AddRange(
			new string[] {
				Path.Combine(mysqlxPath,"include")
			}
			);
		// add lib
		PublicAdditionalLibraries.Add(Path.Combine(mysqlxPath,"lib64","vs14","mysqlcppconn8-static.lib"));
		PublicAdditionalLibraries.Add(Path.Combine(mysqlxPath,"lib64","vs14","libssl.lib"));
		PublicAdditionalLibraries.Add(Path.Combine(mysqlxPath,"lib64","vs14","libcrypto.lib"));
		// add macro
		PublicDefinitions.Add("STATIC_CONCPP");
		
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
