// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"
#include "BreakoutGame/PlayerPaddle.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Engine/StaticMeshActor.h"

// Sets default values
ABall::ABall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ball"));
	RootComponent = BallMesh;

	SeeThroughMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SeeThroughBall"));
	SeeThroughMesh->AttachTo(BallMesh);
}

bool ABall::GetIsActive()
{
	return IsActive;
}

void ABall::BeginPlay()
{
	Super::BeginPlay();
	
	GameMode = Cast<ABreakoutGameGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	FScriptDelegate Delegate = FScriptDelegate();
	Delegate.BindUFunction(this, FName("OnMyActorHit"));
	OnActorHit.Add(Delegate);
}

void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsActive)
	{
		UpdateBallPositionToFollowPaddle();
	}
	else
	{
		ClampVelocityAndAngle();
	}
}

void ABall::OnMyActorHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	if (Cast<AStaticMeshActor>(OtherActor) != nullptr || Cast<APlayerPaddle>(OtherActor) != nullptr)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), Sound_Hit);
	}

	GameMode->CheckBlocksRemaining();

	if (GameMode->GetIsLevelClear())
	{
		Speed = 0.0f;
	}
}

void ABall::LaunchBall()
{
	if (BallMesh != NULL)
	{
		IsActive = true;

		FVector ImpulseVector = FVector(Speed, -Speed, 0.0f);
		BallMesh->AddImpulse(ImpulseVector, NAME_None, true);
	}
}

void ABall::UpdateBallPositionToFollowPaddle()
{
	APlayerPaddle* PlayerPaddle = Cast<APlayerPaddle>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (BallMesh != nullptr && PlayerPaddle != nullptr)
	{
		FVector Location = PlayerPaddle->GetArrowComponent()->GetComponentTransform().GetLocation();
		BallMesh->SetWorldLocation(Location);
	}
}

void ABall::ClampVelocityAndAngle()
{
	if (BallMesh != nullptr)
	{
		FVector Velocity = BallMesh->GetPhysicsLinearVelocity().GetClampedToSize(Speed, Speed);

		FRotator Rotator = FRotator(0.0f, 45.0, 0.0f);

		FVector RotatedVector = Rotator.RotateVector(Velocity);

		float Yaw = FRotationMatrix::MakeFromX(RotatedVector).Rotator().Yaw;

		float NewYaw = (float)(FMath::RoundToInt(Yaw / 90.0f) * 90.0f);

		FRotator NewRotator = FRotator(0.0f, NewYaw, 0.0f);

		FVector NewVector = NewRotator.Vector();

		FVector UnrotatedVector = Rotator.UnrotateVector(NewVector);

		float OrigVectorLength = Velocity.Size();

		FVector NewVelocity = UnrotatedVector * OrigVectorLength;

		BallMesh->SetPhysicsLinearVelocity(NewVelocity);
	}
}

void ABall::IncrementSpeed(float IncrementAmount)
{
	Speed += IncrementAmount;
}

void ABall::OnLifeLost()
{
	IsActive = false;

	if (GameMode != NULL)
	{
		if (GameMode->GetLives() <= 0)
		{
			Destroy();
		}

		GameMode->OnLifeLost();
	}
}