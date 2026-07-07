#pragma once

UENUM(BlueprintType, Blueprintable)
enum class EDevice : uint8
{
	Null,
	JunctionBox,
	Valve,
	Door,
	Lamp,
	Drawer
};