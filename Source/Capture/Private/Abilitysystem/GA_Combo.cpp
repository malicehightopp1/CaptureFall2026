// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilitysystem/CAbilitySystemNativeTags.h"
#include "Abilitysystem/GA_Combo.h"

UGA_Combo::UGA_Combo()
{
	AbilityTags.AddTag(TAG_ABILITY_BASICATTACK);
	BlockAbilitiesWithTag.AddTag(TAG_ABILITY_BASICATTACK);
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
	}
}
