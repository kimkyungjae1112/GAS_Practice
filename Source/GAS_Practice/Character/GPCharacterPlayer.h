// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/GPCharacterBase.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagAssetInterface.h"
#include "GPCharacterPlayer.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UGPInputData;
class UGameplayAbility;
class UAbilitySystemComponent;
class UGPEquipComponent;
struct FInputActionValue;

UCLASS()
class GAS_PRACTICE_API AGPCharacterPlayer 
	: public AGPCharacterBase
	, public IAbilitySystemInterface
	, public IGameplayTagAssetInterface
{
	GENERATED_BODY()
	
public:
	AGPCharacterPlayer();

public:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PostInitializeComponents() override;

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	/* IAbilitySystemInterface 구현 */
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	/* IGameplayTagAssetInterface 구현 */
	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override;

protected:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	void GASInputPressed(int32 InputID);
	void GASInputReleased(int32 InputID);

private:
	void InitAbilityActorInfo();

protected:
	UPROPERTY(EditAnywhere, Category = "GAS | Ability")
	TArray<TSubclassOf<UGameplayAbility>> DefaultAbilities;

	UPROPERTY(EditAnywhere, Category = "GAS | Ability")
	TMap<TSubclassOf<UGameplayAbility>, int32> InputAbilities;

private:
	UPROPERTY(VisibleAnywhere, Category = "Component | Camera")
	TObjectPtr<USpringArmComponent> SpringArmComp;

	UPROPERTY(VisibleAnywhere, Category = "Component | Camera")
	TObjectPtr<UCameraComponent> CameraComp;

	UPROPERTY(VisibleAnywhere, Category = "Component | GAS")
	TObjectPtr<UAbilitySystemComponent> ASComp;

	UPROPERTY(VisibleAnywhere, Category = "Component | Equip")
	TObjectPtr<UGPEquipComponent> EquipComp;

private:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UGPInputData> InputData;
};
