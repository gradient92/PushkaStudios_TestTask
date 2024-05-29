// Fill out your copyright notice in the Description page of Project Settings.


#include "Vashchenko_TestTask/MyDirectory/AchievementViewing_Widget.h"

#include "MySaveAchievements.h"

bool UAchievementViewing_Widget::Initialize()
{
	GameInstance = StaticCast<UMyGameInstance*>(GetGameInstance());
	return Super::Initialize();
}

TArray<EAchievementEnum>* UAchievementViewing_Widget::GetReachedAchievements() const
{
	return &GameInstance->SaveGameInstance->ReachedAchievements;
}

bool UAchievementViewing_Widget::IsAchievementReached(EAchievementEnum Achievement)
{
	return GameInstance->bisAchievement_Completed(Achievement);
}


