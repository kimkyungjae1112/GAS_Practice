// Fill out your copyright notice in the Description page of Project Settings.


#include "GameAbility/GameplayAbility/GPGA_Interact.h"

UGPGA_Interact::UGPGA_Interact()
{
}

void UGPGA_Interact::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

}
