// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GPGA_Interact.generated.h"

UCLASS()
class GAS_PRACTICE_API UGPGA_Interact : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UGPGA_Interact();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Interaction")
	float InteractionRange = 400.f;
};
