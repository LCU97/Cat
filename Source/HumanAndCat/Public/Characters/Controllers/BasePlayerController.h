// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"

class UBaseStateManagerComponent;
/**
 * 
 */
UCLASS()
class HUMANANDCAT_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()
public:	
	ABasePlayerController();
public:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;


public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Input")
	class UInputMappingContext* MappingContext = nullptr;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="StateComponent")
	UBaseStateManagerComponent* StateManager;

	
};
