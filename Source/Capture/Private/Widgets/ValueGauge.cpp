// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/ValueGauge.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UValueGauge::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	ProgressBar->SetFillColorAndOpacity(BarColor);
}

void UValueGauge::SetValue(float NewValue, float NewMaxValue)
{
	if (NewMaxValue == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Max Value CANNOT be 0"));
		return;
	}
	
	ProgressBar->SetPercent(NewValue/NewMaxValue);
	
	static FNumberFormattingOptions NumberFormattingOptions = FNumberFormattingOptions().SetMaximumFractionalDigits(0);
	
	ValueText->SetText(FText::Format(FTextFormat::FromString("{0}/{1}"), FText::AsNumber(NewValue, &NumberFormattingOptions), FText::AsNumber(NewMaxValue, &NumberFormattingOptions)));
}
