// Fill out your copyright notice in the Description page of Project Settings.


#include "Block.h"
#include "BreakoutGame/Ball.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Engine/StaticMeshActor.h"
#include <typeinfo>

// Sets default values
ABlock::ABlock()
{
	PrimaryActorTick.bCanEverTick = true;

	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Block"));
	RootComponent = BlockMesh;
}

// Called when the game starts or when spawned
void ABlock::BeginPlay()
{
	Super::BeginPlay();

	GameMode = Cast<ABreakoutGameGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	FScriptDelegate Delegate;
	Delegate.BindUFunction(this, FName("OnMyActorHit"));
	OnActorHit.Add(Delegate);
}

void ABlock::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (BlockMesh != NULL)
	{
		UMaterialInstanceDynamic* MaterialInstance;
		
		MaterialInstance = BlockMesh->CreateDynamicMaterialInstance(0, Material_Basic);
		MaterialInstance->SetVectorParameterValue(FName(TEXT("Color")), Color);

		MaterialInstance = BlockMesh->CreateDynamicMaterialInstance(1, Material_Basic);
		MaterialInstance->SetVectorParameterValue(FName(TEXT("Color")), Color);
	}
}

void ABlock::OnMyActorHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	ABall* Ball = Cast<ABall>(OtherActor);

	if (Ball != nullptr)
	{
		Destroy();
		GameMode->UpdateScore(FMath::TruncToFloat(Points));
		Ball->IncrementSpeed(Points);
		UGameplayStatics::PlaySound2D(GetWorld(), Sound_Collectable);
	}
}

