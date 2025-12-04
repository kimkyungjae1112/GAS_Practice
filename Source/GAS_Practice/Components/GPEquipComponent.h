// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GPEquipComponent.generated.h"

class AGPWeaponBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAS_PRACTICE_API UGPEquipComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UGPEquipComponent();

	virtual void BeginPlay() override;

	FORCEINLINE AGPWeaponBase* GetWeapon() const { return Weapon; };

protected:
	/* 임시로 무기를 스폰하기 위한 UClass */
	UPROPERTY(EditAnywhere, Category = "Equip | Weapon")
	TSubclassOf<AGPWeaponBase> WeaponClass;

	UPROPERTY(VisibleAnywhere, Category = "Equip | Weapon")
	TObjectPtr<AGPWeaponBase> Weapon;
};
