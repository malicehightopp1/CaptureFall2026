// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ACPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	//on possess is only called on the server
	virtual void OnPossess(APawn* NewPawn) override;
	
	//called when client received their pawn on the client machine. not called on dedicated server 
	virtual void AcknowledgePossession(APawn* NewPawn) override;
private:
	UPROPERTY() class ACPlayerCharacter* CPlayerCharacter;
};
