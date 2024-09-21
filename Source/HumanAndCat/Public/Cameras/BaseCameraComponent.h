// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Camera/CameraComponent.h"
#include "BaseCameraComponent.generated.h"

/**
 * 
 */
UCLASS()
class HUMANANDCAT_API UBaseCameraComponent : public UCameraComponent
{
	GENERATED_BODY()
public:
	UBaseCameraComponent();


public:
	FGameplayTag CameraTag;
};
