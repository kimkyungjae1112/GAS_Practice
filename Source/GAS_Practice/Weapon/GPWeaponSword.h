// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/GPWeaponBase.h"
#include "GPWeaponSword.generated.h"

UCLASS()
class GAS_PRACTICE_API AGPWeaponSword : public AGPWeaponBase
{
	GENERATED_BODY()
	
public:
	AGPWeaponSword();

	virtual void Tick(float DeltaSecond) override;

protected:
	virtual void PerformTrace() override;
};
