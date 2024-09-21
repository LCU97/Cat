// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CatAIController.generated.h"

/**
 * 
 */
UCLASS()
class HUMANANDCAT_API ACatAIController : public AAIController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	void FollowPlayer();

private:

	ACatAIController();

	APawn* PlayerPawn;
	FTimerHandle TimerHandle;
	float AcceptanceRadius = 150.0f;

};