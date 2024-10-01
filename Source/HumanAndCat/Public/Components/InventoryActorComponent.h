// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAsset/ItemData.h"
#include "Components/ActorComponent.h"
#include "InventoryActorComponent.generated.h"

USTRUCT(BlueprintType)
struct FInventoryItem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory")
	FItemData ItemData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory")
	int32 Quantity;		// ItemData doesnt have any information abt quantity

	FInventoryItem()
		: ItemData(), Quantity(1)		// default quantity
	{}
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HUMANANDCAT_API UInventoryActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryActorComponent();

	// inventory map which use itemID as a key
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory")
	//TMap<int32, FInventoryItem> Inventory;
	TMap<FName, FInventoryItem> Inventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory")
	UDataTable* ItemDataTable;
	
	// load item from DataTable
	UFUNCTION(BlueprintCallable, Category="Inventory")
	FItemData LoadItemFromDataTable(FName ItemRowName);

	// add item
	UFUNCTION(BlueprintCallable, Category="Inventory")
	void AddItemToInventory(FName ItemRowName, int32 quantity);

	// remove item
	UFUNCTION(BlueprintCallable, Category="Inventory")
	void RemoveItemFromInventory(FName ItemRowName, int32 quantity);
	
	//  check whether it  is full or not
	UFUNCTION(BlueprintCallable, Category="Inventory")
	bool IsInventoryFull() const;
	
	// maxsize
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory")
	int32 MaxInventorySize;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
		
};
