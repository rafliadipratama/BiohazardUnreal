using UnrealBuildTool;
using System.Collections.Generic;

public class BiohazardUnrealEditorTarget : TargetRules
{
	public BiohazardUnrealEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		ExtraModuleNames.Add("BiohazardUnreal");
	}
}
