// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAchievementsUpdated);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnResetAchievements);

class UMySaveAchievements;

// ACHIEVEMENTS ENUM
UENUM()
enum class EAchievementEnum : uint8
{
	Achievement_Jump UMETA(DisplayName = "Jump"),
	Achievement_HitTheBox UMETA(DisplayName = "Hit the box by weapon"),
	Achievement_OverlapTrigger UMETA(DisplayName = "Overlap the Trigger"),
	Achievement_Run50m UMETA(DisplayName = "Run 50 metres"),
	Achievement_TakeWeapon UMETA(DisplayName = "Take Weapon")
};

UCLASS()
class VASHCHENKO_TESTTASK_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UMyGameInstance();

	//USaveGame
	UPROPERTY()
	UMySaveAchievements* SaveGameInstance;
	
	UFUNCTION()
	void Complete_Achievement(EAchievementEnum AchievementName);
	
	UFUNCTION()
	bool bisAchievement_Completed(EAchievementEnum AchievementName);

	UFUNCTION()
	void Reset_Achievements();

	UPROPERTY(BlueprintAssignable)
	FOnAchievementsUpdated OnAchievementUpdated;

	UPROPERTY(BlueprintAssignable)
	FOnResetAchievements OnResetAchievements;
	
private:
	
	UPROPERTY()
	FString Achievement_SaveSlotName = "AchievementSave";
};
