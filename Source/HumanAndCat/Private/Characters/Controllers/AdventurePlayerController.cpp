// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Controllers/AdventurePlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"


AAdventurePlayerController::AAdventurePlayerController(const FObjectInitializer FObjectInitializer):
	Super()
{
	
}

void AAdventurePlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AAdventurePlayerController::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAdventurePlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAdventurePlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if(UEnhancedInputLocalPlayerSubsystem* InputsubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		InputsubSystem->AddMappingContext(MappingContext, 0);			
	}
}

void AAdventurePlayerController::OnUnPossess()
{
	Super::OnUnPossess();
	if(UEnhancedInputLocalPlayerSubsystem* InputsubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		InputsubSystem->RemoveMappingContext(MappingContext);		
	}
}
