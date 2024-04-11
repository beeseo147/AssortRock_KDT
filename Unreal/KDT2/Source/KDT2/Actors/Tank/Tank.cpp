// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Tank/Tank.h"
#include "MISC/MISC.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"

// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	CameraSpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArmComponent"));
	DefaultCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("DefaultCamera"));
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	TurretSpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("TurretSpringArmComponent"));
	Turret = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret"));
	Muzzle = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle"));
	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	ZoomCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ZoomCamera"));
	KDT2FloatingPawnMovement = CreateDefaultSubobject<UKDT2FloatingPawnMovement>(TEXT("KDT2FloatingPawnMovement"));

	BoxComponent->SetCollisionProfileName(FCollisionPresetNameTable::Player);

	CameraSpringArmComponent->bUsePawnControlRotation = true;
	CameraSpringArmComponent->bInheritRoll = false;

	TurretSpringArmComponent->bUsePawnControlRotation = true;
	TurretSpringArmComponent->bInheritRoll = false;
	TurretSpringArmComponent->bInheritPitch = false;
	TurretSpringArmComponent->bEnableCameraRotationLag = true;

	/*
	- BoxComponent
		- CameraSpringArmComponent
			- DefaultCamera
		- Body
		- TurretSpringArmComponent
			- Turret
			- Muzzle
				- ArrowComponent
				- ZoomCamera
	*/
	SetRootComponent(BoxComponent);
	CameraSpringArmComponent->SetupAttachment(GetRootComponent());
	DefaultCamera->SetupAttachment(CameraSpringArmComponent);

	Body->SetupAttachment(GetRootComponent());

	TurretSpringArmComponent->SetupAttachment(GetRootComponent());
	Turret->SetupAttachment(TurretSpringArmComponent);
	Muzzle->SetupAttachment(TurretSpringArmComponent);
	ArrowComponent->SetupAttachment(Muzzle);
	ZoomCamera->SetupAttachment(Muzzle);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	ensure(UI);
	ZoomInWidget = CreateWidget<UUserWidget>(GetWorld(), UI);

	UDataSubsystem* DataSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UDataSubsystem>();
	ProjectileRow = DataSubsystem->FindProjectile(ProjectileName);
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::ZoomIn()
{
	ZoomCamera->SetActive(true);
	DefaultCamera->SetActive(false);
	ZoomInWidget->AddToViewport();
}

void ATank::ZoomOut()
{
	ZoomCamera->SetActive(false);
	DefaultCamera->SetActive(true);
	ZoomInWidget->RemoveFromParent();
}

void ATank::Fire()
{
	bool bTimer = GetWorld()->GetTimerManager().IsTimerActive(FireTimerHandle);
	if (bTimer) { return; }
	ensure(ProjectileRow->FireDelay > 0.f);
	GetWorld()->GetTimerManager().SetTimer(FireTimerHandle, ProjectileRow->FireDelay, false);

	UWorld* World = GetWorld();
	ensure(World);

	const FTransform& MuzzleTransform = Muzzle->GetComponentTransform();
	FTransform Transform = FTransform(MuzzleTransform.GetRotation(), MuzzleTransform.GetLocation());

	AProjectile* NewProjectile = ProjectilePool.New<AProjectile>(MuzzleTransform, true, this, this); // World->SpawnActorDeferred<AProjectile>(AProjectile::StaticClass(), Transform, this, this, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	NewProjectile->SetProjectileData(ProjectileRow);
	//NewProjectile->FinishSpawning(MuzzleTransform, true);
}

