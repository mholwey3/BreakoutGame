// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BreakoutGameHUD.generated.h"

class ABreakoutGameGameModeBase;

/**
 * 
 */
UCLASS()
class BREAKOUTGAME_API UBreakoutGameHUD : public UUserWidget
{
	GENERATED_BODY()

private:

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* PointsValue = nullptr;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* LivesValue = nullptr;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* GameOverText = nullptr;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* LevelClearText = nullptr;

	ABreakoutGameGameModeBase* GameMode;

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	virtual void NativeConstruct() override;

	void SetPointsText();
	void SetLivesText();
	void SetGameOverTextVisibility();
	void SetLevelClearTextVisibility();
};
