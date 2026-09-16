// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AN_SendGameplayEvent.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"

void UAN_SendGameplayEvent::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	if (!MeshComp->GetOwner())
	{
		return;
	}
	
	//Grabbing the ability system
	const UAbilitySystemComponent* OwnerASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(MeshComp->GetOwner());
	
	if (!OwnerASC)
	{
		return;
	}
	
	//this sends the gameplay event to the mesh owner
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(MeshComp->GetOwner(), EventTag,FGameplayEventData());
}

FString UAN_SendGameplayEvent::GetNotifyName_Implementation() const
{
	return Super::GetNotifyName_Implementation();
	
	
}
