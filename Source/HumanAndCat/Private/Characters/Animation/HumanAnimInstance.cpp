// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Animation/HumanAnimInstance.h"

#include "Components/BaseCombatComponent.h"
#include "Components/WeaponComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UHumanAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	APawn* PPawn = TryGetPawnOwner();
	if(!PPawn) return;
	
	PlayerCharacter = Cast<ACharacter>(PPawn);

}

void UHumanAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APawn* PPawn = TryGetPawnOwner();
	if(!PPawn) return;
	FVector2D Vel2D;
	Vel2D.X = PPawn->GetVelocity().X;
	Vel2D.Y = PPawn->GetVelocity().Y;
	
	RunSpeed = Vel2D.Length();

	ACharacter* PCharacter = Cast<ACharacter>(PPawn);

	if(PCharacter)
	{
		bIsFalling = PCharacter->GetCharacterMovement()->IsFalling();
	}
	
	
	if(PlayerCharacter &&!bIsWeaponComponentBound)
	{
		UWeaponComponent* WeaponComponent = PlayerCharacter->GetComponentByClass<UWeaponComponent>();
		if(WeaponComponent)
		{
			WeaponComponent->OnWeaponNameChanged.AddDynamic(this, &ThisClass::SetWeaponName);
			bIsWeaponComponentBound = true;
		}
	}
	if(PlayerCharacter&& !bIsCombatComponentBound)
	{
		UBaseCombatComponent* CombatComponent = PlayerCharacter->GetComponentByClass<UBaseCombatComponent>();
		if(CombatComponent)
		{
			CombatComponent->OnInCombatChanged.AddDynamic(this, &ThisClass::SetInCombat);
			bIsCombatComponentBound = true;
		}
	}
}
