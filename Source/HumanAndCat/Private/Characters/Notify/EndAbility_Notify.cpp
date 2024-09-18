// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Notify/EndAbility_Notify.h"

#include "Components/BaseAbilityManagerComponent.h"
#include "Objects/BaseAbilityObject.h"

void UEndAbility_Notify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	//
	AActor* Own = MeshComp->GetOwner();//
	if(Own)
	{
		UBaseAbilityManagerComponent* AbilityManagerComponent =Own->GetComponentByClass<UBaseAbilityManagerComponent>();
		if(AbilityManagerComponent)
		{
			AbilityManagerComponent->GetCurrentAbility()->EndAbility();
		}
	}
	
}
