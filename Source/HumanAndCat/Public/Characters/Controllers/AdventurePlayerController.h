// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePlayerController.h"
#include "AdventurePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class HUMANANDCAT_API AAdventurePlayerController : public ABasePlayerController
{
	GENERATED_BODY()
	public:
	AAdventurePlayerController(const FObjectInitializer& FObjectInitializer);
	
public:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

};
