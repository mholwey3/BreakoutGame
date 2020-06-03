// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BreakoutGameGameModeBase.generated.h"

class UBreakoutGameHUD;

/**
 * 
 */
UCLASS()
class BREAKOUTGAME_API ABreakoutGameGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

private:

	bool IsGameOver;

	bool IsLevelClear;

	UPROPERTY(EditAnywhere)
	int MaxLives;

	int Lives;

	int Points;

	int BlocksRemaining;

	UPROPERTY(EditAnywhere)
	float PointsLostAfterDeath;

	UPROPERTY(EditAnywhere)
	float EndGameDelay;

	FTimerHandle GameOverTimerHandle;

	FTimerHandle LevelClearTimerHandle;

	UBreakoutGameHUD* HUD;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> BreakoutGameHUDClass;

	UPROPERTY(EditAnywhere)
	USoundBase* Sound_GameOver;

	UPROPERTY(EditAnywhere)
	USoundBase* Sound_LevelClear;

	UPROPERTY(EditAnywhere)
	FName BlockTag;

protected:
	virtual void BeginPlay() override;

public:
	bool GetIsGameOver();
	bool GetIsLevelClear();
	int GetLives();
	int GetPoints();

	void Reset();
	void UpdateScore(int PointsToAdd);
	void OnLifeLost();
	void CheckBlocksRemaining();
	void OnGameOver();
	void OnLevelClear();
	void LoadLevel();
	
};
