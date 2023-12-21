// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieBase.h"

#include "EZombieState.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISenseConfig_Sight.h"


void AZombieBase::SetUpStimuliSource()
{
	StimuliSourceComponent = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Stimulus"));
	if (StimuliSourceComponent)
	{
		StimuliSourceComponent->RegisterForSense(TSubclassOf<UAISense_Sight>());
		StimuliSourceComponent->RegisterWithPerceptionSystem();
	}
}

void AZombieBase::SetNpcState(const EZombieState State)
{
	NpcState = State;
	switch (State)
	{
	case EZombieState::ETIP_IDLE:
		GetCharacterMovement()->MaxWalkSpeed =35.f;
		break;;
	case EZombieState::ETIP_ROAM:
		GetCharacterMovement()->MaxWalkSpeed =35.f;
		break;
	case EZombieState::ETIP_SEARCH:
		GetCharacterMovement()->MaxWalkSpeed =35.f;
		break;
	case EZombieState::ETIP_CHASE:
		GetCharacterMovement()->MaxWalkSpeed =150.f;
		break;
	case EZombieState::ETIP_HYPER_CHASE:
		GetCharacterMovement()->MaxWalkSpeed =200.f;
		break;
	default:
		break;
	}
}

// Sets default values
AZombieBase::AZombieBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AZombieBase::BeginPlay()
{
	Super::BeginPlay();
	NpcState = EZombieState::ETIP_ROAM;
}

// Called every frame
void AZombieBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AZombieBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
