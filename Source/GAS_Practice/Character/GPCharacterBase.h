// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GPCharacterBase.generated.h"

UCLASS()
class GAS_PRACTICE_API AGPCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AGPCharacterBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
