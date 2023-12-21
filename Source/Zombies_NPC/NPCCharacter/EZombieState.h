#pragma once

UENUM(BlueprintType)
enum class EZombieState : uint8
{
	ETIP_IDLE UMETA(DisplayName = "IDLE"),
	ETIP_ROAM UMETA(DisplayName = "ROAM"),
	ETIP_SEARCH UMETA(DisplayName = "Search"),
	ETIP_CHASE UMETA(DisplayName = "Chase"),
	ETIP_HYPER_CHASE UMETA(DisplayName = "Hyper Chase"),
	ETIP_SCAVENGING UMETA(DisplayName = "SCAVENGE"),
};
