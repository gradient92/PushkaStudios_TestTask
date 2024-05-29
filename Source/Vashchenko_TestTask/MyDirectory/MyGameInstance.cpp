// Fill out your copyright notice in the Description page of Project Settings.


#include "Vashchenko_TestTask/MyDirectory/MyGameInstance.h"

#include "MySaveAchievements.h"
#include "Kismet/GameplayStatics.h"

UMyGameInstance::UMyGameInstance()
{
	SaveGameInstance = StaticCast<UMySaveAchievements*>(UGameplayStatics::LoadGameFromSlot(Achievement_SaveSlotName, 0));
	
	if (!SaveGameInstance)
	{
		SaveGameInstance = StaticCast<UMySaveAchievements*>(UGameplayStatics::CreateSaveGameObject(UMySaveAchievements::StaticClass()));
	}
}

void UMyGameInstance::Complete_Achievement(EAchievementEnum AchievementName)
{
	if (SaveGameInstance)
	{
		SaveGameInstance->ReachedAchievements.AddUnique(AchievementName);
		
		UGameplayStatics::AsyncSaveGameToSlot(SaveGameInstance, Achievement_SaveSlotName, 0);
		
		OnAchievementUpdated.Broadcast();
	}
}

bool UMyGameInstance::bisAchievement_Completed(EAchievementEnum AchievementName)
{
	if (SaveGameInstance && SaveGameInstance->ReachedAchievements.Contains(AchievementName))
	{
		return true;
	}
	return false;
}

void UMyGameInstance::Reset_Achievements()
{
	if (SaveGameInstance)
	{
		SaveGameInstance->ReachedAchievements.Empty();
		
		UGameplayStatics::AsyncSaveGameToSlot(SaveGameInstance, Achievement_SaveSlotName, 0);

		OnAchievementUpdated.Broadcast();
		OnResetAchievements.Broadcast();
	}
}