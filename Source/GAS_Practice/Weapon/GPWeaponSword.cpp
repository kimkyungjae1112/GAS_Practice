// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/GPWeaponSword.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Engine/DamageEvents.h"

AGPWeaponSword::AGPWeaponSword()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AGPWeaponSword::Tick(float DeltaSecond)
{
	Super::Tick(DeltaSecond);

	if (bIsHitCheckEnabled)
	{
		PerformTrace();
	}
}

void AGPWeaponSword::PerformTrace()
{
	FVector Start = WeaponMeshComp->GetSocketLocation(SocketStartName);
	FVector End = WeaponMeshComp->GetSocketLocation(SocketEndName);

	TArray<FHitResult> HitResults;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	bool bHit = GetWorld()->SweepMultiByChannel(
		HitResults,
		Start,
		End,
		FQuat::Identity,
		ECC_Pawn,
		FCollisionShape::MakeSphere(CollisionSphereRadius),
		Params
	);

	if (bHit)
	{
		for (const FHitResult& Hit : HitResults)
		{
			AActor* HitActor = Hit.GetActor();
			check(IsValid(HitActor));
			
			if (!HitActors.Contains(HitActor))
			{
				HitActors.Add(HitActor);

				FGameplayEventData Payload;
				Payload.EventTag = HitEventTag;
				Payload.Instigator = GetOwner();
				Payload.Target = HitActor;

				UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwner(), HitEventTag, Payload);
			}
		}
	}
}
