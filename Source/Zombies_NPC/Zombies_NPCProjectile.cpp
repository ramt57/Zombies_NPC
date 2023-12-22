// Copyright Epic Games, Inc. All Rights Reserved.

#include "Zombies_NPCProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NPCCharacter/ZombieBase.h"
#include "Perception/AIPerceptionSystem.h"
#include "Perception/AISense_Damage.h"
#include "Perception/AISense_Hearing.h"

AZombies_NPCProjectile::AZombies_NPCProjectile()
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AZombies_NPCProjectile::OnHit);
	// set up a notification for when this component hits something blocking
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AZombies_NPCProjectile::OnSphereBeginOverlap);
	// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void AZombies_NPCProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                                   FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
		// Create a noise event
		UAISense_Hearing::ReportNoiseEvent(GetWorld(), Hit.Location, 2.f, OtherActor, 1000);
		// Try and play the sound if specified
		if (FireSound != nullptr)
		{
			UGameplayStatics::PlaySoundAtLocation(this, FireSound, Hit.Location);
		}
		if (BloodEmitterClass != nullptr)
		{
			// Spawn the emitter at the specified location.
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BloodEmitterClass, Hit.Location, FRotator::ZeroRotator, true);
		}
		Destroy();
	}
}

void AZombies_NPCProjectile::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                                  const FHitResult& SweepResult)
{
	OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
	// Create a noise event
	UAISense_Hearing::ReportNoiseEvent(GetWorld(), SweepResult.Location, 2.f, OtherActor, 1000);
	// Try and play the sound if specified
	if (FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, SweepResult.Location);
	}
	if (const AZombieBase* Character = Cast<AZombieBase>(OtherActor); Character != nullptr)
	{
		// Create a noise event
	//	UAISense_Damage::ReportDamageEvent(GetWorld(), OtherActor, this, 25.f,  Owner->GetActorLocation(), SweepResult.ImpactPoint);
		if (BloodEmitterClass)
		{
			// Spawn the emitter at the specified location.
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BloodEmitterClass, SweepResult.Location, SweepResult.ImpactNormal.Rotation(), true);
		}
	}
}
