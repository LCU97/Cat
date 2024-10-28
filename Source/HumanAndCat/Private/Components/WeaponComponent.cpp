
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

UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* Own = GetOwner();
	OwnerCharacter = Cast<ACharacter>(Own);
	if(!OwnerCharacter) return;
}

void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UWeaponComponent::InitWeaponComponent()
{
	// 시작 시 초기화 입니다.
	if (IsValid(CurrentWeapon))
	{
		return;	
	}
	CurrentWeaponTag = FGameplayTag();
	CurrentWeaponType = nullptr;
	CurrentWeaponName = EWeaponName::None;
	
	if(!BasicWeapon) return;;

	// 기본 무기를 스폰합니다,.
	ABaseWeapon* BasicFistWeapon = GetWorld()->SpawnActor<ABaseWeapon>(BasicWeapon);

	if(BasicFistWeapon)
	{
		BasicFistWeapon->SetWeaponManager(this);
		// 기본 무기에 따른 상태와 어빌리티를 등록하고 현재 무기의 정보를 업데이트 합니다.
		RegisterStateAndAbility(BasicFistWeapon);
		
		BasicWeaponInstanced = BasicFistWeapon;
	}
}

void UWeaponComponent::UpdateStates()
{
	UBaseStateManagerComponent* StateManagerComponent =
		OwnerCharacter->GetController()->GetComponentByClass<UBaseStateManagerComponent>();
	if(StateManagerComponent)
	{
		StateManagerComponent->ClearStatesComponent();
		// DA 에 있는 해당 무기의 State 들을 생성하고 IDle 상태로 변환합니다.
		for(int32 i = 0; i < CurrentWeaponType->States.Num(); i++)
		{
			UBaseStateObject* LocalState = nullptr;
			StateManagerComponent->ConstructStateOfClass(CurrentWeaponType->States[i],LocalState);
		}
		// 초기화되면 Idle 로 강제 변환
		UBaseStateObject* LocalIdleState = StateManagerComponent->GetStateOfGameplayTag(StateTags::State_Idle);
		if(LocalIdleState)
		{
			StateManagerComponent->ChangeStateOfClass(LocalIdleState->GetClass());
		}
	}
}

void UWeaponComponent::UpdateAbilities()
{
	UBaseAbilityManagerComponent* AbilityManagerComponent =
		OwnerCharacter->GetComponentByClass<UBaseAbilityManagerComponent>();
	if(AbilityManagerComponent)
	{
		// DA 에 있는 해당 무기의 Ability 들을 생성하고 초기화합니다/.
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
		// TMap 의 Tag 와 현재 무기를 비교해서 현재 무기에 따른 DA 를 가져와 State Ability 를 초기화합니다. 
		if(WeaponType.Key == CheckingWeaponType->WeaponTag)
		{
			CheckingWeaponType->SetWeaponManager(this);
			if(IsValid(CurrentWeapon))
			{				
				CurrentWeaponTag = FGameplayTag();
				CurrentWeaponType = nullptr;
				CurrentWeaponName = EWeaponName::None;
				CurrentWeapon->Destroy();
				CurrentWeaponLength = 0.f;
			}
			// 바뀔 현재 무기 타입을 재설정합니다.
			CurrentWeapon = CheckingWeaponType;
			CurrentWeaponTag = CheckingWeaponType->WeaponTag;
			CurrentWeaponType = WeaponType.Value;
			CurrentWeaponName = CurrentWeaponType->WeaponName;
			CurrentWeaponLength = CheckingWeaponType->TraceLength;
			
			// 상태 업데이트 및 Idle 상태로 시작
			UpdateStates();

			UpdateAbilities();

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
			// 현재 무기가 손에 들고 있는지 기본 모드인지에 따라 Equip, UnEquip 을 실행합니다.
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
	ABaseWeapon* BasicFistWeapon = GetWorld()->SpawnActor<ABaseWeapon>(BasicWeapon);

	// 다시 기본무기로 변경합니다.
	if(BasicFistWeapon)
	{
		BasicFistWeapon->SetWeaponManager(this);

		RegisterStateAndAbility(BasicFistWeapon);
		
		BasicWeaponInstanced = BasicFistWeapon;
	}	
}

void UWeaponComponent::Equip()
{
	FName EquipSocket = CurrentWeapon->GetEquipSocket();

	if(!EquipSocket.IsNone())
	{
		// 무기가 가지는 소켓 네임을 가져와 부착합니다.
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
			// 무기가 가지는 소켓 네임을 가져와 부착합니다.
			CurrentWeapon->AttachToComponent(CharacterMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, UnEquipSocket);
			bEquip = false;
		}
	}
}

