// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GPCharacterBase.h"

AGPCharacterBase::AGPCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -88.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
}

void AGPCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGPCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGPCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

