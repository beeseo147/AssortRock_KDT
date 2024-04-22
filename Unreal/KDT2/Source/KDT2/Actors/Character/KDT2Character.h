// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "KDT2Character.generated.h"

USTRUCT()
struct FCharacterDataTableRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Character")
	USkeletalMesh* SkeletalMesh;

	UPROPERTY(EditAnywhere, Category = "Character")
	FTransform SkeletalMeshTransform;

	UPROPERTY(EditAnywhere, Category = "Character")
	TSubclassOf<UAnimInstance> AnimClass;

	//UPROPERTY(EditAnywhere, meta = (RowType = "/Script/KDT2.StatusDataTableRow"))
	//FDataTableRowHandle StatusData;
};

UCLASS()
class KDT2_API AKDT2Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AKDT2Character(const FObjectInitializer& ObjectInitializer);

	virtual void SetData(const FDataTableRowHandle& InDataTableRowHandle);

protected:
	virtual void OnConstruction(const FTransform& Transform) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(EditAnywhere, meta = (RowType = "/Script/KDT2.CharacterDataTableRow"))
	FDataTableRowHandle DataTableRowHandle;
	FCharacterDataTableRow* CharacterDataTableRow = nullptr;

};