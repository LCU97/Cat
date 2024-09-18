// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inputs/Interface_InputCommand.h"
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

	virtual void ActionExecute_Implementation(const FInputPayLoad& InputPayLoad) override;
};
