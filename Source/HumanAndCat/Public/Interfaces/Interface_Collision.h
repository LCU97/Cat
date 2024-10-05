// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interface_Collision.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UInterface_Collision : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class HUMANANDCAT_API IInterface_Collision
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void WhenItHit() = 0;
};
