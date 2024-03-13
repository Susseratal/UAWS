// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Runtime.CompilerServices;

public class dynamoDBDemo : ModuleRules 
{
	private static string GetFilePath([CallerFilePath] string path = null) 
	{
		return path;
	}

	public dynamoDBDemo(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });
		PrivateDependencyModuleNames.AddRange(new string[] {  });

		bEnableUndefinedIdentifierWarnings = false;

		var filePath = GetFilePath();
		var dir = System.IO.Path.GetDirectoryName(filePath);

		PublicIncludePaths.Add(dir + "/include/");
		PublicAdditionalLibraries.Add(dir + "/bin/aws-cpp-sdk-core.lib");
		PublicAdditionalLibraries.Add(dir + "/bin/aws-cpp-sdk-dynamodb.lib");
		PublicAdditionalLibraries.Add(dir + "/bin/testing-resources.lib");
		PublicAdditionalLibraries.Add(dir + "/lib/aws-c-http.lib");
		PublicDefinitions.Add("AWS_USE_IO_COMPLETION_PORTS=1");

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
