// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Inputs/InputProperties.h"
#include "GameplayTagContainer.h"
#include "Inputs/Interface_InputCommand.h"
#include "InputHandler.generated.h"

// 1. InpuComponent 가 생성한 InputBuffer 를 추가합니다.
// 2. 최종 사용할 InputBuffer 를 선택합니다.
// 3. 들어올 수 있는 입력 및 처리 타입, 사용할 Command 를 미리 설정합니다.
// 4. 최종 사용 할 Command 들을 선택합니다.
// 5. 헤더에는 중요 멤버 주석, cpp 에는 주요 함수에 주석을 달았습니다.

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
	// InputBuffer 처리 타입.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EInputPropertyType InputBufferType = EInputPropertyType::Last;

	// 핸들러에 들어올 수 있는 입력을 설정
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<UInputAction*, int32> AllowedInputActions;

	// 핸들러에 저장되는 InputBuffer
	UPROPERTY(BlueprintReadWrite)
	TArray<UInputBufferingObject*> InputBufferingObjects;

	// 최종 선택된 Buffer
	UPROPERTY()
	TObjectPtr<UInputBufferingObject> SelectBufferingObject;

	// 마지막에 Excute 되어질 Command 배열
	TArray<TScriptInterface<IInterface_InputCommand>> InputCommands;

	// 해당 핸들러 인스턴스에서 사용 할 수 있는 Command 를 설정하는 멤버
	UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite)
	TMap<FGameplayTag, UBaseCommand*> StateCommandMap;
};
