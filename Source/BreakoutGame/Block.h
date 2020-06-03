// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BreakoutGame/BreakoutGameGameModeBase.h"
#include "GameFramework/Actor.h"
#include "Block.generated.h"

UCLASS()
class BREAKOUTGAME_API ABlock : public AActor
{
	GENERATED_BODY()

private:

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BlockMesh;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* Material_Basic;

	UPROPERTY(EditAnywhere)
	FLinearColor Color;

	UPROPERTY(EditAnywhere)
	float Points;

	UPROPERTY(EditAnywhere)
	USoundBase* Sound_Collectable;

	ABreakoutGameGameModeBase* GameMode;

protected:
	virtual void BeginPlay() override;

public:
	ABlock();

	virtual void OnConstruction(const FTransform& Transform) override;

	UFUNCTION()
	void OnMyActorHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);
};
