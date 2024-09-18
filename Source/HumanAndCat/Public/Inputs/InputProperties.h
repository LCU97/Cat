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

USTRUCT(BlueprintType)
struct FInputPayLoad
{
	GENERATED_BODY()

public:
	FInputPayLoad() {}

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<AActor> OuterActor;
	
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<AController> OuterController;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UInputManagerComponent> InputManager;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UInputBufferingObject> Buffer;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UObject> StateObject;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UObject> AbilityObject;
};
/*struct InputProperties
{
	
};*/
