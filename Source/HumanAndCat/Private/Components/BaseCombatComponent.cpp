// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/BaseCombatComponent.h"

#include "Cameras/BaseCameraComponent.h"
#include "Components/CameraManagerComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values for this component's properties
UBaseCombatComponent::UBaseCombatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBaseCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBaseCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                         FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	if(TargetActor)
	{
		FindInRandgeTargets();

		bool Localbool = FocusingTargets.Contains(TargetActor);

		if(!Localbool)
		{
			DisableLockOn();
		}
	}
}

void UBaseCombatComponent::InitCombatComponent(UCameraComponent* CameraComponent)
{
	OwnerCamera = CameraComponent;
}

void UBaseCombatComponent::SearchTargetActor()
{
	FindInRandgeTargets();
	SelectTarget();
}

void UBaseCombatComponent::FindInRandgeTargets()
{
	TArray<AActor*> FoundActors;
	TArray<AActor*> IgnoreActors;

	IgnoreActors.Add(GetOwner());

	UKismetSystemLibrary::SphereOverlapActors(GetOwner(), GetOwner()->GetActorLocation(), TargetingRadius,TargetsType, TargetClass, IgnoreActors,FoundActors);

	TArray<AActor*> EnableActors;

	for(AActor*& Enemy : FoundActors)
	{
		if ( CanBeTargeted(Enemy))
		{
			EnableActors.AddUnique(Enemy);
		}
	}
	FocusingTargets = EnableActors;
}

void UBaseCombatComponent::SelectTarget()
{
	if(!TargetActor)
	{
		TMap<AActor*, float> LocalEnableTargets;

		for(AActor*& Target : FocusingTargets)
		{
			if(CanBeTargeted(Target))
			{
				LocalEnableTargets.Add(Target, UKismetMathLibrary::Abs(CalculateAngleFromCamera(Target)));
			}
		}
		
		if(LocalEnableTargets.Num()>0)
		{
			TArray<AActor*> LocalActors;
			TArray<float> LocalAngles;
			LocalEnableTargets.GenerateKeyArray(LocalActors);
			LocalEnableTargets.GenerateValueArray(LocalAngles);

			int32 Idx;
			float MaxValue = FMath::Min<float>(LocalAngles, &Idx);
			TargetActor = LocalActors[Idx];
			LockOnTarget();
		}
	}
	else
	{
		DisableLockOn();
	}
	
}

float UBaseCombatComponent::CalculateAngleFromCamera(AActor* Actor)
{
	FRotator DeltaRot;

	if(TargetActor && OwnerCamera)
	{
		AActor* PActor =  GetOwner();
		UCameraManagerComponent* GameCamera = PActor->GetComponentByClass<UCameraManagerComponent>();
		if(GameCamera)
		{
			
			FRotator RequireRot  = UKismetMathLibrary::FindLookAtRotation(GameCamera->InGameCamera->GetComponentLocation(), TargetActor->GetActorLocation());

			ACharacter* PCharacter = Cast<ACharacter>(PActor);
			DeltaRot = UKismetMathLibrary::NormalizedDeltaRotator(RequireRot, PCharacter->GetControlRotation());
		}
	}
	
	return UKismetMathLibrary::Abs(UKismetMathLibrary::Abs(DeltaRot.Yaw) + UKismetMathLibrary::Abs(DeltaRot.Pitch));
}

void UBaseCombatComponent::DisableLockOn()
{
	AActor* PActor =  GetOwner();
	UCameraManagerComponent* GameCamera = PActor->GetComponentByClass<UCameraManagerComponent>();

	if(!GameCamera) return;
	GameCamera->SetIsTarget(false);

	ACharacter* PCharacter = Cast<ACharacter>(PActor);
	if(PCharacter)
	{
		PCharacter->GetCharacterMovement()->bOrientRotationToMovement = true;
		TargetActor = nullptr;
		PCharacter->GetCharacterMovement()->MaxWalkSpeed = 450.f;
		OnInFocusing.Broadcast(false);
		USpringArmComponent* Arm = PCharacter->GetComponentByClass<USpringArmComponent>();
		if(Arm)
		{
			Arm->bInheritPitch = true;
		}
	}
}

void UBaseCombatComponent::LockOnTarget()
{
	AActor* PActor =  GetOwner();
	UCameraManagerComponent* GameCamera = PActor->GetComponentByClass<UCameraManagerComponent>();

	if(!GameCamera) return;
	GameCamera->SetIsTarget(true);

	ACharacter* PCharacter = Cast<ACharacter>(PActor);
	if(PCharacter)
	{
		PCharacter->GetCharacterMovement()->bOrientRotationToMovement = false;
		PCharacter->GetCharacterMovement()->MaxWalkSpeed = 300.f;
		OnInFocusing.Broadcast(true);
		USpringArmComponent* Arm = PCharacter->GetComponentByClass<USpringArmComponent>();
		if(Arm)
		{
			Arm->bInheritPitch = false;
		}
	}
}

bool UBaseCombatComponent::CanBeTargeted(AActor* Target)
{
	if(!bInCombat) return false;

	
	// TODO
	// 액터에게 몬스터 태그가 있는지 확인

	return true;
}

