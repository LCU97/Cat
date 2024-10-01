// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemData.h"
#include "Item.generated.h"

UCLASS()
class HUMANANDCAT_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FItemData ItemData;
	
	UFUNCTION(BlueprintCallable, Category = "Item")
	void OnPickUp(class AAdventurePlayer* Player);

	UFUNCTION(BlueprintCallable, Category = "Item")
	void OnDrop(class AAdventurePlayer* Player);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	UStaticMeshComponent* ItemMeshComponent;
};
