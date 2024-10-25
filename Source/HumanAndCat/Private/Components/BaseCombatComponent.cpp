// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/BaseCombatComponent.h"

#include "Cameras/BaseCameraComponent.h"
#include "Components/CameraManagerComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"


UBaseCombatComponent::UBaseCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UBaseCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void UBaseCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                         FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// 타겟 액터가 존재한다면 Tick 마다 일정 범위 안에 타겟 액터가 존재하는지 확인합니다.
	// 타겟 액터가 일정 범위를 넘어서면 타겟팅을 풀어버립니다.
	if(IsValid(TargetActor))
	{
		FindInRandgeTargets();
		bIsTarget = false;
		bool Localbool = FocusingTargets.Contains(TargetActor);

		if(!Localbool)
		{
			DisableLockOn();
		}
	}
	else if(!bIsTarget && !IsValid(TargetActor))
	{
		bIsTarget = true;
		DisableLockOn();
	}
}

void UBaseCombatComponent::InitCombatComponent(UCameraComponent* CameraComponent)
{
	OwnerCamera = CameraComponent;
}

// 타겟팅 입력이 들어오면 호출됩니다.
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

	// 특정 반경 안에 Actor 들 중에 원하는 타입 및 클래스의 Actor 를 찾아 저장합니다.
	UKismetSystemLibrary::SphereOverlapActors(GetOwner(), GetOwner()->GetActorLocation(),
		TargetingRadius,TargetsType, TargetClass, IgnoreActors,FoundActors);

	// 찾은 Actor 들을 멤버에 저장합니다.
	FocusingTargets = FoundActors;
}

void UBaseCombatComponent::SelectTarget()
{
	if(!TargetActor)
	{
		TMap<AActor*, float> LocalEnableTargets;

		for(AActor*& Target : FocusingTargets)
		{
			// 해당 Target 후보와 캐릭터를 기준으로 거리 계산을 하고 저장합니다.
			LocalEnableTargets.Add(Target, UKismetMathLibrary::Abs(CalculateAngleFromCamera(Target)));
		}
		
		if(LocalEnableTargets.Num()>0)
		{
			TArray<AActor*> LocalActors;
			TArray<float> LocalAngles;
			// 키와 값을 나누어 관리합니다.
			LocalEnableTargets.GenerateKeyArray(LocalActors);
			LocalEnableTargets.GenerateValueArray(LocalAngles);

			int32 Idx;
			// 거리가 가장 짧은 Actor 의 Index 를 반환 합니다.
			float MaxValue = FMath::Min<float>(LocalAngles, &Idx);
			// TargetActor 가 지정되고 타겟팅을 시작합니다.
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

	if(Actor && OwnerCamera)
	{
		AActor* PActor =  GetOwner();
		UCameraManagerComponent* GameCamera = PActor->GetComponentByClass<UCameraManagerComponent>();
		if(GameCamera)
		{
			// 타겟 액터를 바라보기 위해 필요한 회전 값(카메라 -> 타겟 액터)을 계산합니다.
			FRotator RequireRot  = UKismetMathLibrary::FindLookAtRotation(GameCamera->GetInGameCamera()->GetComponentLocation(), Actor->GetActorLocation());

			ACharacter* PCharacter = Cast<ACharacter>(PActor);
			// RequireRot과 캐릭터의 현재 컨트롤 회전 값 사이의 차이를 계산하여,
			// 그 차이를 반환합니다.
			DeltaRot = UKismetMathLibrary::NormalizedDeltaRotator(RequireRot, PCharacter->GetControlRotation());
		}
	}
	// 최종적으로 회전 값 중 y,z 의 합을 반환하여 가장 짧은 위치에 존재하는 TargetActor 후보를 찾도록 합니다. 
	return UKismetMathLibrary::Abs(UKismetMathLibrary::Abs(DeltaRot.Yaw) + UKismetMathLibrary::Abs(DeltaRot.Pitch));
}

void UBaseCombatComponent::DisableLockOn()
{
	AActor* PActor =  GetOwner();
	UCameraManagerComponent* GameCamera = PActor->GetComponentByClass<UCameraManagerComponent>();

	if(!GameCamera) return;
	GameCamera->SetIsTarget(false);

	ACharacter* PCharacter = Cast<ACharacter>(PActor);
	// 타겟팅을 취소하며 캐릭터를 기본 셋팅으로 변환합니다.
	if(PCharacter)
	{
		PCharacter->GetCharacterMovement()->bOrientRotationToMovement = true;
		TargetActor = nullptr;
		PCharacter->GetCharacterMovement()->MaxWalkSpeed = 600.f;
		OnInFocusing.Broadcast(false);
		USpringArmComponent* Arm = PCharacter->GetComponentByClass<USpringArmComponent>();
		if(Arm)
		{
			Arm->bInheritPitch = true;
			AGameModeBase* Mode = GetWorld()->GetAuthGameMode();
			if(Mode)
			{
				Arm->AttachToComponent(PCharacter->GetRootComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
				Arm->SetRelativeLocation(FVector(0, 0, 60.f));
			}
			Arm->bEnableCameraLag = true;
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
	if(!PCharacter) return;
	// 타겟팅이 시작되며 움직임에 따른 회전을 false 하여 TargetActor 를 바라보게 하며 속도를 지정합니다.
	PCharacter->GetCharacterMovement()->bOrientRotationToMovement = false;
	PCharacter->GetCharacterMovement()->MaxWalkSpeed = 450.f;
	
	// ABP 에게 포커싱이 되었음 알려줍니다. 블렌드 스페이스를 변경하기 위함입니다.
	OnInFocusing.Broadcast(true);
	USpringArmComponent* Arm = PCharacter->GetComponentByClass<USpringArmComponent>();
	if(Arm)
	{
		// 스프링암의 피치 값 상속을 false 로 하여 카메라 제어를 별도로 가능하도록 만듭니다.
		Arm->bInheritPitch = false;
		AGameModeBase* Mode = GetWorld()->GetAuthGameMode();
		if(Mode)
		{
			// 게임모드에게 스프링암을 부착합니다. 이는, 타겟팅 시 카메라의 움직임을 별도로 제어하기 위함입니다. ( 캐릭터를 따라 움직이지 않습니다)
			Arm->AttachToComponent(Mode->GetRootComponent(), FAttachmentTransformRules::KeepWorldTransform);
		}
		Arm->bEnableCameraLag = false;
	}
}
