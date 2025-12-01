// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/GPAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UGPAnimInstance::UGPAnimInstance()
{
}

void UGPAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Character = Cast<ACharacter>(GetOwningActor());
	if (Character)
	{
		Movement = Character->GetCharacterMovement();
	}
}

void UGPAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Movement)
	{
		Velocity = Movement->Velocity;
		GroundSpeed = Velocity.Size2D();
		bIsIdle = GroundSpeed < ThreshouldSpeed && Movement->GetCurrentAcceleration() == FVector::ZeroVector;
		bIsFalling = Movement->IsFalling();
		bIsJumping = bIsFalling && Velocity.Z > ThreshouldJumping;
	}
}
