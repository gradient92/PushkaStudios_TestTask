// Copyright Epic Games, Inc. All Rights Reserved.

#include "Vashchenko_TestTaskGameMode.h"
#include "Vashchenko_TestTaskCharacter.h"
#include "UObject/ConstructorHelpers.h"

AVashchenko_TestTaskGameMode::AVashchenko_TestTaskGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
