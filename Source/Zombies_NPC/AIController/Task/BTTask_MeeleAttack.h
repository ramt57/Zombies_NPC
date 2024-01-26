// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_MeeleAttack.generated.h"

class AZombieBase;
/**
 * 
 */
UCLASS()
class ZOMBIES_NPC_API UBTTask_MeeleAttack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTTask_MeeleAttack();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
private:
	static bool MontageHasFinished(const ACharacter* Npc);
};
