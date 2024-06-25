// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Enemy/Enemy.h"
#include "Engine/SkinnedAssetCommon.h"
#include "UI/StatusBarUserWidget.h"
#include "Actors/Weapon/Weapon.h"
#include "PaperSprite.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	PaperSpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("PaperSpriteComponent"));
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	KDT2FloatingPawnMovement = CreateDefaultSubobject<UKDT2FloatingPawnMovement>(TEXT("MovementComponent"));
	
	WeaponChildActorComponent = CreateDefaultSubobject<UChildActorComponent>(TEXT("WeaponChildActorComponent"));
	WeaponChildActorComponent->SetChildActorClass(AWeapon::StaticClass());

	StatusWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("StatusUI"));
	{
		static ConstructorHelpers::FClassFinder<UUserWidget>FindClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/KDT2/Blueprint/Enemy/UI/UI_EnemyStatus.UI_EnemyStatus_C'"));
		ensure(FindClass.Class);
		StatusWidget->SetWidgetClass(FindClass.Class);
		StatusWidget->SetWidgetSpace(EWidgetSpace::Screen);
		StatusWidget->SetDrawSize(FVector2D(200., 36.));
		StatusWidget->SetVisibility(false);
	}

	PaperBurnEffectTimelineComponent = CreateDefaultSubobject<UTimelineComponent>(TEXT("PaperBurnEffectTimelineComponent"));
	{
		static ConstructorHelpers::FObjectFinder<UCurveFloat> ObjectFinder(TEXT("/Script/Engine.CurveFloat'/Game/KDT2/Blueprint/Effect/Curve_PaperBurnEffect.Curve_PaperBurnEffect'"));
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
	WeaponChildActorComponent->SetupAttachment(GetRootComponent());
	PaperSpriteComponent->SetVisibleInSceneCaptureOnly(true);
	PaperSpriteComponent->SetupAttachment(GetRootComponent());
	PaperSpriteComponent->SetRelativeLocation(FVector(0., 0., 240.0));
	PaperSpriteComponent->SetRelativeRotation(FRotator(0., 90.0, -90.0));

	{
		static ConstructorHelpers::FObjectFinder<UPaperSprite> Asset(TEXT("/Script/Paper2D.PaperSprite'/Game/KDT2/Blueprint/RPG/UI/Enemy_Sprite.Enemy_Sprite'"));
		ensure(Asset.Object);
		PaperSpriteComponent->SetSprite(Asset.Object);
	}

	SkeletalMeshComponent->SetupAttachment(GetRootComponent());
	SkeletalMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	StatusWidget->SetRelativeRotation(FRotator(0., 90., 0.));
	StatusWidget->SetupAttachment(SkeletalMeshComponent);

	BoxComponent->SetCollisionProfileName(FCollisionPresetNameTable::Enemy);
	BoxComponent->SetCanEverAffectNavigation(false);

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

AEnemy::~AEnemy()
{
}

void AEnemy::SetEnemyData(const FDataTableRowHandle& InDataTableRowHandle)
{
	DataTableRowHandle = InDataTableRowHandle;
	if (DataTableRowHandle.IsNull()) { return; }
	if (DataTableRowHandle.RowName == NAME_None) { return; }
	EnemyDataTableRow = DataTableRowHandle.GetRow<FEnemyDataTableRow>(TEXT(""));
	SetEnemyData(EnemyDataTableRow);
}

void AEnemy::SetEnemyData(const FEnemyDataTableRow* InData)
{
	ensure(InData);
	if (!InData) { return; }
	//if (InData == EnemyDataTableRow) { return; }

	EnemyDataTableRow = InData;

	BoxComponent->SetBoxExtent(InData->BoxExtent);
	StatusWidget->SetRelativeLocation(FVector(0., 0., InData->BoxExtent.Z * 2.1));

	//if (SkeletalMeshComponent->GetSkeletalMeshAsset() != InData->SkeletalMesh)
	{
		SkeletalMeshComponent->SetSkeletalMesh(InData->SkeletalMesh);
		SkeletalMeshComponent->SetAnimClass(InData->AnimClass);
		const TArray<FSkeletalMaterial>& SkeletalMaterials = SkeletalMeshComponent->GetSkinnedAsset()->GetMaterials();
		const int32 MaterialNum = SkeletalMaterials.Num();
		for (int32 i = 0; i < MaterialNum; ++i)
		{
			SkeletalMeshComponent->CreateDynamicMaterialInstance(i, SkeletalMaterials[i].MaterialInterface);
		}
	}

	SkeletalMeshComponent->SetRelativeTransform(InData->SkeletalMeshTransform);

	if (StatusComponent && !InData->StatusData.IsNull() && InData->StatusData.RowName != NAME_None)
	{
		FStatusDataTableRow* StatusDataTableRow = InData->StatusData.GetRow<FStatusDataTableRow>(TEXT(""));
		
		KDT2FloatingPawnMovement->MaxSpeed = StatusDataTableRow->Speed;
		StatusComponent->SetStatusData(StatusDataTableRow);
	}

	AActor* WeaponActor = WeaponChildActorComponent->GetChildActor();
	if (IsValid(WeaponActor))
	{
		AWeapon* Weapon = Cast<AWeapon>(WeaponActor);
		Weapon->SetOwner(this);
		Weapon->SetActorRelativeTransform(InData->SkeletalMeshTransform);
		if (!InData->WeaponData.IsNull() &&
			InData->WeaponData.RowName != NAME_None)
		{
			Weapon->SetData(InData->WeaponData);
		}
	}
}

float AEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	UE_LOG(LogTemp, Warning, TEXT("Hit Enemy!: %f"), Damage);

	Damage = StatusComponent->ProcessDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	StatusWidget->SetVisibility(true);
	UUserWidget* StatusUserWidget = StatusWidget->GetWidget();
	if (StatusUserWidget)
	{
		const float MaxHP = StatusComponent->StatusDataTableRow->HP;
		UStatusBarUserWidget* EnemyStatusUserWidget = Cast<UStatusBarUserWidget>(StatusUserWidget);
		ensure(EnemyStatusUserWidget);

		EnemyStatusUserWidget->SetHP(StatusComponent->HP, MaxHP);
	}

	if (StatusComponent->HP <= 0.f)
	{
		SetActorEnableCollision(false);
		GetController()->StopMovement();
		GetController()->UnPossess();

		AActor* WeaponActor = WeaponChildActorComponent->GetChildActor();
		if (IsValid(WeaponActor))
		{
			Cast<AWeapon>(WeaponActor)->SetDie();
		}

		PaperBurnEffectTimelineComponent->PlayFromStart();
	}
	else
	{
		AActor* WeaponActor = WeaponChildActorComponent->GetChildActor();
		if (IsValid(WeaponActor))
		{
			Cast<AWeapon>(WeaponActor)->SetDamaged();
		}
	}

	return Damage;
}

void AEnemy::OnPaperBurnEffect(float InPower)
{
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

	// AttachedActors StaticMeshComponet PaperBurn
	{
		TArray<AActor*> AttachedActors;
		GetAttachedActors(AttachedActors);

		for (AActor* It : AttachedActors)
		{
			TArray<UStaticMeshComponent*> ResultStaticMeshComponents;
			It->GetComponents(UStaticMeshComponent::StaticClass(), ResultStaticMeshComponents);

			for (UStaticMeshComponent* StaticMeshComponent : ResultStaticMeshComponents)
			{
				const int32 MaterialNum = StaticMeshComponent->GetStaticMesh()->GetStaticMaterials().Num();
				for (int32 i = 0; i < MaterialNum; ++i)
				{
					UMaterialInterface* Material =StaticMeshComponent->GetMaterial(i);
					UMaterialInstanceDynamic* MID = Cast<UMaterialInstanceDynamic>(Material);
					if (MID)
					{
						MID->SetScalarParameterValue(TEXT("MF_PostEffect_PaperBurn"), InPower);
					}
				}
			}
		}
	}
}

void AEnemy::OnPaperBurnEffectEnd()
{
	Destroy();
}

void AEnemy::PostInitializeComponents()
{
	if (DataTableRowHandle.IsNull()) { Super::PostInitializeComponents(); return; }
	if (DataTableRowHandle.RowName == NAME_None) { Super::PostInitializeComponents(); return; }
	FEnemyDataTableRow* Data = DataTableRowHandle.GetRow<FEnemyDataTableRow>(TEXT(""));

	AIControllerClass = Data->AIClass;

	Super::PostInitializeComponents();
}

void AEnemy::PostRegisterAllComponents()
{
	Super::PostRegisterAllComponents();

	SetEnemyData(DataTableRowHandle);
}

void AEnemy::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	SetEnemyData(DataTableRowHandle);
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

