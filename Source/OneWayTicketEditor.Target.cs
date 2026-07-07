// Pietrasy's code.

using UnrealBuildTool;
using System.Collections.Generic;

public class OneWayTicketEditorTarget : TargetRules
{
	public OneWayTicketEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V6;

		ExtraModuleNames.AddRange( new string[] { "OneWayTicket" } );
	}
}
