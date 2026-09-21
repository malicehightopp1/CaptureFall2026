// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilitysystem/CGameplayAbility.h"
#include "Kismet//KismetSystemLibrary.h"

TArray<FHitResult> UCGameplayAbility::GetHitResultsFromSweepLocationTargetData(const FGameplayAbilityTargetDataHandle& TargetDataHandle, float SphereSweepRadius, bool bDrawDebug,bool bIgnoreSelf) const
{
	TArray<FHitResult> OutResults;
	TSet<AActor*> HitActors;
	
	for (const TSharedPtr<FGameplayAbilityTargetData>& TargetData : TargetDataHandle.Data)
	{
		//Same idea as the child class
		FVector StartLoc = TargetData->GetOrigin().GetTranslation();
		FVector EndLoc = TargetData->GetEndPoint();
		
		//saying were only looking for this type being the pawn
		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
		
		//array of actors to ignore
		TArray<AActor*> ActorToIgnore;
		if (bIgnoreSelf)
		{
			ActorToIgnore.Add(GetAvatarActorFromActorInfo());
		}
		
		TArray<FHitResult> Results;
		
		//drawing wire sphere
		UKismetSystemLibrary::SphereTraceMultiForObjects(this, StartLoc, EndLoc, SphereSweepRadius, ObjectTypes, false, ActorToIgnore, 
			bDrawDebug ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None, Results, false);
		
		//if we already have the actor
		for (const FHitResult& Result : Results)
		{
			if (HitActors.Contains(Result.GetActor()))
			{
				continue;
			}
			//add if dont have already
			HitActors.Add(Result.GetActor());
			
			OutResults.Add(Result);
		}
		
	}
	return OutResults;
}
