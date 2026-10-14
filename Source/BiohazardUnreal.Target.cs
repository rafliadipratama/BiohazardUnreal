using UnrealBuildTool;
using System.Collections.Generic;

public class BiohazardUnrealTarget : TargetRules
{
	public BiohazardUnrealTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		ExtraModuleNames.Add("BiohazardUnreal");
	}
}
