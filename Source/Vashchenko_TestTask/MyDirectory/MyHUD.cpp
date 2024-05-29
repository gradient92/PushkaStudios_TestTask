// Fill out your copyright notice in the Description page of Project Settings.


#include "Vashchenko_TestTask/MyDirectory/MyHUD.h"

#include "Blueprint/UserWidget.h"

AMyHUD::AMyHUD(): AchievementWidget(nullptr), TipsWidget(nullptr)
{
	static const ConstructorHelpers::FClassFinder<UUserWidget> UserWidget_path(TEXT(
		"/Script/UMGEditor.WidgetBlueprint'/Game/MyBlueprints/AchievementViewing_WidgetBP.AchievementViewing_WidgetBP_C'"));
	static const ConstructorHelpers::FClassFinder<UUserWidget> TipsWidget_path(
		TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/MyBlueprints/Tips_WBP.Tips_WBP_C'"));

	AchievementWidgetClass = UserWidget_path.Class;
	TipsWidgetClass = TipsWidget_path.Class;
}

void AMyHUD::BeginPlay()
{
	Super::BeginPlay();
	
	if(AchievementWidgetClass && TipsWidgetClass)
	{
		AchievementWidget = CreateWidget<UUserWidget>(GetWorld(), AchievementWidgetClass);
		AchievementWidget->AddToViewport();

		TipsWidget = CreateWidget<UUserWidget>(GetWorld(), TipsWidgetClass);
		TipsWidget->AddToViewport();
		
		Hide_AchievementWidget();
	}
}

void AMyHUD::Display_AchievementWidget() const
{
	if(AchievementWidget && TipsWidget)
	{
		AchievementWidget->SetVisibility(ESlateVisibility::Visible);
		TipsWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void AMyHUD::Hide_AchievementWidget() const
{
	if(AchievementWidget && TipsWidget)
	{
		AchievementWidget->SetVisibility(ESlateVisibility::Collapsed);
		TipsWidget->SetVisibility(ESlateVisibility::Visible);
	}
}


