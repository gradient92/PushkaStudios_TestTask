// Fill out your copyright notice in the Description page of Project Settings.


#include "Vashchenko_TestTask/MyDirectory/AchievementTriggerBox.h"

#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Vashchenko_TestTask/Vashchenko_TestTaskCharacter.h"

void AAchievementTriggerBox::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if(Cast<AVashchenko_TestTaskCharacter>(OtherActor) )
	{
		if(UMyGameInstance* GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
		{
			GameInstance->Complete_Achievement(EAchievementEnum::Achievement_OverlapTrigger);
		}
	}
}
