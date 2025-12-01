// Fill out your copyright notice in the Description page of Project Settings.


#include "GameAbility/GameplayAbility/GPGA_DefaultAttack.h"
#include "GameFramework/Character.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"

UGPGA_DefaultAttack::UGPGA_DefaultAttack()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UGPGA_DefaultAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	// 1. 코스트 및 쿨타임 지불
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	// 2. 대미지 및 공격 효과 적용
	if (DamageEffectClass)
	{
		FGameplayEffectSpecHandle SpecHandle = MakeOutgoingGameplayEffectSpec(DamageEffectClass);
		if (SpecHandle.IsValid())
		{
			ApplyGameplayEffectSpecToOwner(Handle, ActorInfo, ActivationInfo, SpecHandle);
		}
	}

	// 3. TA로 몽타주 재생 및 종료 조건 적용
	UAbilityTask_PlayMontageAndWait* PlayAttackTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, TEXT("PlayAttack"), AttackMontage, 1.f, NAME_None, true);
	if (PlayAttackTask)
	{
		// 정상적으로 다 재생됐을 때
		PlayAttackTask->OnCompleted.AddDynamic(this, &ThisClass::OnMontageEnded);

		// 다른 애니메이션으로 섞여 넘어갈 때
		PlayAttackTask->OnBlendOut.AddDynamic(this, &ThisClass::OnMontageEnded);

		// 피격 등으로 인해 끊겼을 때
		PlayAttackTask->OnInterrupted.AddDynamic(this, &ThisClass::OnMontageEnded);

		// 어빌리티가 취소되었을 때
		PlayAttackTask->OnCancelled.AddDynamic(this, &ThisClass::OnMontageEnded);

		// 태스크 활성화 (실제 재생 시작)
		PlayAttackTask->ReadyForActivation();
	}
	else
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
	}
}

void UGPGA_DefaultAttack::InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputPressed(Handle, ActorInfo, ActivationInfo);

}

void UGPGA_DefaultAttack::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);

}

void UGPGA_DefaultAttack::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

}

void UGPGA_DefaultAttack::OnMontageEnded()
{
	bool bReplicateEndAbility = true;
	bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicateEndAbility, bWasCancelled);
}
