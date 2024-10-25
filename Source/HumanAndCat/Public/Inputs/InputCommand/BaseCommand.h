// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inputs/Interface_InputCommand.h"
#include "Inputs/InputBuffer/InputBufferingObject.h"
#include "UObject/Object.h"
#include "BaseCommand.generated.h"

/**
 * 
 */
UCLASS(Abstract, BlueprintType, EditInlineNew)
class HUMANANDCAT_API UBaseCommand : public UObject, public IInterface_InputCommand
{
	GENERATED_BODY()

public:
	UBaseCommand();

	// 커맨드 패턴을 활용하기 위한 Excute 함수 입니다.
	virtual void ActionExecute_Implementation(UInputBufferingObject* BufferingObject) override;
};
