// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CAbilityInputID.generated.h"

//uint8 means unsigned int 8 bit
UENUM(BlueprintType)
enum class ECAbilityInputID : uint8
{
	None UMETA(DisplayName = "None"),
	BasicAttack UMETA(DisplayName = "Basic Attack"),
	Ability1 UMETA(DisplayName = "Ability 1"),
	Ability2 UMETA(DisplayName = "Ability 2"),
	Ability3 UMETA(DisplayName = "Ability 3"),
	Ability4 UMETA(DisplayName = "Ability 4"),
	
	Confirm UMETA(DisplayName = "Confirm"),
	Cancel UMETA(DisplayName = "Cancel")
};