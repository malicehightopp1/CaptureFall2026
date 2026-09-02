// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilitysystem/CAbilitySystemComponent.h"

void UCAbilitySystemComponent::ApplyInitialEffects()
{
	if (GetOwner() || !GetOwner()->HasAuthority()){ return; } //need this guard against hackers
	
	for (const TSubclassOf<UGameplayEffect>& InitialEffectClass : InitialEffects)
	{
		FGameplayEffectSpecHandle EffectSpec = MakeOutgoingSpec(InitialEffectClass, 1, MakeEffectContext());
		ApplyGameplayEffectSpecToSelf(*EffectSpec.Data); //"de-Pointer" to get pointer 
	}
}
