// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_UpdateNPCState.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Chaos/ChaosPerfTest.h"
#include "Zombies_NPC/NPCCharacter/ZombieBase.h"

UBTTask_UpdateNPCState::UBTTask_UpdateNPCState(const FObjectInitializer& ObjectInitializer)
{
	NodeName = TEXT("Update NPC State");
}

EBTNodeResult::Type UBTTask_UpdateNPCState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (AZombieBase* Character = Cast<AZombieBase>(OwnerComp.GetAIOwner()->GetCharacter()))
	{
		Character->SetNpcState(State);
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(GetSelectedBlackboardKey(), static_cast<uint8>(State));
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
