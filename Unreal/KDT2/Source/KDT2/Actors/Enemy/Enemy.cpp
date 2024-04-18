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

	PaperBurnEffectTimelineComponent = CreateDefaultSubobject<UTimelineComponent>(TEXT("PaperBurnEffectTimelineComponent"));
	{
		static ConstructorHelpers::FObjectFinder<UCurveFloat> ObjectFinder(TEXT("/Script/Engine.CurveFloat'/Game/KDT2/BluePrint/Effect/Curve_ParperBurnEffect.Curve_ParperBurnEffect'"));
		ensure(ObjectFinder.Object);

		FOnTimelineFloat Delegate;
		Delegate.BindUFunction(this, TEXT("OnPaperBurnEffect"));

		PaperBurnEffectTimelineComponent->AddInterpFloat(ObjectFinder.Object, Delegate);
		FScriptDelegate FinishedDelegate;
		FinishedDelegate.BindUFunction(this, TEXT("OnPaperBurnEffectEnd"));
		PaperBurnEffectTimelineComponent->SetTimelineFinishedFunc(FOnTimelineEvent(FinishedDelegate));
		PaperBurnEffectTimelineComponent->SetPlayRate(0.5f);
	}

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

	//if (SkeletalMeshComponent->GetSkeletalMeshAsset() != InData->SkeletalMesh)
	{
		SkeletalMeshComponent->SetSkeletalMesh(InData->SkeletalMesh);
		const int32 MaterialNum = SkeletalMeshComponent->GetSkinnedAsset()->GetMaterials().Num();
		for (int32 i = 0; i < MaterialNum; ++i)
		{
			SkeletalMeshComponent->CreateDynamicMaterialInstance(i);
		}
	}

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

	if (StatusComponent->HP <= 0.f)
	{
		SetActorEnableCollision(false);
		PaperBurnEffectTimelineComponent->PlayFromStart();
	}

	return Damage;
}
void AEnemy::OnPaperBurnEffect(float InPower)
{
	const int32 MaterialNum = SkeletalMeshComponent->GetSkinnedAsset()->GetMaterials().Num();
	for (int32 i = 0; i < MaterialNum; ++i)
	{
		UMaterialInstanceDynamic* MID = Cast<UMaterialInstanceDynamic>(SkeletalMeshComponent->GetMaterial(i));
		if (MID)
		{
			MID->SetScalarParameterValue(TEXT("MF_PostEffect_PaperBurn"), InPower);
		}
		else
		{
			ensure(false);
		}
	}
}

void AEnemy::OnPaperBurnEffectEnd()
{
	Destroy();
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

