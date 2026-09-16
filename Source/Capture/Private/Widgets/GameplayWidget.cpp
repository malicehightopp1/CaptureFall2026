// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/GameplayWidget.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "ValueGauge.h"
#include "AbilitySystem/CAttributeSet.h"

void UGameplayWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	//grabbing the ability system from the owning pawn and returning it
	UAbilitySystemComponent* AbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwningPlayerPawn());

	HealthBar->SetAndBindWithAbilitySystemComponent(AbilitySystemComponent, UCAttributeSet::GetHealthAttribute(), UCAttributeSet::GetMaxHealthAttribute());
	ManaBar->SetAndBindWithAbilitySystemComponent(AbilitySystemComponent, UCAttributeSet::GetManaAttribute(), UCAttributeSet::GetMaxManaAttribute());
}
