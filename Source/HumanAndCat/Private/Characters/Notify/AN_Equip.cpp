// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Notify/AN_Equip.h"

#include "Components/WeaponComponent.h"

void UAN_Equip::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                       const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	AActor* Own = MeshComp->GetOwner();
	if(Own)
	{
		UWeaponComponent* WeaponComp =Own->GetComponentByClass<UWeaponComponent>();
		if(WeaponComp)
		{
			WeaponComp->Equip();
		}
	}
}
