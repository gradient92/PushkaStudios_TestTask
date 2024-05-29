// Copyright Epic Games, Inc. All Rights Reserved.

#include "Vashchenko_TestTaskCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "MyDirectory/MyGameInstance.h"
#include "MyDirectory/MyHUD.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AVashchenko_TestTaskCharacter

void AVashchenko_TestTaskCharacter::Jump()
{
	Super::Jump();

	if(GameInstance)
	{
		GameInstance->Complete_Achievement(EAchievementEnum::Achievement_Jump);
	}
}

AVashchenko_TestTaskCharacter::AVashchenko_TestTaskCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));
}

void AVashchenko_TestTaskCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	PlayerController = Cast<AVashchenko_TestTaskPlayerController>(Controller);
	PlayerHUD = Cast<AMyHUD>(PlayerController->GetHUD());

	CalculateTraveledDistance();

	if(GameInstance)
	{
		GameInstance->OnResetAchievements.AddUniqueDynamic(this, &AVashchenko_TestTaskCharacter::CalculateTraveledDistance);
	}
}

//////////////////////////////////////////////////////////////////////////// Input

void AVashchenko_TestTaskCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AVashchenko_TestTaskCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AVashchenko_TestTaskCharacter::Look);

		// Achievement Menu
		EnhancedInputComponent->BindAction(AchievementMenuAction, ETriggerEvent::Started, this, &AVashchenko_TestTaskCharacter::Display_AchievementMenu);
		EnhancedInputComponent->BindAction(AchievementMenuAction, ETriggerEvent::Completed, this, &AVashchenko_TestTaskCharacter::Hide_AchievementMenu);

		//Reset Achievement
		EnhancedInputComponent->BindAction(ResetAchievementsAction, ETriggerEvent::Completed, this, &AVashchenko_TestTaskCharacter::ResetAchievements);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AVashchenko_TestTaskCharacter::Display_AchievementMenu()
{
	if(PlayerHUD)
	{
		PlayerHUD->Display_AchievementWidget();
	}
}

void AVashchenko_TestTaskCharacter::Hide_AchievementMenu()
{
	if(PlayerHUD)
	{
		PlayerHUD->Hide_AchievementWidget();
	}
}

void AVashchenko_TestTaskCharacter::ResetAchievements()
{
	if(GameInstance)
	{
		GameInstance->Reset_Achievements();
	}
}

struct FTraveledDistanceData
{
	float TraveledDistance;
	FVector PreviousPoint;

	FTraveledDistanceData() : TraveledDistance(0.0f), PreviousPoint(FVector::ZeroVector) {}
};

void AVashchenko_TestTaskCharacter::CalculateTraveledDistance()
{
	//is Achievement Completed
	if(GameInstance->bisAchievement_Completed(EAchievementEnum::Achievement_Run50m))
	{
		return;
	}

	TSharedPtr<FTraveledDistanceData> Data = MakeShared<FTraveledDistanceData>();
	Data->PreviousPoint = GetActorLocation();

	//Timer that every 0.25s checking character location & calculate traveled distance
	GetWorld()->GetTimerManager().SetTimer(RunAchievementTimerHandle, [this, Data]()
	{
		FVector ActualPoint = GetActorLocation();
        	
		if (Data->PreviousPoint != ActualPoint)
		{
			Data->TraveledDistance += FVector::Dist(Data->PreviousPoint, ActualPoint);
			
			/*if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 0.25f, FColor::Green,
					FString::Printf(TEXT("Traveled Distance: %f"), Data->TraveledDistance));
			}*/
			
			Data->PreviousPoint = ActualPoint;
			if(Data->TraveledDistance/100 >= 50)
			{
				if(GameInstance)
				{
					GameInstance->Complete_Achievement(EAchievementEnum::Achievement_Run50m);
				}
            	
				GetWorld()->GetTimerManager().ClearTimer(RunAchievementTimerHandle);
            
				/*if (GEngine)
				{
					GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue,
					FString::Printf(TEXT("Run Achievement Completed")));
				}*/
            			
				Data->TraveledDistance = 0;
			}
		}
		
	}, 0.25, true);
}


void AVashchenko_TestTaskCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AVashchenko_TestTaskCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}