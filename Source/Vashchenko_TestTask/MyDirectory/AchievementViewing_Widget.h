// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyGameInstance.h"
#include "Blueprint/UserWidget.h"
#include "AchievementViewing_Widget.generated.h"

/**
 * 
 */

UCLASS()
class VASHCHENKO_TESTTASK_API UAchievementViewing_Widget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual bool Initialize() override;
	
	TArray<EAchievementEnum>* GetReachedAchievements() const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsAchievementReached(EAchievementEnum Achievement);
	
private:

	UPROPERTY()
	UMyGameInstance* GameInstance;
};
