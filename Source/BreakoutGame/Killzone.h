// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Killzone.generated.h"

UCLASS()
class BREAKOUTGAME_API AKillzone : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* Box;

protected:
	virtual void BeginPlay() override;

public:
	AKillzone();

	UFUNCTION()
	void OnMyActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

};
