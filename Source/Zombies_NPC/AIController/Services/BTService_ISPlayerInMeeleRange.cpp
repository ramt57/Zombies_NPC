// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_ISPlayerInMeeleRange.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_ISPlayerInMeeleRange::UBTService_ISPlayerInMeeleRange()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Is Player Melee In Range");
	NpcPawn = nullptr;
	TargetCharacter = nullptr;
}

void UBTService_ISPlayerInMeeleRange::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);
	const AAIController* Controller = Cast<AAIController>(OwnerComp.GetAIOwner());
	NpcPawn = Cast<APawn>(Controller->GetPawn());
	TargetCharacter = Cast<AActor>(
		OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor"));
}

void UBTService_ISPlayerInMeeleRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	if (TargetCharacter)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(),
		                                                   NpcPawn->GetDistanceTo(TargetCharacter) <= MeleeRange);
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(),
		                                                   false);
	}
}
