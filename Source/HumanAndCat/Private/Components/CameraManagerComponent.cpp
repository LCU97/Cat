// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CameraManagerComponent.h"

#include "Cameras/BaseCameraComponent.h"
#include "Components/BaseCombatComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
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
	ArmComponent = GetOwner()->GetComponentByClass<USpringArmComponent>();
}


// Called every frame
void UCameraManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                            FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	//UE_LOG(LogTemp, Warning, TEXT("%f %f %f"), CurrentCamera->GetComponentLocation().X, CurrentCamera->GetComponentLocation().Y, CurrentCamera->GetComponentLocation().Z);
	ACharacter* PCharacter = Cast<ACharacter>(GetOwner());
	if(!PCharacter) return;
	
	
	if(bIsTarget)
	{
		InGameLockOn();
	}
	else
	{
		InGameLockDown();
	}

	if(UltiLerpDuration > 0.0f && CurrentCamera == UltimateCamera)
	{
		UltiMovingLerp();
		FVector Loc = PCharacter->GetMesh()->GetComponentLocation();
		Loc.Z += 80.f;
		FRotator Rot = UKismetMathLibrary::FindLookAtRotation(UltimateCamera->GetComponentLocation(),Loc );
		UltimateCamera->SetWorldRotation(Rot);
	}
}

void UCameraManagerComponent::InitCameraManager(UBaseCameraComponent* InGame, UBaseCameraComponent* Ultimate)
{
	InGameCamera = InGame;
	UltimateCamera = Ultimate;
	CurrentCamera = InGameCamera;
	
	ACharacter* PCharacter = Cast<ACharacter>(GetOwner());
	if(!PCharacter) return;	
	AController* PController = PCharacter->GetController();
	if(!PController) return;
	APlayerController* PlayerCon = Cast<APlayerController>(PController);
	if(!PlayerCon) return;
	
	PCon = PlayerCon;
		
}

void UCameraManagerComponent::ChangeUltiCamera(float Duration)
{
	if(InGameCamera && UltimateCamera)
	{
		InGameCamera->SetActive(false);
		UltimateCamera->SetActive(true);
		CurrentCamera = UltimateCamera;
		UltiLerpDuration = Duration;
		UltiMovintStartTime = GetWorld()->GetTimeSeconds();
	}
}

void UCameraManagerComponent::ChangeInGameCamera()
{
	if(InGameCamera && UltimateCamera)
	{
		InGameCamera->SetActive(true);
		UltimateCamera->SetActive(false);
		PCon->SetViewTargetWithBlend(GetOwner(), 1.f, EViewTargetBlendFunction::VTBlend_Cubic);
		CurrentCamera = InGameCamera;
		UltiLerpDuration = -1;
	}
}

void UCameraManagerComponent::UltiMovingLerp()
{
	ACharacter* PCharacter = Cast<ACharacter>(GetOwner());
	
	FVector OwnerLocation = PCharacter->GetMesh()->GetSocketLocation(FName("RootMotionSocket"));

	FTransform SocketTransform = PCharacter->GetMesh()->GetSocketTransform(FName("RootMotionSocket"));
	
	
	//FVector OwnerLocation = PCharacter->GetMesh()->GetComponentLocation();
	OwnerLocation.Z += 100.f;
	//FVector OwnerLocation = GetOwner()->GetActorLocation();
	
	FVector OwnerForWardVec = GetOwner()->GetActorForwardVector();
	
	FVector OwnerRightVec = SocketTransform.GetRotation().GetRightVector();

	FVector NewLocation = FVector((OwnerLocation.X - OwnerForWardVec.X * 400.f),(OwnerLocation.Y - OwnerForWardVec.Y * 400.f), OwnerLocation.Z);

	UltimateCamera->SetWorldLocation(NewLocation);
}


FVector UCameraManagerComponent::CalNewPositionUltiCamera(FVector P0, FVector P1, FVector P2, FVector P3, float t)
{
	float u = 1 - t;

	FVector point = u*u*u * P0; // (1-t)^3 * P0
	point += 3 * u*u * t * P1; // 3 * (1-t)^2 * t * P1
	point += 3 * u * t*t * P2; // 3 * (1-t) * t^2 * P2
	point += t*t*t * P3;        // t^3 * P3

	return point;
}


void UCameraManagerComponent::InGameLockOn()
{
	if(CurrentCamera->CameraTag != CameraTags::Camera_InGame) return;
	if(!CombatComponent) return;
	if(!CombatComponent->TargetActor) bIsTarget = false;
	
	FVector TargetLocation = CombatComponent->TargetActor->GetActorLocation();	
	FRotator Rot = UKismetMathLibrary::FindLookAtRotation(GetOwner()->GetActorLocation(), TargetLocation);
	
	float Dis = FVector::Distance( TargetLocation,GetOwner()->GetActorLocation());
	float Alpha;
	
	if(Dis > StandardDis)
	{
		Alpha = 0.2f;
	}
	else
	{
		Alpha = 0.4f;
	}
	ACharacter* PCharacter = Cast<ACharacter>(GetOwner());
	if(!PCharacter) return;
	
	FRotator PRot = PCon->GetControlRotation();
	FRotator CalRot = UKismetMathLibrary::RLerp(Rot,PRot , Alpha, true);

	FRotator FinalRot = FRotator(PRot.Pitch, CalRot.Yaw, PRot.Roll);
								// Pit, CalRot.Yaw, PRot.Roll
	PCon->SetControlRotation(FinalRot);
	// 타겟팅 시작 후 뷰 스페이스와 관련된 카메라 무빙
	TargetingCameraMoving(PCharacter);
}

void UCameraManagerComponent::InGameLockDown()
{
	if(CurrentCamera->CameraTag != CameraTags::Camera_InGame) return;
	if(!CombatComponent) return;
	if(!CombatComponent->TargetActor) return;
}


void UCameraManagerComponent::TargetingCameraMoving(ACharacter* PCharacter)
{
	if(!PCharacter) return;

	FVector2D ScreenSize;
	int32 x;
	int32 y;
	PCon->GetViewportSize(x,y);

	ScreenSize.X = (float)x;
	ScreenSize.Y = (float)y;

	// 스크린 좌표를 이용한 카메라 움직임
	FVector ActorLocation = FVector(PCharacter->GetActorLocation().X, PCharacter->GetActorLocation().Y, PCharacter->GetActorLocation().Z + 60.f);	
	FVector2D ScreenPosition;	
	FVector2D ScreenCenter(ScreenSize.X/2.f, ScreenSize.Y/2.f);
	
	bool bIsOnScreen = PCon->ProjectWorldLocationToScreen(ActorLocation, ScreenPosition);

	float HalfWidth = 300.f;
	float HalfHeight = 50.f;

	
	//PCon->DeprojectScreenPositionToWorld()
	if(bIsOnScreen)
	{
		bIsInBox =
			((ScreenPosition.X >= ScreenCenter.X - HalfWidth && ScreenPosition.X <= ScreenCenter.X + HalfWidth) &&
			(ScreenPosition.Y >= ScreenCenter.Y - HalfHeight && ScreenPosition.Y <= ScreenCenter.Y + HalfHeight));
		
		// 스크린 좌표의 특정 영역 안에 들어왔어요.
		if(bIsInBox)
		{			
			
		}
		// 영역 밖입니다. 
		else
		{
			
			bLerping = true;
			if(!SetInitTime)
			{
				SetInitTime = true;
				FTimerHandle TimerHandle;
				GetWorld()->GetTimerManager().SetTimer(TimerHandle, this,&ThisClass::InitCameraMovingLerp, 1.f,false, 1.f);
			}
		}
	}
	
	USpringArmComponent* Arm = PCharacter->GetComponentByClass<USpringArmComponent>();
	if(bLerping)
	{
		
		if(Arm)
		{
			FVector CurrentLocation = Arm->GetComponentLocation();
			
			float Distance = FVector::Dist(CurrentLocation, ActorLocation);
			float Alpha = FMath::Clamp(Distance / 140.0f, 0.0f, 1.0f);
			
			// NewLocation 계산
			float Delta = GetWorld()->GetDeltaSeconds();
			FVector NewLocation = FMath::VInterpTo(CurrentLocation, ActorLocation, Delta * 3.f, Alpha);
//
			Arm->SetWorldLocation(NewLocation);
		}
	}
}

void UCameraManagerComponent::InitCameraMovingLerp()
{
	bLerping = false;
	SetInitTime = false;
}

