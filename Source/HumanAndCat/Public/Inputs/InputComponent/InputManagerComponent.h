// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "InputManagerComponent.generated.h"

// 1. InputBufferObject 를 생성합니다.
// 2. InputBuffer 생성 가능/불가능을 관리합니다.
// 3. 최종 Command 의 Excute 의 시발점이 되는 함수를 가지고 있습니다.
// 4. 헤더에서는 중요 멤버에 주석, cpp 에서는 주요 함수에 주석을 달았습니다.

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
	
private:
	// 입력 버퍼 생성을 위한 bool 값입니다.
	bool bIsBufferOpesn;

	// NotifyState 에서 복제된 핸들러입니다.
	UPROPERTY()
	UInputHandler* InputHandler;

	// Onwer 입니다.
	UPROPERTY()
	AActor* OwnerActor;

	// Owner 의 컨트롤러입니다.
	UPROPERTY()
	AController* OwnerController;
	
	UPROPERTY()
	UBaseStateManagerComponent* StateManagerComponent;

	UPROPERTY()
	UBaseAbilityManagerComponent* AbilityManagerComponent;

	
};
