// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Tank/NewTank.h"
#include "Blueprint/UserWidget.h"
#include "Actors/Projectile/Projectile.h"
#include "Actors/Effect/Effect.h"
#include "Actors/GameMode/TankGameModeBase.h"

namespace Socket
{
	const FName TurretJointSocket = TEXT("turret_jntSocket");
	const FName FireSocket = TEXT("gun_1_jntSocket");
}

// Sets default values
ANewTank::ANewTank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	CameraSpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArmComponent"));
	DefaultCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("DefaultCamera"));
	{
		ConstructorHelpers::FObjectFinder<USkeletalMesh> Asset{TEXT("/Script/Engine.SkeletalMesh'/Game/KDT2/Blueprint/Tank/VigilanteContent/Vehicles/West_Tank_M1A1Abrams/SK_West_Tank_M1A1Abrams.SK_West_Tank_M1A1Abrams'")};
		check(Asset.Object);
		SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
		SkeletalMeshComponent->SetSkeletalMesh(Asset.Object);

		ConstructorHelpers::FClassFinder<UAnimInstance> AnimAsset{ TEXT("/Script/Engine.AnimBlueprint'/Game/KDT2/Blueprint/Tank/BPA_Tank.BPA_Tank_C'") };
		check(AnimAsset.Class);
		SkeletalMeshComponent->SetAnimClass(AnimAsset.Class);
	}

	ZoomCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ZoomCamera"));
	KDT2FloatingPawnMovement = CreateDefaultSubobject<UKDT2FloatingPawnMovement>(TEXT("KDT2FloatingPawnMovement"));

	BoxComponent->SetCollisionProfileName(FCollisionPresetNameTable::Player);
	SkeletalMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	CameraSpringArmComponent->bUsePawnControlRotation = true;
	CameraSpringArmComponent->bInheritRoll = false;

	/*
	- BoxComponent
		- SkeletalMeshComponent
			- CameraSpringArmComponent (turret_jntSocket)
				- DefaultCamera
			- ZoomCamera (gun_1_jntSocket)
	*/
	SkeletalMeshComponent->SetupAttachment(BoxComponent);
	CameraSpringArmComponent->SetupAttachment(SkeletalMeshComponent, Socket::TurretJointSocket);
	DefaultCamera->SetupAttachment(CameraSpringArmComponent);

	ZoomCamera->SetupAttachment(SkeletalMeshComponent, Socket::FireSocket);

	SetRootComponent(BoxComponent);
	BoxComponent->SetCanEverAffectNavigation(false);
	SkeletalMeshComponent->AddTickPrerequisiteComponent(KDT2FloatingPawnMovement);
}

ANewTank::~ANewTank()
{
}

void ANewTank::ZoomIn()
{
	if (!ZoomInWidget) { return; }
	ZoomCamera->SetActive(true);
	DefaultCamera->SetActive(false);
	ZoomInWidget->AddToViewport();
}

void ANewTank::ZoomOut()
{
	if (!ZoomInWidget) { return; }
	ZoomCamera->SetActive(false);
	DefaultCamera->SetActive(true);
	ZoomInWidget->RemoveFromParent();
}

void ANewTank::Fire()
{
	bool bTimer = GetWorld()->GetTimerManager().IsTimerActive(FireTimerHandle);
	if (bTimer) { return; }
	ensure(ProjectileRow->FireDelay > 0.f);
	GetWorld()->GetTimerManager().SetTimer(FireTimerHandle, ProjectileRow->FireDelay, false);

	const FTransform SocketTransform = SkeletalMeshComponent->GetSocketTransform(Socket::FireSocket);

	ATankGameModeBase* GameMode = Cast<ATankGameModeBase>(GetWorld()->GetAuthGameMode());
	ensure(GameMode);

	if (!ProjectileRow->FireEffect.IsNull() && ProjectileRow->FireEffect.RowName != NAME_None)
	{
		const FEffectDataTableRow* EffectDataTableRow = ProjectileRow->FireEffect.GetRow<FEffectDataTableRow>(TEXT(""));
		ensure(EffectDataTableRow);
		AEffect* NewEffect = GameMode->GetEffectPool().New<AEffect>(SocketTransform,
			[this, EffectDataTableRow](AEffect* NewActor)
			{
				NewActor->SetEffectData(EffectDataTableRow);
			}
		, true, this, nullptr);
	}

	AProjectile* NewProjectile = GameMode->GetProjectilePool().New<AProjectile>(SocketTransform,
		[this](AProjectile* NewActor)
		{
			NewActor->SetProjectileData(ProjectileRow);
		}

	, true, this, this);
}

void ANewTank::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	const int32 MaterialNum = SkeletalMeshComponent->GetSkinnedAsset()->GetMaterials().Num();
	for (int32 i = 0; i < MaterialNum; ++i)
	{
		SkeletalMeshComponent->CreateDynamicMaterialInstance(i);
	}
}

// Called when the game starts or when spawned
void ANewTank::BeginPlay()
{
	Super::BeginPlay();
	ensure(UI);
	ZoomInWidget = CreateWidget<UUserWidget>(GetWorld(), UI);

	UDataSubsystem* DataSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UDataSubsystem>();
	ProjectileRow = DataSubsystem->FindProjectile(ProjectileName);
}

void ANewTank::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

// Called every frame
void ANewTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANewTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

