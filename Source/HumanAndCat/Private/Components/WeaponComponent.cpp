// Fill out your copyright notice in the Description page of Project Settings.


#include "HumanAndCat/Public/Components/WeaponComponent.h"

#include "GeometryTypes.h"
#include "Characters/Animation/HumanAnimInstance.h"
#include "Components/BaseAbilityManagerComponent.h"
#include "Components/BaseStateManagerComponent.h"
#include "GameFramework/Character.h"
#include "Objects/BaseStateObject.h"
#include "Weapons/BaseWeapon.h"
#include "Weapons/FistWeapon.h"
#include "HumanAndCat/Public/Utilities/HumanAndCatTags.h"


// Sets default values for this component's properties
UWeaponComponent::UWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	AActor* Own = GetOwner();
	OwnerCharacter = Cast<ACharacter>(Own);
	if(!OwnerCharacter) return;
}


// Called every frame
void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UWeaponComponent::InitWeaponComponent()
{
	if (IsValid(CurrentWeapon))
	{
		return;	
	}
	CurrentWeaponTag = FGameplayTag();
	CurrentWeaponType = nullptr;
	CurrentWeaponName = EWeaponName::None;
	
	if(!BasicWeapon) return;;
	
	ABaseWeapon* BasicFistWeapon = GetWorld()->SpawnActor<ABaseWeapon>(BasicWeapon);

	if(BasicFistWeapon)
	{
		BasicFistWeapon->SetWeaponManager(this);

		RegisterStateAndAbility(BasicFistWeapon);
		
		BasicWeaponInstanced = BasicFistWeapon;
	}
}

void UWeaponComponent::UpdateStates()
{
	UBaseStateManagerComponent* StateManagerComponent = OwnerCharacter->GetController()->GetComponentByClass<UBaseStateManagerComponent>();
	if(StateManagerComponent)
	{
		StateManagerComponent->ClearStatesComponent();
		for(int32 i = 0; i < CurrentWeaponType->States.Num(); i++)
		{
			UBaseStateObject* LocalState = nullptr;
			StateManagerComponent->ConstructStateOfClass(CurrentWeaponType->States[i],LocalState);
		}

		UBaseStateObject* LocalIdleState = StateManagerComponent->GetStateOfGameplayTag(StateTags::State_Idle);
		if(LocalIdleState)
		{
			StateManagerComponent->ChangeStateOfClass(LocalIdleState->GetClass());
		}
	}
}

void UWeaponComponent::UpdateAbilities()
{
	UBaseAbilityManagerComponent* AbilityManagerComponent = OwnerCharacter->GetComponentByClass<UBaseAbilityManagerComponent>();
	if(AbilityManagerComponent)
	{
		AbilityManagerComponent->ClearAbilityManager();
		for(int32 i = 0; i<CurrentWeaponType->Abilities.Num(); i++)
		{
			FAbilityList LocalAbilityList = CurrentWeaponType->Abilities[i];
			UBaseAbilityObject* LocalAbilityObject;
			AbilityManagerComponent->ContructAbilityOfClass(LocalAbilityList.AbilityObject, LocalAbilityObject);
		}
	}
}

void UWeaponComponent::RegisterStateAndAbility(ABaseWeapon* CheckingWeaponType)
{
	if(!CheckingWeaponType) return;

	if(WeaponTypes.IsEmpty()) return;

	for(auto WeaponType : WeaponTypes)
	{
		if(WeaponType.Key == CheckingWeaponType->WeaponTag)
		{
			if(IsValid(CurrentWeapon))
			{				
				CurrentWeaponTag = FGameplayTag();
				CurrentWeaponType = nullptr;
				CurrentWeaponName = EWeaponName::None;
				CurrentWeapon->Destroy();
				CurrentWeaponLength = 0.f;
			}
			CurrentWeapon = CheckingWeaponType;
			CurrentWeaponTag = CheckingWeaponType->WeaponTag;
			CurrentWeaponType = WeaponType.Value;
			CurrentWeaponName = CurrentWeaponType->WeaponName;
			CurrentWeaponLength = CheckingWeaponType->TraceLength;

			

			// 상태 업데이트 및 Idle 상태로 시작
			UpdateStates();

			UpdateAbilities();

			// 애니메이션에게 무기가 바뀌었음을 알려주기
			//if(OnWeaponNameChanged.IsBound())
			//{
			//	OnWeaponNameChanged.Broadcast(CurrentWeaponName);
			//}


			// 임시 방편
			AActor* ActorOwner = GetOwner();
			if(ActorOwner)
			{
				ACharacter* CharacterOwner = Cast<ACharacter>(ActorOwner);
				if(CharacterOwner)
				{
					UAnimInstance* OwnerAnim = CharacterOwner->GetMesh()->GetAnimInstance();
					if(OwnerAnim)
					{
						UHumanAnimInstance* HumanAnimInstance = Cast<UHumanAnimInstance>(OwnerAnim);
						if(HumanAnimInstance)
						{
							HumanAnimInstance->OnNewWeaponNameChanged.Broadcast(CurrentWeaponName);
						}
					}
				}
			}
			// 처음에는 장착 안한 상태
			if(bEquip)
			{
				Equip();
			}
			else
			{
				UnEquip();
			}
			return;
		}
	}
}

void UWeaponComponent::UnregisterStateAndAility()
{
	// 기본 무기로 바꾸기
	if(CurrentWeapon->GetClass() == BasicWeapon)
	{
		return;
	}
	CurrentWeapon->Destroy(); 
	RegisterStateAndAbility(BasicWeaponInstanced);	
}

void UWeaponComponent::Equip()
{
	FName EquipSocket = CurrentWeapon->GetEquipSocket();

	if(!EquipSocket.IsNone())
	{
		USkeletalMeshComponent* CharacterMesh = GetOwner()->FindComponentByClass<USkeletalMeshComponent>();
		if (CharacterMesh)
		{
			CurrentWeapon->AttachToComponent(CharacterMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, EquipSocket);
			bEquip = true;
		}
	}
}

void UWeaponComponent::UnEquip()
{
	FName UnEquipSocket = CurrentWeapon->GetUnEquipSocket();

	if(!UnEquipSocket.IsNone())
	{
		USkeletalMeshComponent* CharacterMesh = GetOwner()->FindComponentByClass<USkeletalMeshComponent>();
		if (CharacterMesh)
		{
			CurrentWeapon->AttachToComponent(CharacterMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, UnEquipSocket);
			bEquip = false;
		}
	}
}

