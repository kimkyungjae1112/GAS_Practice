// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/GPPlayerState.h"
#include "AbilitySystemComponent.h"

AGPPlayerState::AGPPlayerState()
{
	ASComp = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("Ability System Component"));
	ASComp->SetIsReplicated(true);
}

UAbilitySystemComponent* AGPPlayerState::GetAbilitySystemComponent() const
{
	return ASComp;
}
