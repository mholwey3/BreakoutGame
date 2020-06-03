// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockWall.h"
#include "DestructibleComponent.h"
#include "Kismet/GameplayStatics.h"

ABlockWall::ABlockWall()
{
	
}

void ABlockWall::BeginPlay()
{
	Super::BeginPlay();

	FScriptDelegate Delegate = FScriptDelegate();
	Delegate.BindUFunction(this, FName("OnMyActorFracture"));
	OnActorFracture.Add(Delegate);
}

void ABlockWall::OnMyActorFracture(const FVector& HitPoint, const FVector& HitDirection)
{
	GetDestructibleComponent()->SetEnableGravity(true);
	GetDestructibleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_PhysicsBody, ECollisionResponse::ECR_Ignore);
	GetDestructibleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Destructible, ECollisionResponse::ECR_Block);
	GetDestructibleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);

	FVector Origin = GetDestructibleComponent()->GetComponentTransform().GetLocation();
	Origin.Z += RadialImpulseOriginOffsetZ;
	float Radius = FMath::RandRange(RadialImpulseRadiusLow, RadialImpulseRadiusHigh);
	float Strength = FMath::RandRange(RadialImpulseStrengthLow, RadialImpulseStrengthHigh);
	GetDestructibleComponent()->AddRadialImpulse(Origin, Radius, Strength, ERadialImpulseFalloff::RIF_Constant);

	UGameplayStatics::PlaySound2D(GetWorld(), Sound_Crumble);
	GetWorld()->GetTimerManager().SetTimer(FractureTimerHandle, this, &ABlockWall::DestroyActor, FractureTimerDelay, false);
}

void ABlockWall::DestroyActor()
{
	Destroy();
}