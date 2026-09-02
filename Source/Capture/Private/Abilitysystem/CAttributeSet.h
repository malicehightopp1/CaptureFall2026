// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "CAttributeSet.generated.h"


UCLASS()
class UCAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	//for fine-tuning the behavior of replicating of sending the information to the client
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
private:
	UPROPERTY(ReplicatedUsing = OnRep_Health) FGameplayAttributeData Health; 
	
	//Replicated using is the function name that sends the information to the client *REQUIRED*
	UPROPERTY(ReplicatedUsing = OnRep_MaxHealth) FGameplayAttributeData MaxHealth;
	
	UPROPERTY(ReplicatedUsing = OnRep_Mana) FGameplayAttributeData Mana; 
	
	//Replicated using is the function name that sends the information to the client *REQUIRED*
	UPROPERTY(ReplicatedUsing = OnRep_MaxMana) FGameplayAttributeData MaxMana;
	
	UFUNCTION() void OnRep_MaxHealth(const FGameplayAttributeData& OldValue);//for updating and telling the client that a value has changed

	UFUNCTION() void OnRep_Health(const FGameplayAttributeData& OldValue);//for updating and telling the client that a value has changed

	UFUNCTION() void OnRep_MaxMana(const FGameplayAttributeData& OldValue);//for updating and telling the client that a value has changed

	UFUNCTION() void OnRep_Mana(const FGameplayAttributeData& OldValue);//for updating and telling the client that a value has changed
};
