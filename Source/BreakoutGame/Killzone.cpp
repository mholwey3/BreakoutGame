// Fill out your copyright notice in the Description page of Project Settings.


#include "Killzone.h"
#include "BreakoutGame/Ball.h"

AKillzone::AKillzone()
{
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;
}

void AKillzone::BeginPlay()
{
	FScriptDelegate Delegate = FScriptDelegate();
	Delegate.BindUFunction(this, FName("OnMyActorBeginOverlap"));
	OnActorBeginOverlap.Add(Delegate);
}

void AKillzone::OnMyActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	ABall* Ball = Cast<ABall>(OtherActor);

	if (Ball != nullptr)
	{
		Ball->OnLifeLost();
	}
}

