// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SetIsSearchingStatus.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTTask_SetIsSearchingStatus::UBTTask_SetIsSearchingStatus(const FObjectInitializer& ObjectInitializer)
{
	NodeName = TEXT("Set Search Status");
}

EBTNodeResult::Type UBTTask_SetIsSearchingStatus::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), true);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
}
