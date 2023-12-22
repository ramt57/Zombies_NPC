﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ZombieActionInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UZombieActionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ZOMBIES_NPC_API IZombieActionInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Combat")
	int MeleeAttack();
};
