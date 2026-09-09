// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "CCharacter.generated.h"

UCLASS()
class ACCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ACCharacter();
	void ServerSideInit();
	void ClientSideInit();

	virtual void PossessedBy(AController* NewController) override;
protected:
	virtual void BeginPlay() override;
 
public:	
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	bool IsLocallyControlledByPlayer() const;
	//-------------------------------------------------------------//
	//				Gameplay abilites 
	//-------------------------------------------------------------//
public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
private:
	UPROPERTY(VisibleDefaultsOnly, Category = "Ability System") class UCAbilitySystemComponent* AbilitySystemComponent;
	UPROPERTY() class UCAttributeSet* AttributeSet;
	
	//----------------------------------------------------------------------------//
	//									UI										  //
	//----------------------------------------------------------------------------//
	
private:
	UPROPERTY(VisibleDefaultsOnly, Category = "UI") class UWidgetComponent* OverheadWidgetComponent;
	void ConfigureOverheadWidgetComponent();
};
