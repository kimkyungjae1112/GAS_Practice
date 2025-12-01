// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GPAnimInstance.generated.h"

UCLASS()
class GAS_PRACTICE_API UGPAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UGPAnimInstance();

	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsIdle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsFalling;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsJumping;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ThreshouldSpeed = 3.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ThreshouldJumping = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float GroundSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Velocity;

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class ACharacter> Character;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UCharacterMovementComponent> Movement;

};
