// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/MidBossFSM.h"
#include <Kismet/GameplayStatics.h>
#include "Characters/AdventurePlayer.h"
#include "Characters/MidBoss.h"
#include "Characters/Animation/MidBossAnim.h"
#include <Components/CapsuleComponent.h>
#include <NavigationSystem.h>
#include <AIController.h>
#include "Navigation/PathFollowingComponent.h"


UMidBossFSM::UMidBossFSM()
{
}

// Called when the game starts
void UMidBossFSM::BeginPlay()
{
	Super::BeginPlay();

	auto actor = UGameplayStatics::GetActorOfClass(GetWorld(), AAdventurePlayer::StaticClass());
	player = Cast<AAdventurePlayer>(actor);

	me = Cast<AMidBoss>(GetOwner());
	anim = Cast<UMidBossAnim>(me->GetMesh()->GetAnimInstance());

	ai = Cast<AAIController>(me->GetController());
}


// Called every frame
void UMidBossFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FString logMsg = UEnum::GetValueAsString(mState);
	GEngine->AddOnScreenDebugMessage(0, 1, FColor::Cyan, logMsg);
	
	switch(mState)
	{
	case EMidBossState::Idle:
		IdleState();
		break;
	case EMidBossState::Move:
		MoveState();
		break;
	case EMidBossState::Attack:
		AttackState();
		break;
	case EMidBossState::Damage:
		DamageState();
		break;
	case EMidBossState::Die:
		DieState();
		break;
	}
}

void UMidBossFSM::IdleState()
{
	currentTime += GetWorld()->DeltaTimeSeconds;
	if (currentTime > idleDelayTime)	// idle for delay time
	{
		mState = EMidBossState::Move;
		currentTime = 0;
		anim->animState = mState;
		GetRandomPositionInNavMesh(me->GetActorLocation(), 500, randomPos);
	}
}

bool UMidBossFSM::GetRandomPositionInNavMesh(FVector centerLocation, float radius, FVector& dest)
{
	auto ns = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	FNavLocation loc;
	bool result = ns->GetRandomReachablePointInRadius(centerLocation, radius, loc);
	dest = loc.Location;
	return result;
}

void UMidBossFSM::MoveState()
{
	FVector destination = player->GetActorLocation();
	FVector dir = destination - me->GetActorLocation();
	//me->AddMovementInput(dir.GetSafeNormal());
	//ai->MoveToLocation(destination);

	auto ns = UNavigationSystemV1::GetNavigationSystem(GetWorld());

	FPathFindingQuery query;	// query abt how to go there, finding the way
	FAIMoveRequest req;	// struct
	req.SetAcceptanceRadius(3);
	req.SetGoalLocation(destination);
	ai->BuildPathfindingQuery(req, query); 
	FPathFindingResult r = ns->FindPathSync(query);	// reuturns the way

	if (r.Result == ENavigationQueryResult::Success)	// if it can find a way
	{
		ai->MoveToLocation(destination);
	}
	else
	{
		auto result = ai->MoveToLocation(randomPos);

		if (result == EPathFollowingRequestResult::AlreadyAtGoal)
		{
			GetRandomPositionInNavMesh(me->GetActorLocation(), 500, randomPos);
		}
	}
	
	if (dir.Size() < attackRange)
	{
		ai->StopMovement();
		mState = EMidBossState::Attack;
		anim->animState = mState;
		anim->bAttackPlay = true;
		currentTime = attackDelayTime; //  immediately attack
	}
}

void UMidBossFSM::AttackState()
{
	currentTime += GetWorld()->DeltaTimeSeconds;
	if (currentTime > attackDelayTime)
	{
		currentTime = 0;
		anim->bAttackPlay = true;
	}

	FVector distance = player->GetActorLocation() - me->GetActorLocation();
	if (distance.Size() > attackRange)
	{
		mState = EMidBossState::Move;
		anim->animState = mState;
		GetRandomPositionInNavMesh(me->GetActorLocation(), 500, randomPos);
	}
} 

void UMidBossFSM::DamageState()
{
	currentTime += GetWorld()->DeltaTimeSeconds;
	if (currentTime > damageDelayTime)
	{
		mState = EMidBossState::Idle;
		currentTime = 0;
		anim->animState = mState;
	}
}

void UMidBossFSM::DieState()
{
	if (anim->bDieDone == false)
	{
		return;
	}
	FVector P0 = me->GetActorLocation();
	FVector vt = FVector::DownVector * dieSpeed * GetWorld()->DeltaTimeSeconds; 
	FVector P = P0 + vt;
	me->SetActorLocation(P);

	if (P.Z < -200.0f)
	{
		me->Destroy();
	}
}

void UMidBossFSM::OnDamageProcess()
{
	hp--;
	if (hp>0)
	{
		mState = EMidBossState::Damage;

		currentTime = 0;

		int32 index = FMath::RandRange(0, 1);
		FString sectionName = FString::Printf(TEXT("Damage%d"), index);
		anim->PlayDamageAnim(*sectionName);
	}
	else
	{
		mState = EMidBossState::Die;
		me->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		anim->PlayDamageAnim(TEXT("Die"));
	}
	anim->animState = mState;
	ai->StopMovement();
}
