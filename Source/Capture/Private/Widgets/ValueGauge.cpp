// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/ValueGauge.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "GameplayEffectTypes.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UValueGauge::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	ProgressBar->SetFillColorAndOpacity(BarColor);
}

void UValueGauge::ValueUpdated(const struct FOnAttributeChangeData& OnAttributeChangeData)
{
	SetValue(OnAttributeChangeData.NewValue, CachedMaxValue);
}

void UValueGauge::MaxValueUpdated(const struct FOnAttributeChangeData& OnAttributeChangeData)
{
	SetValue(CachedValue, OnAttributeChangeData.NewValue);
}

void UValueGauge::SetAndBindWithAbilitySystemComponent(UAbilitySystemComponent* AbilitySystemComponent, const struct FGameplayAttribute& Attribute, const struct FGameplayAttribute& MaxAttribute)
{
	if (AbilitySystemComponent)
	{
		bool bIsFound = false;
		float Value = AbilitySystemComponent->GetGameplayAttributeValue(Attribute, bIsFound);
		
		if (!bIsFound)
		{
			UE_LOG(LogTemp, Warning, TEXT("Cant find the attribute set: %s"), *(Attribute.GetName()));
			return;
		}
		
		float MaxValue = AbilitySystemComponent->GetGameplayAttributeValue(MaxAttribute, bIsFound);
		if (!bIsFound)
		{
			UE_LOG(LogTemp, Warning, TEXT("Cant find the attribute set: %s"), *(Attribute.GetName()));
		}
		
		//Setting the value that were grabbing from the attribute set
		SetValue(Value, MaxValue);
		
		//Safe approach for time not lining up for exmaple player lag
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute).AddUObject(this, &UValueGauge::ValueUpdated);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MaxAttribute).AddUObject(this, &UValueGauge::MaxValueUpdated);

	}
}

void UValueGauge::SetValue(float NewValue, float NewMaxValue)
{
	CachedValue = NewValue;
	CachedMaxValue = NewMaxValue;
	
	if (NewMaxValue == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Max Value CANNOT be 0"));
		return;
	}
	
	ProgressBar->SetPercent(NewValue/NewMaxValue);
	
	static FNumberFormattingOptions NumberFormattingOptions = FNumberFormattingOptions().SetMaximumFractionalDigits(0);
	
	ValueText->SetText(FText::Format(FTextFormat::FromString("{0}/{1}"), FText::AsNumber(NewValue, &NumberFormattingOptions), FText::AsNumber(NewMaxValue, &NumberFormattingOptions)));
}
