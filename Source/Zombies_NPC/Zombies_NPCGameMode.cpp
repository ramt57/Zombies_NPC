// Copyright Epic Games, Inc. All Rights Reserved.

#include "Zombies_NPCGameMode.h"
#include "Zombies_NPCCharacter.h"
#include "UObject/ConstructorHelpers.h"

AZombies_NPCGameMode::AZombies_NPCGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
