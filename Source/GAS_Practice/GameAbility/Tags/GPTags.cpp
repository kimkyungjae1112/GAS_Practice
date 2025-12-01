// Fill out your copyright notice in the Description page of Project Settings.


#include "GameAbility/Tags/GPTags.h"
#include "GameplayTagsManager.h"

FGPGameplayTags FGPGameplayTags::GameplayTags;

void FGPGameplayTags::InitializeNativeGameplayTags()
{
    GameplayTags.AddTag(GameplayTags.Action.Attack, "Action.Attack", "기본 공격 수행");
    GameplayTags.AddTag(GameplayTags.Action.Interact, "Action.Interact", "사물 상호작용 수행");
    GameplayTags.AddTag(GameplayTags.Action.Jump, "Action.Jump", "점프 수행");

    GameplayTags.AddTag(GameplayTags.Event.Montage.EnableCombo, "Event.Montage.EnableCombo", "콤보 허용");
    GameplayTags.AddTag(GameplayTags.Event.Montage.NextSection, "Event.Montage.NextSection", "다음 콤보 실행");

    GameplayTags.AddTag(GameplayTags.Status.Dead, "Status.Dead", "사망 상태");
    GameplayTags.AddTag(GameplayTags.Status.Hit, "Status.Hit", "피격");
    GameplayTags.AddTag(GameplayTags.Status.Attacking, "Status.Attacking", "공격 중");
    GameplayTags.AddTag(GameplayTags.Status.Interacting, "Status.Interacting", "상호작용 중");
    GameplayTags.AddTag(GameplayTags.Status.Jumping, "Status.Jumping", "점프 중");

    GameplayTags.AddTag(GameplayTags.Status.Debuff.Stun, "Status.Debuff.Stun", "상태이상: 기절");
    GameplayTags.AddTag(GameplayTags.Status.Debuff.Freeze, "Status.Debuff.Freeze", "상태이상: 빙결");

    GameplayTags.AddTag(GameplayTags.Status.Buff.Haste, "Status.Buff.Haste", "버프: 가속");
    GameplayTags.AddTag(GameplayTags.Status.Buff.Shield, "Status.Buff.Shield", "버프: 보호막");
}

void FGPGameplayTags::AddTag(FGameplayTag& OutTag, const ANSICHAR* TagName, const ANSICHAR* TagComment)
{
    OutTag = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName(TagName),
        FString(FString(TagName) + TEXT(" : ") + FString(TagComment))
    );
}
