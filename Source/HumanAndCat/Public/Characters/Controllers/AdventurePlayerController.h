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

	UFUNCTION(BlueprintCallable)
	void TogglePawnChange();
	
	UFUNCTION(BlueprintNativeEvent ,BlueprintCallable)
	void PossessCatPlayer();
	
	UFUNCTION(BlueprintNativeEvent ,BlueprintCallable)
	void PossessHumanPlayer();
	
public:
	UFUNCTION(BlueprintCallable)
	void SetFwdBak(float Value) { FwdBak = Value; };

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float FwdBak;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<APawn> CatPlayerClass;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<APawn> HumanPlayerClass;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	APawn* CatPlayerPawn;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	APawn* HumanPlayerPawn;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	APawn* AICat;
	
};
