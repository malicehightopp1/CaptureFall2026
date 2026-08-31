// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class UCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativeInitializeAnimation() override;
	
	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe)) FORCEINLINE bool IsMoving() const {return Speed > 0;} //simplfies returning speed
	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe)) FORCEINLINE bool IsNotMoving() const {return Speed == 0;}
	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe)) FORCEINLINE bool IsOnGround() const {return !bIsFalling;}
	
	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe)) FORCEINLINE float GetLookYawOffset() const {return LookRotationOffset.Yaw; }
	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe)) FORCEINLINE float GetLookPitchOffset() const {return LookRotationOffset.Pitch; }

private:
	UPROPERTY() class ACharacter* OwningCharacter;
	UPROPERTY() class UCharacterMovementComponent* OwningCharacterMovementComponent;
	
	UPROPERTY(BlueprintReadOnly, meta =(AllowPrivateAccess)) float Speed; //for character running
	UPROPERTY(BlueprintReadOnly, meta =(AllowPrivateAccess)) bool bIsFalling; //for character jumping
	UPROPERTY(BlueprintReadOnly, meta =(AllowPrivateAccess)) float YawSpeed; //for character leaning
	
	UPROPERTY(BlueprintReadOnly, meta =(AllowPrivateAccess)) float SmoothedYawSpeed; //for character leaning
	
	UPROPERTY(EditDefaultsOnly, Category = "Animation") float YawSpeedSmoothLerpRate = 2.f;
	
	FRotator BodyPrevRotation; //grabbing the players previous yaw 
	
	//Aim offset 
	UPROPERTY() FRotator LookRotationOffset;
	
};
