// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DestructibleActor.h"
#include "BlockWall.generated.h"

/**
 * 
 */
UCLASS()
class BREAKOUTGAME_API ABlockWall : public ADestructibleActor
{
	GENERATED_BODY()
	
private:

	UPROPERTY(EditAnywhere)
	USoundBase* Sound_Crumble;

	UPROPERTY(EditAnywhere)
	float RadialImpulseOriginOffsetZ;

	UPROPERTY(EditAnywhere)
	float RadialImpulseRadiusLow;
	
	UPROPERTY(EditAnywhere)
	float RadialImpulseRadiusHigh;

	UPROPERTY(EditAnywhere)
	float RadialImpulseStrengthLow;

	UPROPERTY(EditAnywhere)
	float RadialImpulseStrengthHigh;

	UPROPERTY(EditAnywhere)
	float FractureTimerDelay;

	FTimerHandle FractureTimerHandle;

protected:
	virtual void BeginPlay() override;

public:
	ABlockWall();

	UFUNCTION()
	void OnMyActorFracture(const FVector& HitPoint, const FVector& HitDirection);

	void DestroyActor();

};
