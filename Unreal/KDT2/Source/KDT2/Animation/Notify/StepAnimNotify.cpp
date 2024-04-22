// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Notify/StepAnimNotify.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

void UStepAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	AActor* Actor = MeshComp->GetOwner();
	const FVector Start = Actor->GetActorLocation();
	const FVector End = Start - FVector(0., 0., 150.);
	
	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(MeshComp->GetOwner());

	FHitResult HitResult;
	const bool bHit = UKismetSystemLibrary::LineTraceSingle(Actor, Start, End, ETraceTypeQuery::TraceTypeQuery1,
		false, IgnoreActors, EDrawDebugTrace::None, HitResult, true);

	if (!bHit) { return; }
	ensure(HitResult.PhysMaterial.Get());
	switch (HitResult.PhysMaterial->SurfaceType)
	{
	/*case SurfaceType_Default:
		break;*/
	case SurfaceType1: // Water
		Play(MeshComp, FootStepInfo_Water);
		break;
	default:
		Play(MeshComp, FootStepInfo_Default);
		break;
	}
}

void UStepAnimNotify::Play(USkeletalMeshComponent* MeshComp, const FFootStepInfo& InFootStepInfo)
{
	AActor* Actor = MeshComp->GetOwner();
	const FVector ActorLocation = Actor->GetActorLocation();
	const FVector MeshCompLocation = MeshComp->GetComponentLocation();

	if (!InFootStepInfo.Sounds.IsEmpty())
	{
		const int32 SoundNum = InFootStepInfo.Sounds.Num();
		const int32 SoundIndex = FMath::RandRange(0, SoundNum - 1);
		UGameplayStatics::PlaySoundAtLocation(MeshComp, InFootStepInfo.Sounds[SoundIndex],
			MeshCompLocation, InFootStepInfo.VolumeMultiplier);
	}

	if (InFootStepInfo.Particle)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(MeshComp, InFootStepInfo.Particle,
			MeshCompLocation, FRotator::ZeroRotator, InFootStepInfo.ParticleScale);
	}
}
