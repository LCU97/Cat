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

	ACharacter* PCharacter = Cast<ACharacter>(GetOwner());
	if(!PCharacter) return;
	
	
	if(bIsTarget)
	{
		InGameLockOn();
	}

	// UltiLerpDuration 이 궁극기 애니메이션 시작 시 특정 Duration 을 받아 0 보다 커지게 됩니다.
	if(UltiLerpDuration > 0.0f && CurrentCamera == UltimateCamera)
	{
		UltiMoving();
		FVector Loc = PCharacter->GetMesh()->GetComponentLocation();
		Loc.Z += 80.f;
		FRotator Rot = UKismetMathLibrary::FindLookAtRotation(UltimateCamera->GetComponentLocation(),Loc );
		UltimateCamera->SetWorldRotation(Rot);
	}
}

void UCameraManagerComponent::InitCameraManager(UBaseCameraComponent* InGame, UBaseCameraComponent* Ultimate)
{
	// 시작 시 카메라매니저 클래스를 초기화합니다.
	InGameCamera = InGame;
	UltimateCamera = Ultimate;
	CurrentCamera = InGameCamera;
	
	ACharacter* PCharacter = Cast<ACharacter>(GetOwner());
	if(!PCharacter) return;	
	AController* PController = PCharacter->GetController();
	if(!PController) return;
	APlayerController* PlayerCon = Cast<APlayerController>(PController);
	if(!PlayerCon) return;

	// 컨트롤러를 캐싱하여 접근 속도를 더 빠르게 합니다.
	PCon = PlayerCon;
		
}

void UCameraManagerComponent::ChangeUltiCamera(float Duration)
{
	// NotifyState Begin에서 Duration 을 받고 사용 카메라를 변환합니다.
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
	// NotifyState End 에서 사용 카메라를 변환합니다.
	if(InGameCamera && UltimateCamera)
	{
		InGameCamera->SetActive(true);
		UltimateCamera->SetActive(false);
		PCon->SetViewTargetWithBlend(GetOwner(), 1.f, EViewTargetBlendFunction::VTBlend_Cubic);
		CurrentCamera = InGameCamera;
		UltiLerpDuration = -1;
	}
}

void UCameraManagerComponent::UltiMoving()
{
	// 궁극기 기술 사용 시 카메라의 위치를 변경 합니다.
	ACharacter* PCharacter = Cast<ACharacter>(GetOwner());
	
	FVector OwnerLocation = PCharacter->GetMesh()->GetSocketLocation(FName("RootMotionSocket"));
	FTransform SocketTransform = PCharacter->GetMesh()->GetSocketTransform(FName("RootMotionSocket"));
	
	OwnerLocation.Z += 100.f;
	
	FVector OwnerForWardVec = GetOwner()->GetActorForwardVector();	
	FVector OwnerRightVec = SocketTransform.GetRotation().GetRightVector();
	
	FVector NewLocation = FVector((OwnerLocation.X - OwnerForWardVec.X * 400.f),(OwnerLocation.Y - OwnerForWardVec.Y * 400.f), OwnerLocation.Z);

	UltimateCamera->SetWorldLocation(NewLocation);
}


void UCameraManagerComponent::InGameLockOn()
{
	if(CurrentCamera->CameraTag != CameraTags::Camera_InGame) return;
	if(!CombatComponent) return;
	if(!CombatComponent->GetTargetActor()) bIsTarget = false;
	
	FVector TargetLocation = CombatComponent->GetTargetActor()->GetActorLocation();	
	FRotator Rot = UKismetMathLibrary::FindLookAtRotation(GetOwner()->GetActorLocation(), TargetLocation);	
	float Dis = FVector::Distance( TargetLocation,GetOwner()->GetActorLocation());
	float Alpha;
	
	 // 캐릭터와 타겟액터의 거리에 따라 회전 보간 값을 변경합니다.	
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
	
	// 캐릭터가 타겟액터를 바라보는 회전값과 컨트롤러의 회전 값을 보간합니다.
	FRotator CalRot = UKismetMathLibrary::RLerp(Rot,PRot , Alpha, true);
	FRotator FinalRot = FRotator(PRot.Pitch, CalRot.Yaw, PRot.Roll);	
	// 컨트롤러가 타겟액터를 바라보도록 만듭니다.
	PCon->SetControlRotation(FinalRot);
	// 타겟팅 시작 후 뷰 스페이스와 관련된 카메라 무빙
	TargetingCameraMoving(PCharacter);
}

void UCameraManagerComponent::InGameLockDown()
{
	if(CurrentCamera->CameraTag != CameraTags::Camera_InGame) return;
	if(!CombatComponent) return;
	if(!CombatComponent->GetTargetActor()) return;
}


void UCameraManagerComponent::TargetingCameraMoving(ACharacter* PCharacter)
{
	if(!PCharacter) return;

	FVector2D ScreenSize;
	int32 x;
	int32 y;
	// 뷰포트의 사이즈를 받아옵니다.
	PCon->GetViewportSize(x,y);

	ScreenSize.X = (float)x;
	ScreenSize.Y = (float)y;

	// 스크린 좌표를 이용한 카메라 움직임
	FVector ActorLocation = FVector(PCharacter->GetActorLocation().X, PCharacter->GetActorLocation().Y, PCharacter->GetActorLocation().Z + 60.f);	
	FVector2D ScreenPosition;	
	FVector2D ScreenCenter(ScreenSize.X/2.f, ScreenSize.Y/2.f);

	// 캐릭터 WolrdSpace 좌표를 ViewSpace 좌표로 변환합니다.
	bool bIsOnScreen = PCon->ProjectWorldLocationToScreen(ActorLocation, ScreenPosition);
	float HalfWidth = 300.f;
	float HalfHeight = 50.f;
	
	if(bIsOnScreen)
	{
		// 뷰포트의 중앙 위치를 기준으로 특정 범위 내에 캐릭터가 존재하는지 확인합니다.
		bIsInBox =
			((ScreenPosition.X >= ScreenCenter.X - HalfWidth && ScreenPosition.X <= ScreenCenter.X + HalfWidth) &&
			(ScreenPosition.Y >= ScreenCenter.Y - HalfHeight && ScreenPosition.Y <= ScreenCenter.Y + HalfHeight));
		
		// 스크린 좌표의 특정 영역 안에 들어왔어요.
		if(bIsInBox)
		{			
			// 특정 영역 안에 있으므로 Camera 는 움직이 않습니다. 회전만 컨트롤러를 따라합니다.
		}
		// 영역 밖입니다. 
		else
		{
			
			bLerping = true;
			if(!SetInitTime)
			{
				SetInitTime = true;
				FTimerHandle TimerHandle;
				// 특정 영역 밖에 있으니 카메라는 캐릭터를 따라갑니다. 이때 이 따라가는 시간을 1초로 제한합니다. 만약 계속 밖이라면 1초 마다 계속 다시 Lerp 를 시작합니다.
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
			// 캐릭터의 위치와 스프링암의 위치를 거리로 계산하고 특정 거리를 기준(140.0f)으로 보간 값을 설정합니다.
			float Distance = FVector::Dist(CurrentLocation, ActorLocation);
			float Alpha = FMath::Clamp(Distance / 140.0f, 0.0f, 1.0f);
			
			// NewLocation 계산
			float Delta = GetWorld()->GetDeltaSeconds();
			FVector NewLocation = FMath::VInterpTo(CurrentLocation, ActorLocation, Delta * 3.f, Alpha);
//			// 보간에 따른 새 좌표로 스프링암을 움직입니다.
			Arm->SetWorldLocation(NewLocation);
		}
	}
}

void UCameraManagerComponent::InitCameraMovingLerp()
{
	bLerping = false;
	SetInitTime = false;
}

