#include "StageSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "Actors/Spawner/SplineEnemySpawner.h"
#include "Actors/Enemy/Enemy.h"

void UStageSubsystem::StartStage(UStageDataAsset* NewStageDataAsset)
{
	if (!NewStageDataAsset)
	{
		ensure(false);
		return;
	}

	if (NewStageDataAsset->Waves.IsEmpty())
	{
		ensure(false);
		return;
	}

	if (IsValid(LevelSequencePlayer))
	{
		LevelSequencePlayer->Destroy();
		ensure(false);
	}

	StageDataAsset = NewStageDataAsset;

	LevelSequencePlayer = GetWorld()->SpawnActor<ALevelSequenceActor>();
	StartWave(0);
}

void UStageSubsystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsValid(StageDataAsset)) { return; }
	if (!IsValid(LevelSequencePlayer)) { return; }

	if (!CanTransitionWave()) { return; }

	const uint32 NextWaveIndex = CurrentWaveIndex + 1;
	StartWave(NextWaveIndex);
}

TStatId UStageSubsystem::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UStageSubsystem, STATGROUP_Tickables);
}

void UStageSubsystem::StartWave(const uint32 NewWaveIndex)
{
	if ((uint32)StageDataAsset->Waves.Num() <= NewWaveIndex)
	{
		//check(false);
		StageFinished();
		return;
	}

	bWaveFinish = false;
	CurrentWaveIndex = NewWaveIndex;
	const FWaveInfo& WaveInfo = StageDataAsset->Waves[CurrentWaveIndex];
	LevelSequencePlayer->SetSequence(WaveInfo.Wave);

	if (!LevelSequencePlayer->GetSequencePlayer()->OnFinished.IsBound())
	{
		LevelSequencePlayer->GetSequencePlayer()->OnFinished.AddDynamic(this, &ThisClass::OnWaveFinished);
	}
	LevelSequencePlayer->GetSequencePlayer()->Play();
}

void UStageSubsystem::StageFinished()
{
	LevelSequencePlayer->Destroy();
	StageDataAsset = nullptr;
}

bool UStageSubsystem::CanTransitionWave()
{
	if (!bWaveFinish) { return false; }

	const EWaveTransitionRule WaveTransitionRule = StageDataAsset->Waves[CurrentWaveIndex].WaveTransitionRule;
	switch (WaveTransitionRule)
	{
	case EWaveTransitionRule::Auto:
		return true;
	case EWaveTransitionRule::KillAllEnemies:
	{
		AActor* FindSpawner = UGameplayStatics::GetActorOfClass(LevelSequencePlayer, ASplineEnemySpawner::StaticClass());
		if (FindSpawner)
		{
			return false;
		}

		AActor* FindEnemy = UGameplayStatics::GetActorOfClass(LevelSequencePlayer, AEnemy::StaticClass());
		if (FindEnemy)
		{
			return false;
		}
		return true;
	}
	}

	return false;
}

void UStageSubsystem::OnWaveFinished()
{
	bWaveFinish = true;
}
