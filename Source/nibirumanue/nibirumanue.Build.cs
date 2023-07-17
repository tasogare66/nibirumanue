// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using Tools.DotNETCommon;
using UnrealBuildTool;

public class nibirumanue : ModuleRules
{
	public nibirumanue(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		CppStandard = CppStandardVersion.Cpp17;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "Niagara", "NiagaraCore" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true

		LoadLua(Target);
	}

	private string ThirdPartyPath {
		get { return Path.GetFullPath(Path.Combine(ModuleDirectory, "../../ThirdParty/")); }
	}

	private void LoadLua(ReadOnlyTargetRules Target)
	{
		// Check if we are on Windows
		if ((Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Win32)) {
			string LuaVer = "5.4.6";
			string LuaLib = "lua-"+LuaVer;
			string LuaPath = Path.Combine(ThirdPartyPath, "Lua", LuaLib);

			string PlatformString = (Target.Platform == UnrealTargetPlatform.Win64) ? "win64" : "x86";

			// This string is either "x64" or "x86" so we can append it on the lib filename
			string LibrariesPath = Path.Combine(LuaPath, "lib", PlatformString);
			Log.TraceInformation("Lua lib: {0}", LibrariesPath);

			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "lua"+LuaVer+"-static.lib"));

			PublicIncludePaths.Add(Path.Combine(LuaPath, "src"));
		}
		else
		{
			Log.TraceError("unsupported");
		}
	}
}
