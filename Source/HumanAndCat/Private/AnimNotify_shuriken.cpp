// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_shuriken.h"
#include "BlackEnemy_shuriken.h" 



void UAnimNotify_shuriken::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{

    AActor* Owner = MeshComp->GetOwner();
    FName SocketName = FName(TEXT("shuriken_lSocket"));
    FVector SpawnLocation = MeshComp->GetSocketLocation(SocketName);
    FRotator SpawnRotation = MeshComp->GetSocketRotation(SocketName);


    UWorld* World = Owner->GetWorld();


    if (World)
    {
        //TSubclassOf<AActor> ShurikenClass = ABlackEnemy_shuriken::StaticClass();

       

        World->SpawnActor<ABlackEnemy_shuriken>(ShurikenClass, SpawnLocation, SpawnRotation);
    }
}