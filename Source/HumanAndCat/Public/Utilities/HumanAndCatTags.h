#pragma once

#include "NativeGameplayTags.h"

namespace StateTags
{
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(State)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Idle)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Run)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Attack)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_AttackCharge)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Dodge)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Equip)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_UnEquip)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Jump)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Falling)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Hit)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Die)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Riding)
}

namespace AbilityTags
{
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Attack_NormalAttack)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_AttackCharge)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Attack_SpecialAttack)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Dodge)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Equip)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_UnEquip)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Death) 
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Hit) 
}

namespace InputTags
{
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_MoveForWard)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_MoveRight)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_NorMalAttack)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_AttackCharging)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_SpecialAttack)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Dodge)	
}
namespace WeaponTags
{
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Fist)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Sword)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Staff)
		
}

namespace CameraTags
{
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Camera_InGame)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Camera_Ultimate)
		
}