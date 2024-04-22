// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Character/KDT2Character.h"
#include "Components/KDT2CharacterMovementComponent.h"

// Sets default values
AKDT2Character::AKDT2Character(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UKDT2CharacterMovementComponent>(Super::CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AKDT2Character::SetData(const FDataTableRowHandle& InDataTableRowHandle)
{
	DataTableRowHandle = InDataTableRowHandle;

	if (DataTableRowHandle.IsNull()) { return; }
	if (DataTableRowHandle.RowName == NAME_None) { return; }

	CharacterDataTableRow = DataTableRowHandle.GetRow<FCharacterDataTableRow>(TEXT(""));
	GetMesh()->SetSkeletalMesh(CharacterDataTableRow->SkeletalMesh);
	GetMesh()->SetRelativeTransform(CharacterDataTableRow->SkeletalMeshTransform);
	GetMesh()->SetAnimClass(CharacterDataTableRow->AnimClass);
}

void AKDT2Character::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	SetData(DataTableRowHandle);
}

// Called when the game starts or when spawned
void AKDT2Character::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKDT2Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AKDT2Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

