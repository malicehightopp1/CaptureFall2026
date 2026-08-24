// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/CCharacter.h"
#include "CPlayerCharacter.generated.h"

class UInputAction;
class UInputMappingContext;

UCLASS()
class ACPlayerCharacter : public ACCharacter
{
	GENERATED_BODY()
	
public:
	ACPlayerCharacter();
	
	virtual void PawnClientRestart() override; //called everytime the client reconnects or connects, aka if you join the game it starts your stuff then
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
private:
	
	//Camera setup
	UPROPERTY(VisibleDefaultsOnly, Category = "Camera") class USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleDefaultsOnly, Category = "Camera") class UCameraComponent* ViewCam;
	
	//Inputs
	UPROPERTY(EditDefaultsOnly, Category = "Input") class UInputMappingContext* PlayerInputMappingContext;
	UPROPERTY(EditDefaultsOnly, Category = "Input") class UInputAction* JumpingAction;
	
};
