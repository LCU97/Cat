// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "InputManagerComponent.generated.h"

class UBaseStateManagerComponent;
class UBaseAbilityManagerComponent;
class UInputHandler;
class UInputAction;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class HUMANANDCAT_API UInputManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInputManagerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

public:
	UFUNCTION(BlueprintCallable)
	void BufferCreateOpen();

	UFUNCTION(BlueprintCallable)
	void BufferCreateClose();

	UFUNCTION(BlueprintCallable)
	bool IsBufferOpen();

	UFUNCTION(BlueprintCallable)
	void CreateBufferingObject(UInputAction* Input, FGameplayTag Tag);

	UFUNCTION(BlueprintCallable)
	void SetInputHandler(UInputHandler* NewHandler);

	UFUNCTION(BlueprintCallable)
	UInputHandler* GetInputHandler() {return InputHandler;} ;
	
	UFUNCTION(BlueprintCallable)
	APawn* GetPlayerPawn();
	
public:
	bool bIsBufferOpesn;

	UPROPERTY()
	UInputHandler* InputHandler;

	UPROPERTY()
	AActor* OwnerActor;

	UPROPERTY()
	AController* OwnerController;

	UPROPERTY()
	UBaseStateManagerComponent* StateManagerComponent;

	UPROPERTY()
	UBaseAbilityManagerComponent* AbilityManagerComponent;

	
};
