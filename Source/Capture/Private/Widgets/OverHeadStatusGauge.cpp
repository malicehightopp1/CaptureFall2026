// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/OverHeadStatusGauge.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/CAttributeSet.h"
#include "Widgets/ValueGauge.h"

void UOverHeadStatusGauge::ConfigureWithAbilitySystemComponent(class UAbilitySystemComponent* AbilitySystemComponent)
{
	if (AbilitySystemComponent)
	{
		HealthBar->SetAndBindWithAbilitySystemComponent(AbilitySystemComponent, UCAttributeSet::GetHealthAttribute(), UCAttributeSet::GetMaxHealthAttribute());	
		ManaBar->SetAndBindWithAbilitySystemComponent(AbilitySystemComponent, UCAttributeSet::GetManaAttribute(), UCAttributeSet::GetMaxManaAttribute());	
	}
}
