// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/GPEquipComponent.h"
#include "Weapon/GPWeaponBase.h"
#include "GameFramework/Character.h"

UGPEquipComponent::UGPEquipComponent()
{

}

void UGPEquipComponent::BeginPlay()
{
	Super::BeginPlay();

	Weapon = GetWorld()->SpawnActor<AGPWeaponBase>(WeaponClass, GetOwner()->GetTransform());

	if (ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner()))
	{
		if (USkeletalMeshComponent* CharacterMesh = OwnerCharacter->GetMesh())
		{
			Weapon->AttachToComponent(CharacterMesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("hand_rSocket"));
		}
	}
}
