// Fill out your copyright notice in the Description page of Project Settings.


#include "GameAbility/AbilityTask/GPAT_JumpAndWaitForLanding.h"
#include "GameFramework/Character.h"

UGPAT_JumpAndWaitForLanding::UGPAT_JumpAndWaitForLanding()
{
}

UGPAT_JumpAndWaitForLanding* UGPAT_JumpAndWaitForLanding::CreateTask(UGameplayAbility* OwningAbility)
{
	UGPAT_JumpAndWaitForLanding* NewTask = NewAbilityTask<UGPAT_JumpAndWaitForLanding>(OwningAbility);
	return NewTask;
}

void UGPAT_JumpAndWaitForLanding::Activate()
{
	Super::Activate();

	ACharacter* Character = CastChecked<ACharacter>(GetAvatarActor());
	Character->LandedDelegate.AddDynamic(this, &ThisClass::OnLandedCallback);
	Character->Jump();

	SetWaitingOnAvatar();
}

void UGPAT_JumpAndWaitForLanding::OnDestroy(bool AbilityEnded)
{
	ACharacter* Character = CastChecked<ACharacter>(GetAvatarActor());
	Character->LandedDelegate.RemoveDynamic(this, &ThisClass::OnLandedCallback);

	Super::OnDestroy(AbilityEnded);
}

void UGPAT_JumpAndWaitForLanding::OnLandedCallback(const FHitResult& Hit)
{
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnComplete.Broadcast();
	}
}
