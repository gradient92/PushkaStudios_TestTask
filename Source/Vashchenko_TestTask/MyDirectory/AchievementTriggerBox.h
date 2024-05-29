// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "AchievementTriggerBox.generated.h"

/**
 * 
 */
UCLASS()
class VASHCHENKO_TESTTASK_API AAchievementTriggerBox : public ATriggerBox
{
	GENERATED_BODY()

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
