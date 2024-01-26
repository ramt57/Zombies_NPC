// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MeeleAttack.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Zombies_NPC/NPCCharacter/ZombieBase.h"

UBTTask_MeeleAttack::UBTTask_MeeleAttack()
{
	NodeName = TEXT("Melee Attack");
}

EBTNodeResult::Type UBTTask_MeeleAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto const InRange = OwnerComp.GetBlackboardComponent()->GetValueAsBool(GetSelectedBlackboardKey());
	const AAIController* Controller = Cast<AAIController>(OwnerComp.GetAIOwner());
	AZombieBase* NpcPawn = Cast<AZombieBase>(Controller->GetPawn());
	if (!InRange)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		NpcPawn->GetMesh()->GetAnimInstance()->Montage_Stop(1, NpcPawn->GetCurrentMontage());
		return EBTNodeResult::Succeeded;
	}
	if (NpcPawn && NpcPawn->GetClass()->ImplementsInterface(UZombieActionInterface::StaticClass()))
	{
		if (MontageHasFinished(NpcPawn))
		{
			IZombieActionInterface::Execute_MeleeAttack(NpcPawn);
		}
	}
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Type();
}

bool UBTTask_MeeleAttack::MontageHasFinished(const ACharacter* Npc)
{
	return Npc->GetMesh()->GetAnimInstance()->Montage_GetIsStopped(Npc->GetCurrentMontage());
}
