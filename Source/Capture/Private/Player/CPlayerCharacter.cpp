// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/CPlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "Capture/Capture.h"

ACPlayerCharacter::ACPlayerCharacter()
{
	//Player spring arm
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("Camera Boom");
	CameraBoom->SetupAttachment(GetRootComponent());
	
	//Player camera
	ViewCam = CreateDefaultSubobject<UCameraComponent>("View Cam");
	ViewCam->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	
	CameraBoom->bUsePawnControlRotation = true; //allows pitch to work
	CameraBoom->ProbeChannel = ECC_CameraBoom;
	
	bUseControllerRotationYaw = false; //so the camera rotates around the player not follows
	
	GetCharacterMovement()->bOrientRotationToMovement = true; //rotates body to where your moving towards
	GetCharacterMovement()->RotationRate = FRotator(360.0f);
}

void ACPlayerCharacter::PawnClientRestart()
{
	Super::PawnClientRestart();

	if (UEnhancedInputLocalPlayerSubsystem* EnhancedInputLocalPlayerSubsystem = GetController<APlayerController>()->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
	{
		EnhancedInputLocalPlayerSubsystem->ClearAllMappings();
		EnhancedInputLocalPlayerSubsystem->AddMappingContext(PlayerInputMappingContext, 0);
	}
}

void ACPlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(JumpingAction, ETriggerEvent::Triggered, this, &ACPlayerCharacter::Jump);
		
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACPlayerCharacter::HandlelookInput);
		
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACPlayerCharacter::HandleMoveInput);
		
		for (const TPair<ECAbilityInputID, UInputAction*> InputActionPair : GamePlayAbilityInputActions)
		{
			EnhancedInputComponent->BindAction(InputActionPair.Value, ETriggerEvent::Triggered, this, &ACPlayerCharacter::HandleAbilityInputAction, InputActionPair.Key);
		}
	}
}

void ACPlayerCharacter::HandleAbilityInputAction(const struct FInputActionValue& InputActionValue,ECAbilityInputID InputID)
{
	bool bPressed = InputActionValue.Get<bool>();
	if (bPressed)
	{
		GetAbilitySystemComponent()->AbilityLocalInputPressed((int32)InputID);
	}
	else
	{
		GetAbilitySystemComponent()->AbilityLocalInputReleased((int32)InputID);
	}
}

void ACPlayerCharacter::HandlelookInput(const struct FInputActionValue& InputActionValue) 
{
	FVector2D InputAction = InputActionValue.Get<FVector2D>();
	AddControllerYawInput(InputAction.X);
	AddControllerPitchInput(InputAction.Y);
}

void ACPlayerCharacter::HandleMoveInput(const struct FInputActionValue& InputActionValue)
{
	FVector2D InputAction = InputActionValue.Get<FVector2D>();
	
	InputAction.Normalize();
	AddMovementInput(GetMoveFWDDirection() * InputAction.Y + GetRightDirection() * InputAction.X);
}

FVector ACPlayerCharacter::GetRightDirection() const
{
	return ViewCam->GetRightVector();
}

FVector ACPlayerCharacter::GetLookFWDVector() const
{
	return ViewCam->GetForwardVector();
}

FVector ACPlayerCharacter::GetMoveFWDDirection() const
{
	return FVector::CrossProduct(GetRightDirection(), FVector::UpVector);
}

