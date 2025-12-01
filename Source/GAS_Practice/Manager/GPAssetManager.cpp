// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/GPAssetManager.h"
#include "GameAbility/Tags/GPTags.h"

void UGPAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	FGPGameplayTags::InitializeNativeGameplayTags();
}
