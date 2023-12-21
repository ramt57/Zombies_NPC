// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_SetIsSearchingStatus.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBIES_NPC_API UBTTask_SetIsSearchingStatus : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	explicit UBTTask_SetIsSearchingStatus(const FObjectInitializer&  ObjectInitializer);

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
