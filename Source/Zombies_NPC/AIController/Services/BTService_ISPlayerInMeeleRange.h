// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_ISPlayerInMeeleRange.generated.h"

class UBlackboardKeyType_Object;
/**
 * 
 */
UCLASS()
class ZOMBIES_NPC_API UBTService_ISPlayerInMeeleRange : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	UBTService_ISPlayerInMeeleRange();
public:
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI", meta=(AllowPrivateAccess="true"))
	float MeleeRange = 150.f;
	UPROPERTY()
	const APawn* NpcPawn;
	UPROPERTY()
	const AActor* TargetCharacter;
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
