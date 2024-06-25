#pragma once
#include "CoreMinimal.h"
#include "LevelSequencePlayer.h"
#include "LevelSequenceActor.h"
#include "StageSubsystem.generated.h"

UENUM(BlueprintType)
enum class EWaveTransitionRule : uint8
{
	Auto,
	KillAllEnemies,
};

USTRUCT()
struct FWaveInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	ULevelSequence* Wave;

	UPROPERTY(EditAnywhere)
	EWaveTransitionRule WaveTransitionRule = EWaveTransitionRule::Auto;
};

UCLASS(BlueprintType)
class UStageDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TArray<FWaveInfo> Waves;
};

UCLASS()
class UStageSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void StartStage(UStageDataAsset* NewStageDataAsset);

protected:
	virtual void Tick(float DeltaTime) override;
	virtual TStatId GetStatId() const override;

protected:
	void StartWave(const uint32 NewWaveIndex);
	void StageFinished();
	bool CanTransitionWave();

protected:
	UFUNCTION()
	void OnWaveFinished();

protected:
	UPROPERTY(Transient)
	UStageDataAsset* StageDataAsset = nullptr;
	UPROPERTY(Transient)
	ALevelSequenceActor* LevelSequencePlayer = nullptr;

	bool bWaveFinish = false;
	uint32 CurrentWaveIndex = 0;
};