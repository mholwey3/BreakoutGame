// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#include "BreakoutGameGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "BreakoutGame/PlayerPaddle.h"
#include "BreakoutGame/BreakoutGameHUD.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"


void ABreakoutGameGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	HUD = CreateWidget<UBreakoutGameHUD>(GetWorld(), BreakoutGameHUDClass);
	HUD->AddToViewport();

	Reset();
}

bool ABreakoutGameGameModeBase::GetIsGameOver()
{
	return IsGameOver;
}

bool ABreakoutGameGameModeBase::GetIsLevelClear()
{
	return IsLevelClear;
}

int ABreakoutGameGameModeBase::GetLives()
{
	return Lives;
}

int ABreakoutGameGameModeBase::GetPoints()
{
	return Points;
}

void ABreakoutGameGameModeBase::Reset()
{
	Lives = MaxLives;
	Points = 0;
	IsGameOver = false;
}

void ABreakoutGameGameModeBase::UpdateScore(int DeltaPoints)
{
	Points += DeltaPoints;

	if (Points <= 0)
	{
		Points = 0;
	}
}

void ABreakoutGameGameModeBase::OnLifeLost()
{
	UpdateScore(-PointsLostAfterDeath);

	if (Lives <= 0)
	{
		OnGameOver();
	}
	else
	{
		Lives -= 1;
	}
}

void ABreakoutGameGameModeBase::CheckBlocksRemaining()
{
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), BlockTag, Actors);

	BlocksRemaining = Actors.Num();

	if (BlocksRemaining <= 0)
	{
		OnLevelClear();
	}
}

void ABreakoutGameGameModeBase::OnGameOver()
{
	IsGameOver = true;
	UGameplayStatics::PlaySound2D(this, Sound_GameOver);

	GetWorld()->GetTimerManager().SetTimer(GameOverTimerHandle, this, &ABreakoutGameGameModeBase::LoadLevel, EndGameDelay, false);
}

void ABreakoutGameGameModeBase::OnLevelClear()
{
	IsLevelClear = true;
	UGameplayStatics::PlaySound2D(this, Sound_LevelClear);

	GetWorld()->GetTimerManager().SetTimer(LevelClearTimerHandle, this, &ABreakoutGameGameModeBase::LoadLevel, EndGameDelay, false);
}

void ABreakoutGameGameModeBase::LoadLevel()
{
	UGameplayStatics::OpenLevel(GetWorld(), "Level1");
}
