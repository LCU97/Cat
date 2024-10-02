// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InventoryActorComponent.h"

// Sets default values for this component's properties
UInventoryActorComponent::UInventoryActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


FItemData UInventoryActorComponent::LoadItemFromDataTable(FName ItemRowName)
{
	if (!ItemDataTable)
	{
		UE_LOG(LogTemp, Error, TEXT("ItemDataTable is NULL"));
		return FItemData();
	}
	
	FItemData* ItemData = ItemDataTable->FindRow<FItemData>(ItemRowName, TEXT("Item Lookup"));
	if (ItemData)
	{
		return *ItemData;
	}
	else
	{
		{
			UE_LOG(LogTemp, Error, TEXT("ItemDataTable is NULL"));
			return FItemData();
		}
	}
}

void UInventoryActorComponent::AddItemToInventory(FName ItemRowName, int32 quantity)
{
	if (IsInventoryFull())
	{
		UE_LOG(LogTemp, Warning, TEXT("Inventory Full"));
		return;
	}
	
	if (Inventory.Contains(ItemRowName))	// if it already has an item 
	{
		FInventoryItem& ExistingItem = Inventory[ItemRowName];

		if (ExistingItem.ItemData.bIsStackable)		// about quantity
		{
			ExistingItem.Quantity += quantity;
			UE_LOG(LogTemp, Log, TEXT("Increased quantity of item with ID %s to %d."), *ItemRowName.ToString(), ExistingItem.Quantity);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Item %s is not stackable!"), *ItemRowName.ToString());
		}
	}
	else		// if it does not have an item
	{
		if (ItemDataTable)
		{
			FItemData ItemData = LoadItemFromDataTable(ItemRowName);
			FInventoryItem NewItem;
			NewItem.ItemData = ItemData;
			NewItem.Quantity = quantity;
			Inventory.Add(ItemRowName, NewItem);
		}
	}
}

void UInventoryActorComponent::RemoveItemFromInventory(FName ItemRowName, int32 quantity)
{
	if (Inventory.Contains(ItemRowName))
	{
		FInventoryItem& ItemData = Inventory[ItemRowName];
		ItemData.Quantity -= quantity;
		if (ItemData.Quantity <= 0)
		{
			Inventory.Remove(ItemRowName);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Item %s not found in inventory."),  *ItemRowName.ToString());
	}
}

bool UInventoryActorComponent::IsInventoryFull() const
{
	return Inventory.Num() >= MaxInventorySize;
}


// Called when the game starts
void UInventoryActorComponent::BeginPlay()
{
	Super::BeginPlay();

}

