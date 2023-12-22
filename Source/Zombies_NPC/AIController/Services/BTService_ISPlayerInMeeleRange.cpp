// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_ISPlayerInMeeleRange.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_ISPlayerInMeeleRange::UBTService_ISPlayerInMeeleRange()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Is Player Melee In Range");
}

void UBTService_ISPlayerInMeeleRange::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const AAIController* Controller = Cast<AAIController>(OwnerComp.GetAIOwner());
	const APawn* NpcPawn = Cast<APawn>(Controller->GetPawn());
	const AActor* TargetCharacter = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor"));
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(),
	                                                   NpcPawn->GetDistanceTo(TargetCharacter) <= MeleeRange);
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);
}
