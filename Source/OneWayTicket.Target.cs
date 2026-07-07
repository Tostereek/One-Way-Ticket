// Pietrasy's code.

using UnrealBuildTool;
using System.Collections.Generic;

public class OneWayTicketTarget : TargetRules
{
	public OneWayTicketTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V6;

		ExtraModuleNames.AddRange( new string[] { "OneWayTicket" } );
	}
}
