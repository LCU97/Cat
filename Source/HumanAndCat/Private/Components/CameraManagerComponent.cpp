// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CameraManagerComponent.h"

#include "Cameras/BaseCameraComponent.h"
#include "Components/BaseCombatComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"
#include "Utilities/HumanAndCatTags.h"


// Sets default values for this component's properties
UCameraManagerComponent::UCameraManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCameraManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	CombatComponent = GetOwner()->GetComponentByClass<UBaseCombatComponent>();
}


// Called every frame
void UCameraManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                            FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	if(bIsTarget)
	{
		InGameLockOn();
	}
	else
	{
		InGameLockDown();
	}
}

void UCameraManagerComponent::InGameLockOn()
{
	if(CurrentCamera->CameraTag != CameraTags::Camera_InGame) return;
	if(!CombatComponent) return;
	if(!CombatComponent->TargetActor) bIsTarget = false;
	
	FVector TargetLocation = CombatComponent->TargetActor->GetActorLocation();
	
	FRotator Rot = UKismetMathLibrary::FindLookAtRotation(CurrentCamera->GetComponentLocation(), TargetLocation);
	
	float Dis = FVector::Distance( TargetLocation,GetOwner()->GetActorLocation());

	float Alpha;
	if(Dis > 500.f)
	{
		Alpha = 0.2f;
	}
	else
	{
		Alpha = 0.4f;
	}

	ACharacter* PCharacter = Cast<ACharacter>(GetOwner());
	if(!PCharacter) return;
	
	AController* PCon = PCharacter->GetController();
	if(!PCon) return;
	
	FRotator PRot = PCon->GetControlRotation();
	FRotator CalRot = UKismetMathLibrary::RLerp(Rot,PRot , Alpha, true);

	float Pit = UKismetMathLibrary::Clamp(CalRot.Pitch, -15.f, 30.f);

	FRotator FinalRot = FRotator(PRot.Roll, Pit, CalRot.Yaw);
	
	PCon->SetControlRotation(FinalRot);
}

void UCameraManagerComponent::InGameLockDown()
{
	if(CurrentCamera->CameraTag != CameraTags::Camera_InGame) return;
	if(!CombatComponent) return;
	if(!CombatComponent->TargetActor) return;

	
}

