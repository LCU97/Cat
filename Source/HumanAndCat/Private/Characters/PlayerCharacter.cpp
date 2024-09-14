// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PlayerCharacter.h"
#include "BlueprintGameplayTagLibrary.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


void APlayerCharacter::GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const
{
	TagContainer = PlayerGameplayTags;
}

void APlayerCharacter::AddGameplayTag(FGameplayTag Tag)
{
	PlayerGameplayTags.AddTag(Tag);
}

void APlayerCharacter::RemoveGameplayTag(FGameplayTag Tag)
{
	PlayerGameplayTags.RemoveTag(Tag);
}

bool APlayerCharacter::GetCurrentGameplayTag(FGameplayTag ParentTag, FGameplayTag& OutTag)
{
	// 원하는 태그의 부모 태그까지 확인하여 플레이어의 태그컨테이너에서 확인합니다.
	if(UBlueprintGameplayTagLibrary::HasTag(PlayerGameplayTags,ParentTag,false))
	{
		TArray<FGameplayTag> GetTags;
		PlayerGameplayTags.GetGameplayTagArray(GetTags);

		for(auto GameplayTag : GetTags)
		{
			// 해당 태그가 플레이어의 태그 배열에서 부모 형식으로라도 가지고 있으면 반환합니다.
			if(GameplayTag.MatchesTag(ParentTag))
			{
				OutTag = GameplayTag;
				return true;
			}
		}
	}
	return false;
}