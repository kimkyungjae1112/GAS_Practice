// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotifyState_GPHitCheck.h"
#include "Components/GPEquipComponent.h"
#include "Weapon/GPWeaponBase.h"

void UAnimNotifyState_GPHitCheck::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	if (AActor* Owner = MeshComp->GetOwner())
	{
		if (UGPEquipComponent* EquipComp = Owner->GetComponentByClass<UGPEquipComponent>())
		{
			if (AGPWeaponBase* Weapon = EquipComp->GetWeapon())
			{
				Weapon->EnableHitDetection();
			}
		}
	}
}

void UAnimNotifyState_GPHitCheck::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (AActor* Owner = MeshComp->GetOwner())
	{
		if (UGPEquipComponent* EquipComp = Owner->GetComponentByClass<UGPEquipComponent>())
		{
			if (AGPWeaponBase* Weapon = EquipComp->GetWeapon())
			{
				Weapon->DisableHitDetection();
			}
		}
	}
}
