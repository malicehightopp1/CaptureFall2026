// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilitysystem/CGameplayAbility.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "GA_Combo.generated.h"

UCLASS()
class UGA_Combo : public UCGameplayAbility
{
	GENERATED_BODY()
	
public:
	UGA_Combo();
	
	UFUNCTION() void DoDamage(FGameplayEventData Payload);
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;;
	
	UPROPERTY(EditDefaultsOnly, Category = "Damage") TMap<FName, TSubclassOf<class UGameplayEffect>> DamageEffect;
		
	UPROPERTY(EditDefaultsOnly, Category = "Damage") TSubclassOf<UGameplayEffect> DefaultDamageEffect;
	
	TSubclassOf<class UGameplayEffect> GetDamageEffectForcurrentCombo() const;
private:
	UFUNCTION()void HandleComboChange(FGameplayEventData EventData);
	
	UPROPERTY(EditDefaultsOnly, Category = "Animation") UAnimMontage* ComboMontage;
	FName NextComboName;
	
	UFUNCTION() void HandleComboInputPress(float TimeWaited);
	void SetupWaitInputPress();
	
};
