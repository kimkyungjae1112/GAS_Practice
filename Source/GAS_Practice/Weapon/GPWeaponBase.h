// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagContainer.h"
#include "GPWeaponBase.generated.h"

UCLASS()
class GAS_PRACTICE_API AGPWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AGPWeaponBase();

	virtual void BeginPlay() override;

	void EnableHitDetection();
	void DisableHitDetection();

protected:
	virtual void PerformTrace() {};

protected:
	UPROPERTY(EditAnywhere, Category = "Mesh")
	TObjectPtr<UStaticMeshComponent> WeaponMeshComp;

	UPROPERTY(EditAnywhere, Category = "Socket")
	FName SocketStartName;

	UPROPERTY(EditAnywhere, Category = "Socket")
	FName SocketEndName;

	UPROPERTY(EditAnywhere, Category = "GAS")
	FGameplayTag HitEventTag;

	UPROPERTY(EditAnywhere, Category = "Stat")
	float CollisionSphereRadius = 20.f;

	bool bIsHitCheckEnabled = false;

	UPROPERTY()
	TArray<AActor*> HitActors;


};
