// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MySaveAchievements.generated.h"

/**
 * 
 */

enum class EAchievementEnum : uint8;

UCLASS()
class VASHCHENKO_TESTTASK_API UMySaveAchievements : public USaveGame
{
	GENERATED_BODY()

public:

	//Achievements array to save
	UPROPERTY()
	TArray<EAchievementEnum> ReachedAchievements;
};
