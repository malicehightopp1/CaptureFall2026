// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "Blueprint/UserWidget.h"
#include "ValueGauge.generated.h"

class UAbilitySystemComponent;

UCLASS()
class UValueGauge : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativePreConstruct() override;

	void ValueUpdated(const struct FOnAttributeChangeData& OnAttributeChangeData);
	void MaxValueUpdated(const struct FOnAttributeChangeData& OnAttributeChangeData);
	void SetAndBindWithAbilitySystemComponent(UAbilitySystemComponent* AbilitySystemComponent, const struct FGameplayAttribute& Attribute, const struct FGameplayAttribute& MaxAttribute);
	
	float CachedValue;
	float CachedMaxValue;
	
	void SetValue(float NewValue, float NewMaxValue);
private:
	UPROPERTY(meta = (Bindwidget)) class UProgressBar* ProgressBar;
	UPROPERTY(meta = (Bindwidget)) class UTextBlock* ValueText;

	UPROPERTY(EditAnywhere, Category = "Value Gauge") FLinearColor BarColor;
};
