// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/CAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UCAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	
	
	OwningCharacter = Cast<ACharacter>(TryGetPawnOwner());
	
	if (OwningCharacter)
	{
		OwningCharacterMovementComponent = OwningCharacter->GetCharacterMovement();
	}
}
void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (OwningCharacter)
	{
		Speed = OwningCharacter->GetVelocity().Length(); //getting velocity
		FRotator bodyRotation = OwningCharacter->GetActorRotation(); //gets current rotation
		FRotator bodyRotationDelta = UKismetMathLibrary::NormalizedDeltaRotator(bodyRotation, BodyPrevRotation); //tells the difference in rotation from two rotators
		
		YawSpeed = bodyRotationDelta.Yaw / DeltaSeconds; //calculation for the yaw speed divide he differnece by delta seconds
		SmoothedYawSpeed = UKismetMathLibrary::FInterpTo(SmoothedYawSpeed, YawSpeed, DeltaSeconds, YawSpeedSmoothLerpRate);
		BodyPrevRotation = bodyRotation;
		
	}
	if (OwningCharacterMovementComponent)
	{
		bIsFalling = OwningCharacterMovementComponent->IsFalling(); //ground check
	}
}

