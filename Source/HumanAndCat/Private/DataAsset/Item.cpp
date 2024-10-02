// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/Item.h"
#include "Characters/AdventurePlayer.h"

// Sets default values
AItem::AItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AItem::OnPickUp(class AAdventurePlayer* Player)
{
	if (Player)
	{
		//Player->AddItemToInventory(ItemData);
		Destroy();
	}
}

void AItem::OnDrop(class AAdventurePlayer* Player)
{
	if (Player)
	{
		FVector DropLocation = Player->GetActorLocation() + Player->GetActorForwardVector()*100;
		AItem* DroppedItem = GetWorld()->SpawnActor<AItem>(GetClass(), DropLocation, FRotator::ZeroRotator);
		DroppedItem->ItemData = ItemData;

		// remove the item from the inventory
		//Player->RemoveItemFromInventory(ItemData.ItemID);
	}
}
