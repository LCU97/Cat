// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Inputs/InputProperties.h"
#include "GameplayTagContainer.h"
#include "Inputs/Interface_InputCommand.h"
#include "InputHandler.generated.h"

class UBaseAbilityManagerComponent;
class UBaseStateManagerComponent;
class UBaseCommand;
class UInputAction;
class UInputBufferingObject;
/**
 * 
 */
UCLASS(BlueprintType, Blueprintable,EditInlineNew)
class HUMANANDCAT_API UInputHandler : public UObject
{
	GENERATED_BODY()
public:
	UInputHandler();
public:
	// 입력 버퍼를 추가.
	UFUNCTION(BlueprintCallable)
	bool AddBufferingObject(UInputBufferingObject* NewBufferingObject);

	// 입력 버퍼 모아둔거 클리어
	UFUNCTION(BlueprintCallable)
	void ClearBuffering();

	// 사용할 버퍼객체를 선택

	UFUNCTION(BlueprintCallable)
	UInputBufferingObject* SelectInputBufferingObject();

	UFUNCTION()
	UInputBufferingObject* SelectBufferingObjectByPriority();
	
	// 사용할 커맨드를 바인딩
	UFUNCTION(BlueprintCallable)
	void BindCommand(UObject* CommandObject);

	// 사용할 커맨드 셋업
	UFUNCTION(BlueprintCallable)
	void SetupCommand(FInputPayLoad& InputPayLoad);
	void SetupCommand(UInputBufferingObject* BufferObject);
	
	// 실제 바인딩되어진 커맨드를 실행
	UFUNCTION(BlueprintCallable)
	void ExecuteCommand();

public:
	// Get, Set
	UFUNCTION(BlueprintCallable)
	EInputPropertyType GetInputPropertyType() { return InputBufferType;}

	UBaseStateManagerComponent* GetStateManager(AController* Con);
	UBaseAbilityManagerComponent* GetAbilityManager(AActor* Actor);
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EInputPropertyType InputBufferType = EInputPropertyType::Last;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<UInputAction*, int32> AllowedInputActions;

	UPROPERTY(BlueprintReadWrite)
	TArray<UInputBufferingObject*> InputBufferingObjects;

	UPROPERTY()
	TObjectPtr<UInputBufferingObject> SelectBufferingObject;

	TArray<TScriptInterface<IInterface_InputCommand>> InputCommands;
	
	UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite)
	TMap<FGameplayTag, UBaseCommand*> StateCommandMap;
};
