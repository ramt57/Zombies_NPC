// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindTargetLocation.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FindTargetLocation::UBTTask_FindTargetLocation(FObjectInitializer const& ObjectInitializer)
{
	NodeName="Find Random Location";
}

EBTNodeResult::Type UBTTask_FindTargetLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if(const AAIController* AIController = Cast<AAIController>(OwnerComp.GetAIOwner()))
	{
		if(const APawn* Pawn = AIController->GetPawn())
		{
			if(const UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld()))
			{
				FNavLocation Location;
				SearchRadius = 1500.f;
				NavSys->GetRandomPointInNavigableRadius(Pawn->GetActorLocation(), SearchRadius, Location);
				OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), Location.Location);
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}
