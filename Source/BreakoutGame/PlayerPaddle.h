// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ArrowComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BreakoutGame/BreakoutGameGameModeBase.h"
#include "PlayerPaddle.generated.h"

class ABall;

UCLASS()
class BREAKOUTGAME_API APlayerPaddle : public APawn
{
	GENERATED_BODY()

private:
	UPROPERTY()
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* PaddleMesh;

	UPROPERTY(VisibleAnywhere)
	UArrowComponent* ArrowComponent;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABall> BallBP;

	UPROPERTY(EditAnywhere)
	USoundBase* Sound_Hit;

	UPROPERTY(EditAnywhere)
	float Speed;

	ABall* Ball;

	ABreakoutGameGameModeBase* GameMode;

protected:
	virtual void BeginPlay() override;

public:
	APlayerPaddle();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void OnMyActorHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

	UArrowComponent* GetArrowComponent();
	void SpawnBall();
	void FireBall();
	void MovePaddle(float AxisValue);

};
