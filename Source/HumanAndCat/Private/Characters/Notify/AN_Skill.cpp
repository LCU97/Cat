// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Notify/AN_Skill.h"

#include "Components/WeaponComponent.h"
#include "Weapons/BaseWeapon.h"


void UAN_Skill::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                       const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	UWeaponComponent* WeaponComponent =
					Cast<UWeaponComponent>(MeshComp->GetOwner()->GetComponentByClass(UWeaponComponent::StaticClass()));
	if(!WeaponComponent) return;
	
	ABaseWeapon* Weapon;	
	WeaponComponent->GetCurrentWeapon(Weapon);	
	if(!Weapon) return;
	
	switch (SkillIdx)
	{
		case 0:
			{				
				Weapon->SkillAttack(UsedSkill);
				break;
			}
		case 1:
			{
				Weapon->SkillAttack2(UsedSkill);
				break;
			}
		default:
			break;
	}
}
