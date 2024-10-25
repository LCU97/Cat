#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Inputs/InputComponent/InputManagerComponent.h"
#include "InputProperties.generated.h"

//class UInputManagerComponent;
class UInputBufferingObject;

UENUM(BlueprintType)
enum class EInputPropertyType : uint8
{
	Immediately,
	Last,
	Priority
};
