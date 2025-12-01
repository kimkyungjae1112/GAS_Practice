// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "GPPlayerState.generated.h"

UCLASS()
class GAS_PRACTICE_API AGPPlayerState 
	: public APlayerState
	, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	AGPPlayerState();

	/* IAbilitySystemInterface Implement */
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	UPROPERTY(VisibleAnywhere, Category = "GAS")
	TObjectPtr<class UAbilitySystemComponent> ASComp;
};
