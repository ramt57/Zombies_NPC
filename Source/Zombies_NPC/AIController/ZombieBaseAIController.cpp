// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieBaseAIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Damage.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Zombies_NPC/NPCCharacter/ZombieBase.h"

void AZombieBaseAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AZombieBaseAIController::SetupPerceptionSystem()
{
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	HearConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("HearConfig"));
	DamageConfig = CreateDefaultSubobject<UAISenseConfig_Damage>(TEXT("DamageConfig"));
	if (SightConfig && HearConfig && DamageConfig)
	{
		/* Sight */
		SightConfig->SightRadius = 500.f;
		SightConfig->LoseSightRadius = SightConfig->SightRadius + 500.f;
		SightConfig->PeripheralVisionAngleDegrees = 90.f;
		SightConfig->SetMaxAge(5.f);
		SightConfig->AutoSuccessRangeFromLastSeenLocation = 520.f;
		SightConfig->DetectionByAffiliation.bDetectEnemies = true;
		SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
		SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

		/* Hearing */
		HearConfig->DetectionByAffiliation.bDetectEnemies = true;
		HearConfig->DetectionByAffiliation.bDetectFriendlies = true;
		HearConfig->DetectionByAffiliation.bDetectNeutrals = true;
		HearConfig->SetMaxAge(10.f);

		/* Damage */
		DamageConfig->SetMaxAge(20.f);

		SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));

		GetPerceptionComponent()->SetDominantSense(*HearConfig->GetSenseImplementation());
		GetPerceptionComponent()->ConfigureSense(*SightConfig);
		GetPerceptionComponent()->ConfigureSense(*HearConfig);
		GetPerceptionComponent()->ConfigureSense(*DamageConfig);

		GetPerceptionComponent()->OnTargetPerceptionUpdated.
		                          AddDynamic(this, &AZombieBaseAIController::OnTargetDetected);
	}
}

void AZombieBaseAIController::OnTargetDetected(AActor* Actor, FAIStimulus Stimulus)
{
	if (Stimulus.IsValid())
	{
		if (Stimulus.Type.Name == SightConfig->GetSenseID().Name)
		{
			// The stimulus is related to sight
			GetBlackboardComponent()->SetValueAsBool("CanSensePlayer", Stimulus.IsActive());
			GetBlackboardComponent()->SetValueAsObject("TargetActor", Stimulus.IsActive() ? Actor : nullptr);
			// The stimulus is related to last player known location
			GetBlackboardComponent()->SetValueAsVector("TargetLocation", Actor->GetActorLocation());
		}
		else if (Stimulus.Type.Name == HearConfig->GetSenseID().Name)
		{
			// The stimulus is related to hearing
			GetBlackboardComponent()->SetValueAsVector("TargetLocation", Stimulus.StimulusLocation);
		}
		else if (Stimulus.Type.Name == DamageConfig->GetSenseID().Name)
		{
		}
	}
}

AZombieBaseAIController::AZombieBaseAIController(FObjectInitializer const& ObjectInitializer)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetupPerceptionSystem();
}

// Called when the game starts or when spawned
void AZombieBaseAIController::BeginPlay()
{
	Super::BeginPlay();
	if (Tree != nullptr)
	{
		UBlackboardComponent* b;
		UseBlackboard(Tree->GetBlackboardAsset(), b);
		Blackboard = b;
	}
}

// Called every frame

void AZombieBaseAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (AZombieBase* ZombieCharacter = Cast<AZombieBase>(InPawn))
	{
		if (Tree != nullptr)
		{
			RunBehaviorTree(Tree);
		}
	}
}
