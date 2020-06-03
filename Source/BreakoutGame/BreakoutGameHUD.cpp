// Fill out your copyright notice in the Description page of Project Settings.


#include "BreakoutGameHUD.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetTextLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "BreakoutGame/BreakoutGameGameModeBase.h"

void UBreakoutGameHUD::NativeConstruct()
{
	Super::NativeConstruct();

	GameMode = Cast<ABreakoutGameGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
}

void UBreakoutGameHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	SetPointsText();
	SetLivesText();
	SetGameOverTextVisibility();
	SetLevelClearTextVisibility();
}

void UBreakoutGameHUD::SetPointsText()
{
	if (PointsValue)
	{
		PointsValue->SetText(UKismetTextLibrary::Conv_IntToText(GameMode->GetPoints()));
	}
}

void UBreakoutGameHUD::SetLivesText()
{
	if (LivesValue)
	{
		LivesValue->SetText(UKismetTextLibrary::Conv_IntToText(GameMode->GetLives()));
	}
}

void UBreakoutGameHUD::SetGameOverTextVisibility()
{
	if (GameOverText)
	{
		GameOverText->SetVisibility(GameMode->GetIsGameOver() ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	}
}

void UBreakoutGameHUD::SetLevelClearTextVisibility()
{
	if (LevelClearText)
	{
		LevelClearText->SetVisibility(GameMode->GetIsLevelClear() ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	}
}
