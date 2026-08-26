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
	
	//----------------------------------------------------------------------------//
	//									Functions								  //
	//----------------------------------------------------------------------------//
	virtual void PawnClientRestart() override; //called everytime the client reconnects or connects, aka if you join the game it starts your stuff then
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	

	//Camera setup
	UPROPERTY(VisibleDefaultsOnly, Category = "Camera") class USpringArmComponent* CameraBoom;
	
	UPROPERTY(VisibleDefaultsOnly, Category = "Camera") class UCameraComponent* ViewCam;
	
	//----------------------------------------------------------------------------//
	//									input									  //
	//----------------------------------------------------------------------------//
private:
	void HandlelookInput(const struct FInputActionValue& InputActionValue); //no need to copy just need the reference and read the variable **if no '&' its a copy not a reference**
	void HandleMoveInput(const struct FInputActionValue& InputActionValue);

	UPROPERTY(EditDefaultsOnly, Category = "Input") class UInputMappingContext* PlayerInputMappingContext;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input") class UInputAction* JumpingAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input") class UInputAction* LookAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input") class UInputAction* MoveAction;
	
	
};
