// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPaddle.h"
#include "BreakoutGame/Ball.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include <typeinfo>

// Sets default values
APlayerPaddle::APlayerPaddle()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	PaddleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Paddle"));
	PaddleMesh->AttachTo(Root);

	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	ArrowComponent->AttachTo(PaddleMesh);
}

// Called when the game starts or when spawned
void APlayerPaddle::BeginPlay()
{
	Super::BeginPlay();

	GameMode = Cast<ABreakoutGameGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	FScriptDelegate Delegate = FScriptDelegate();
	Delegate.BindUFunction(this, FName("OnMyActorHit"));
	OnActorHit.Add(Delegate);

	SpawnBall();
}

// Called to bind functionality to input
void APlayerPaddle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APlayerPaddle::FireBall);
	PlayerInputComponent->BindAxis("HorizontalMovement", this, &APlayerPaddle::MovePaddle);
}

void APlayerPaddle::OnMyActorHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	if (typeid(OtherActor) == typeid(ABall))
	{
		UGameplayStatics::PlaySound2D(GetWorld(), Sound_Hit);
	}
}

UArrowComponent* APlayerPaddle::GetArrowComponent()
{
	return ArrowComponent;
}

void APlayerPaddle::SpawnBall()
{
	if (!GameMode->GetIsGameOver() && BallBP != NULL)
	{
		FVector Vector = GetArrowComponent()->GetComponentTransform().GetLocation();
		Ball = (ABall*)(GetWorld()->SpawnActor(BallBP, &Vector));
	}
}

void APlayerPaddle::FireBall()
{
	if (UKismetSystemLibrary::IsValid(Ball) && !Ball->GetIsActive())
	{
		Ball->LaunchBall();
	}
}

void APlayerPaddle::MovePaddle(float AxisValue)
{
	float DirectionalSpeed = Speed * AxisValue;
	FVector Impulse = FVector(DirectionalSpeed, 0.0f, 0.0f);

	PaddleMesh->AddImpulse(Impulse);
}
