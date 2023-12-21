// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ClearBlackBoardKey.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTTask_ClearBlackBoardKey::UBTTask_ClearBlackBoardKey(const FObjectInitializer& ObjectInitializer)
{
	NodeName = TEXT("Clear Selected BlackBoard Key");
}

EBTNodeResult::Type UBTTask_ClearBlackBoardKey::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
