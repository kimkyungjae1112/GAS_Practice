// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/GPWeaponBase.h"

AGPWeaponBase::AGPWeaponBase()
{
	WeaponMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	SetRootComponent(WeaponMeshComp);
	WeaponMeshComp->SetCollisionProfileName(TEXT("NoCollision"));
}

void AGPWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGPWeaponBase::EnableHitDetection()
{
	bIsHitCheckEnabled = true;
	HitActors.Empty();
}

void AGPWeaponBase::DisableHitDetection()
{
	bIsHitCheckEnabled = false;
}


