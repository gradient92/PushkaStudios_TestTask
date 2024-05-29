// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AchievementViewing_Widget.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

/**
 * 
 */
UCLASS()
class VASHCHENKO_TESTTASK_API AMyHUD : public AHUD
{
	GENERATED_BODY()
public:
	
	AMyHUD();

	UFUNCTION()
	void Display_AchievementWidget() const;

	UFUNCTION()
	void Hide_AchievementWidget() const;

private:

	virtual void BeginPlay() override;
	
	TSubclassOf<UUserWidget> AchievementWidgetClass;
	
	TSubclassOf<UUserWidget> TipsWidgetClass;

	UPROPERTY()
	UUserWidget* AchievementWidget;

	UPROPERTY()
	UUserWidget* TipsWidget;
	
	
};
