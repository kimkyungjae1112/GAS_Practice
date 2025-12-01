// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

struct FGPGameplayTags
{
public:
	static const FGPGameplayTags& Get() { return GameplayTags; };
	static void InitializeNativeGameplayTags();

	// Action 카테고리
	struct FActionTags
	{
		FGameplayTag Attack;
		FGameplayTag Interact;
		FGameplayTag Jump;
	} Action;

	struct FEventTags
	{
		struct FMontageTags
		{
			FGameplayTag EnableCombo;
			FGameplayTag NextSection;
		} Montage;
	} Event;

	// 플레이어 상태 카테고리
	struct FStatusTags
	{
		FGameplayTag Dead;
		FGameplayTag Hit;
		FGameplayTag Attacking;
		FGameplayTag Interacting;
		FGameplayTag Jumping;

		struct FDebuffTags
		{
			FGameplayTag Stun;
			FGameplayTag Freeze;
		} Debuff;

		struct FBuffTags
		{
			FGameplayTag Haste;
			FGameplayTag Shield;
		} Buff;
	} Status;

protected:
	void AddTag(FGameplayTag& OutTag, const ANSICHAR* TagName, const ANSICHAR* TagComment);

private:
	static FGPGameplayTags GameplayTags;
};