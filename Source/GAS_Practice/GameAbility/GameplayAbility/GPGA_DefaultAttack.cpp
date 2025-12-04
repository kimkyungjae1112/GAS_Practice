// Fill out your copyright notice in the Description page of Project Settings.


#include "GameAbility/GameplayAbility/GPGA_DefaultAttack.h"
#include "GameFramework/Character.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"

UGPGA_DefaultAttack::UGPGA_DefaultAttack()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

	HitEventTag = FGameplayTag::RequestGameplayTag(FName("Event.Combat.Hit"));
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
	/*if (DamageEffectClass)
	{
		FGameplayEffectSpecHandle SpecHandle = MakeOutgoingGameplayEffectSpec(DamageEffectClass);
		if (SpecHandle.IsValid())
		{
			ApplyGameplayEffectSpecToOwner(Handle, ActorInfo, ActivationInfo, SpecHandle);
		}
	}*/

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
		return;
	}

	UAbilityTask_WaitGameplayEvent* WaitEventTask = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(
		this,
		HitEventTag,
		nullptr,
		false,
		false
	);

	/* UAbilityTask_WaitGameplayEvent 이 어빌리티 태스크가 HitEventTag 로 등록된 어떠한 이벤트라도 발생한다면 WaitEventTask->EventReceived 해당 델리게이트를 Broadcast 한다. */
	if (WaitEventTask)
	{
		WaitEventTask->EventReceived.AddDynamic(this, &ThisClass::OnHitReceived);
		WaitEventTask->ReadyForActivation();
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

void UGPGA_DefaultAttack::OnHitReceived(FGameplayEventData Payload)
{
	const AActor* TargetActor = Payload.Target;

	// 타겟이 없거나 유효하지 않으면 리턴
	if (!TargetActor) return;

	// 2. 이펙트 생성 (SpecHandle)
	if (DamageEffectClass)
	{
		// Spec 생성
		FGameplayEffectSpecHandle SpecHandle = MakeOutgoingGameplayEffectSpec(DamageEffectClass, GetAbilityLevel());

		if (SpecHandle.IsValid())
		{
			// 3. 타겟 ASC 가져오기
			// UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent는 안전하게 ASC를 찾아줍니다.
			UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(const_cast<AActor*>(TargetActor));

			if (TargetASC)
			{
				// 4. 타겟 데이터 핸들 생성
				FGameplayAbilityTargetDataHandle TargetDataHandle;
				FGameplayAbilityTargetData_SingleTargetHit* NewTargetData = new FGameplayAbilityTargetData_SingleTargetHit();

				NewTargetData->HitResult.Location = TargetActor->GetActorLocation();
				NewTargetData->HitResult.HitObjectHandle = FActorInstanceHandle(const_cast<AActor*>(TargetActor));
				NewTargetData->HitResult.bBlockingHit = true;

				TargetDataHandle.Add(NewTargetData);

				// 5. [최종 적용] 타겟에게 이펙트 적용
				ApplyGameplayEffectSpecToTarget(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, SpecHandle, TargetDataHandle);
			}
		}
	}
}
