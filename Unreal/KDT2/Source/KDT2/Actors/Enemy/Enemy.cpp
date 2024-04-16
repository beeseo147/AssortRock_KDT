// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Enemy/Enemy.h"

// Sets default values
AEnemy::AEnemy()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	KDT2FloatingPawnMovement = CreateDefaultSubobject<UKDT2FloatingPawnMovement>(TEXT("MovementComponent"));

	//StatusComponent = CreateDefaultSubobject<UStatusComponent>(StatusComponentName);

	SetRootComponent(BoxComponent);
	SkeletalMeshComponent->SetupAttachment(GetRootComponent());
	SkeletalMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	BoxComponent->SetCollisionProfileName(FCollisionPresetNameTable::Enemy);

}

AEnemy::~AEnemy()
{
}

void AEnemy::SetEnemyData(const FEnemyDataTableRow* InData)
{
	ensure(InData);
	//if (InData == EnemyDataTableRow) { return; }

	EnemyDataTableRow = InData;

	BoxComponent->SetBoxExtent(InData->BoxExtent);

	SkeletalMeshComponent->SetSkeletalMesh(InData->SkeletalMesh);
	SkeletalMeshComponent->SetRelativeTransform(InData->SkeletalMeshTransform);

	if (StatusComponent && !InData->StatusData.IsNull() && InData->StatusData.RowName != NAME_None)
	{
		FStatusDataTableRow* StatusDataTableRow = InData->StatusData.GetRow<FStatusDataTableRow>(TEXT(""));
		StatusComponent->SetStatusData(StatusDataTableRow);
	}
}

float AEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	UE_LOG(LogTemp, Warning, TEXT("Hit Enemy!: %f"), Damage);

	Damage = StatusComponent->ProcessDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	return Damage;
}

void AEnemy::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (DataTableRowHandle.IsNull()) { return; }
	if (DataTableRowHandle.RowName == NAME_None) { return; }
	FEnemyDataTableRow* Data = DataTableRowHandle.GetRow<FEnemyDataTableRow>(TEXT(""));
	SetEnemyData(Data);
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	if (!DataTableRowHandle.IsNull() && DataTableRowHandle.RowName != NAME_None)
	{
		EnemyDataTableRow = DataTableRowHandle.GetRow<FEnemyDataTableRow>(TEXT(""));

		if (!EnemyDataTableRow->StatusData.IsNull() && EnemyDataTableRow->StatusData.RowName != NAME_None)
		{
			FStatusDataTableRow* StatusDataTableRow = EnemyDataTableRow->StatusData.GetRow<FStatusDataTableRow>(TEXT(""));
			StatusComponent = NewObject<UStatusComponent>(this, StatusDataTableRow->StatusComponentClass, TEXT("StatusComponent"));
			StatusComponent->RegisterComponent();
		}

		SetEnemyData(EnemyDataTableRow);
	}
}

void AEnemy::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

