// #include "E:\Project\Cat\Cat\Intermediate\Build\Win64\x64\HumanAndCatEditor\Development\UnrealEd\SharedPCH.UnrealEd.Project.ValApi.Cpp20.h"
#include "HumanAndCat/Public/Utilities/HumanAndCatTags.h"

namespace StateTags
{
		UE_DEFINE_GAMEPLAY_TAG(State, TEXT("State"));
		UE_DEFINE_GAMEPLAY_TAG(State_Idle, TEXT("State.Idle"));
		UE_DEFINE_GAMEPLAY_TAG(State_Run, TEXT("State.Run"));
		UE_DEFINE_GAMEPLAY_TAG(State_Attack, TEXT("State.Attack"));
		UE_DEFINE_GAMEPLAY_TAG(State_AttackCharge, TEXT("State.AttackCharge"));
		UE_DEFINE_GAMEPLAY_TAG(State_Dodge, TEXT("State.Dodge"));
		UE_DEFINE_GAMEPLAY_TAG(State_Equip, TEXT("State.Equip"));
		UE_DEFINE_GAMEPLAY_TAG(State_UnEquip, TEXT("State.UnEquip"));
		UE_DEFINE_GAMEPLAY_TAG(State_Jump, TEXT("State.Jump"));
		UE_DEFINE_GAMEPLAY_TAG(State_Falling, TEXT("State.Falling"));
		UE_DEFINE_GAMEPLAY_TAG(State_Hit, TEXT("State.Hit"));
		UE_DEFINE_GAMEPLAY_TAG(State_Die, TEXT("State.Die"));
		UE_DEFINE_GAMEPLAY_TAG(State_Riding, TEXT("State.Riding"));
}

namespace AbilityTags
{
		UE_DEFINE_GAMEPLAY_TAG(Ability, TEXT("Ability"));
		UE_DEFINE_GAMEPLAY_TAG(Ability_Attack_NormalAttack, TEXT("Ability.Attack.NormalAttack"));
		UE_DEFINE_GAMEPLAY_TAG(Ability_Attack_SpecialAttack, TEXT("Ability.Attack.SpecialAttack"));
		UE_DEFINE_GAMEPLAY_TAG(Ability_Dodge, TEXT("Ability.Dodge"));
		UE_DEFINE_GAMEPLAY_TAG(Ability_AttackCharge, TEXT("Ability.AttackCharge"))
		UE_DEFINE_GAMEPLAY_TAG(Ability_Equip, TEXT("Ability.Equip"));
		UE_DEFINE_GAMEPLAY_TAG(Ability_UnEquip, TEXT("Ability.UnEquip"));
		UE_DEFINE_GAMEPLAY_TAG(Ability_Death, TEXT("Ability.Death"));
		UE_DEFINE_GAMEPLAY_TAG(Ability_Hit, TEXT("Ability.Hit"));
	
}

namespace InputTags
{
	UE_DEFINE_GAMEPLAY_TAG(Input_MoveForWard, TEXT("Input.MoveForWard"));
	UE_DEFINE_GAMEPLAY_TAG(Input_MoveRight, TEXT("Input.MoveRight"));
	UE_DEFINE_GAMEPLAY_TAG(Input_NorMalAttack, TEXT("Input.NorMalAttack"));
	UE_DEFINE_GAMEPLAY_TAG(Input_AttackCharging, TEXT("Input.AttackCharging"));	
	UE_DEFINE_GAMEPLAY_TAG(Input_SpecialAttack, TEXT("Input.SpecialAttack"));
	UE_DEFINE_GAMEPLAY_TAG(Input_Dodge, TEXT("Input.Dodge"));
}

namespace WeaponTags
{
	UE_DEFINE_GAMEPLAY_TAG(Weapon_Fist, TEXT("Weapon.Fist"));
	UE_DEFINE_GAMEPLAY_TAG(Weapon_Sword, TEXT("Weapon.Sword"));
	UE_DEFINE_GAMEPLAY_TAG(Weapon_Staff, TEXT("Weapon.Staff"));
		
}
