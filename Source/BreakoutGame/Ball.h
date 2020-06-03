// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BreakoutGame/BreakoutGameGameModeBase.h"
#include "Ball.generated.h"

class APlayerPaddle;

UCLASS()
class BREAKOUTGAME_API ABall : public AActor
{
	GENERATED_BODY()

private:

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BallMesh;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* SeeThroughMesh;

	UPROPERTY(EditAnywhere)
	float Speed;

	UPROPERTY(EditAnywhere)
	float SpeedIncrement;

	UPROPERTY(EditAnywhere)
	USoundBase* Sound_Hit;

	ABreakoutGameGameModeBase* GameMode;

	bool IsActive;

protected:
	virtual void BeginPlay() override;

public:
	ABall();

	bool GetIsActive();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnMyActorHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

	void LaunchBall();
	void UpdateBallPositionToFollowPaddle();
	void ClampVelocityAndAngle();
	void IncrementSpeed(float IncrementAmount);
	void OnLifeLost();

};
