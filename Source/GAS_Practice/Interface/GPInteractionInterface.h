// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GPInteractionInterface.generated.h"

UINTERFACE(MinimalAPI)
class UGPInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

class GAS_PRACTICE_API IGPInteractionInterface
{
	GENERATED_BODY()

public:
	virtual void Interact(APawn* InstigatorPawn) = 0;
};
