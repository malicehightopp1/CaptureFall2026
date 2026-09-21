// Fill out your copyright notice in the Description page of Project Settings.

#include "Abilitysystem/GA_Combo.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Abilitysystem/CAbilitySystemNativeTags.h"
#include "Abilities/Tasks/AbilityTask_WaitInputPress.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "GameplayTagsManager.h"
#include "InterchangeResult.h"
#include "SNegativeActionButton.h"
#include "SWarningOrErrorBox.h"

UGA_Combo::UGA_Combo()
{
	SetAssetTags(FGameplayTagContainer(TAG_ABILITY_BASICATTACK));
	BlockAbilitiesWithTag.AddTag(TAG_ABILITY_BASICATTACK);
}

void UGA_Combo::DoDamage(FGameplayEventData Payload)
{
	UE_LOG(LogTemp, Warning, TEXT("Damaging combo"));
	TArray<FHitResult> HitResults = GetHitResultsFromSweepLocationTargetData(Payload.TargetData, 30.0f, true);
	
	for (const FHitResult& HitResult : HitResults)
	{
		TSubclassOf<UGameplayEffect> DamageEffects = GetDamageEffectForcurrentCombo();
		
		FGameplayEffectSpecHandle effectSpecHandle = MakeOutgoingGameplayEffectSpec(DamageEffects, GetAbilityLevel(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo()));
		
		ApplyGameplayEffectSpecToTarget(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), effectSpecHandle, UAbilitySystemBlueprintLibrary::AbilityTargetDataFromActor(HitResult.GetActor()));
	}
	
}

void UGA_Combo::HandleComboChange(FGameplayEventData EventData)
{
	FGameplayTag EventTag = EventData.EventTag;
	
	if (EventTag == TAG_ABILITY_COMBO_CHANGE_END)
	{
		NextComboName = NAME_None;
		UE_LOG(LogTemp, Warning, TEXT("Next combo is none"));

		return;
	}
	
	TArray<FName> TagNames;
	UGameplayTagsManager::Get().SplitGameplayTagFName(EventTag, TagNames);
	NextComboName = TagNames.Last();
	
	UE_LOG(LogTemp, Warning, TEXT("NextComboName: %s"), *(NextComboName.ToString()));
}

void UGA_Combo::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}
	
	UE_LOG(LogTemp,Warning, TEXT("Testing combo ability"));
	
	//if is server or has prediction key they can see the animation being played
	if (HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo)) //this is how you create a task
	{
		UAbilityTask_PlayMontageAndWait* PlayMontageAndWaitTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, ComboMontage);
		
		//listening for all changes with the montage
		PlayMontageAndWaitTask->OnCompleted.AddDynamic(this, &UGA_Combo::K2_EndAbility);
		PlayMontageAndWaitTask->OnCancelled.AddDynamic(this, &UGA_Combo::K2_EndAbility);
		PlayMontageAndWaitTask->OnInterrupted.AddDynamic(this, &UGA_Combo::K2_EndAbility);
		PlayMontageAndWaitTask->OnBlendOut.AddDynamic(this, &UGA_Combo::K2_EndAbility);
		
		PlayMontageAndWaitTask->ReadyForActivation(); //actually plays the task/animation
		
		UAbilityTask_WaitGameplayEvent* WaitComboEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, TAG_ABILITY_COMBO_CHANGE, nullptr, false, false);
		
		WaitComboEvent->EventReceived.AddDynamic(this, &UGA_Combo::HandleComboChange);
		WaitComboEvent->ReadyForActivation();
	}
	SetupWaitInputPress();
	
	if (K2_HasAuthority())
	{
		UAbilityTask_WaitGameplayEvent* WaitDamageEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, TAG_ABILITY_COMBO_DAMAGE, nullptr, false, false);
		WaitDamageEvent->EventReceived.AddDynamic(this, &UGA_Combo::DoDamage);
		WaitDamageEvent->ReadyForActivation();
	}
}

#pragma region Input Handling for combo
void UGA_Combo::HandleComboInputPress(float TimeWaited)
{
	SetupWaitInputPress();
	if (NextComboName == NAME_None)
	{
		return;
	}
	
	if (UAnimInstance* AnimInstance = GetCurrentActorInfo()->GetAnimInstance())
	{
		AnimInstance->Montage_SetNextSection(AnimInstance->Montage_GetCurrentSection(ComboMontage), NextComboName, ComboMontage);
	}
}

void UGA_Combo::SetupWaitInputPress()
{
	UAbilityTask_WaitInputPress* WaitInputPress = UAbilityTask_WaitInputPress::WaitInputPress(this);
	WaitInputPress->OnPress.AddDynamic(this, &UGA_Combo::HandleComboInputPress);
	WaitInputPress->ReadyForActivation();
}

TSubclassOf<class UGameplayEffect> UGA_Combo::GetDamageEffectForcurrentCombo() const
{
	if (UAnimInstance* Owneraniminstance = GetCurrentActorInfo()->GetAnimInstance())
	{
		FName CurrentCombo = Owneraniminstance->Montage_GetCurrentSection(ComboMontage);
		const TSubclassOf<UGameplayEffect>* FoundEffect = DamageEffect.Find(CurrentCombo);
		if (FoundEffect)
		{
			return *FoundEffect;
		}
	}
	return DefaultDamageEffect;
}
#pragma endregion
