// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Controllers/AdventurePlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Characters/AdventurePlayer.h"
#include "Characters/CatPlayer.h"
#include "Kismet/GameplayStatics.h"


AAdventurePlayerController::AAdventurePlayerController(const FObjectInitializer& FObjectInitializer):
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


	CatPlayerPawn = Cast<APawn>(UGameplayStatics::GetActorOfClass(GetWorld(), CatPlayerClass));
	HumanPlayerPawn = Cast<APawn>(UGameplayStatics::GetActorOfClass(GetWorld(), HumanPlayerClass));
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
		if(InPawn && InputsubSystem)
		{
			if(InPawn->IsA(AAdventurePlayer::StaticClass()))
			{
				if(MappingContext)
				{
					InputsubSystem->AddMappingContext(MappingContext, 0);			
				}
			}
			else if(InPawn->IsA(ACatPlayer::StaticClass()))
			{
				if(CatMappingContext)
				{
					InputsubSystem->AddMappingContext(CatMappingContext, 0);			
				}
			}
		}		
	}
}

void AAdventurePlayerController::OnUnPossess()
{
	if(UEnhancedInputLocalPlayerSubsystem* InputsubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if(GetPawn() && InputsubSystem)
		{
			if(GetPawn()->IsA(AAdventurePlayer::StaticClass()))
			{
				if(MappingContext)
				{
					InputsubSystem->RemoveMappingContext(MappingContext);			
				}
			}
			else if(GetPawn()->IsA(ACatPlayer::StaticClass()))
			{
				if(CatMappingContext)
				{
					InputsubSystem->RemoveMappingContext(CatMappingContext);			
				}
			}
		}		
	}
	Super::OnUnPossess();
}

void AAdventurePlayerController::TogglePawnChange()
{
	if(GetPawn()->IsA(ACatPlayer::StaticClass()))
	{
		PossessHumanPlayer();
	}
	else if(GetPawn()->IsA(AAdventurePlayer::StaticClass()))
	{
		PossessCatPlayer();
	}
}

void AAdventurePlayerController::PossessCatPlayer_Implementation()
{
	if(CatPlayerClass && HumanPlayerClass)
	{
		if(CatPlayerPawn)
		{
			UnPossess();
			ACatPlayer* CatPlayer = Cast<ACatPlayer>(CatPlayerPawn);
			if(CatPlayer) CatPlayer->bIsPossess = true;
			Possess(CatPlayerPawn);
		}
	}
}

void AAdventurePlayerController::PossessHumanPlayer_Implementation()
{
	if(CatPlayerClass && HumanPlayerClass)
	{
		if(HumanPlayerPawn)
		{
			UnPossess();
			ACatPlayer* CatPlayer = Cast<ACatPlayer>(CatPlayerPawn);
			if(CatPlayer) CatPlayer->bIsPossess = false;
			Possess(HumanPlayerPawn);
		}
	}
}
