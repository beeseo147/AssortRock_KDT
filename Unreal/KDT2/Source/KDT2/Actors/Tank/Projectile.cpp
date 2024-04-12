// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Tank/Projectile.h"
#include "MISC/MISC.h"
#include "Actors/GameMode/KDT2GameModeBase.h"

// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));

	SetRootComponent(Collider);
	ArrowComponent->SetupAttachment(GetRootComponent());
	StaticMeshComponent->SetupAttachment(Collider);
	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Collider->SetCollisionProfileName(FCollisionPresetNameTable::PlayerProjectile);

	OnActorHit.AddDynamic(this, &ThisClass::OnActorHitFunction);

	ConstructorHelpers::FObjectFinder<UStaticMesh> Asset{ TEXT("/Script/Engine.StaticMesh'/Engine/EditorMeshes/EditorHelp.EditorHelp'") };
	check(Asset.Succeeded());
	StaticMeshComponent->SetStaticMesh(Asset.Object);

	ProjectileMovementComponent->ProjectileGravityScale = 0.f;
}

AProjectile::~AProjectile()
{
}

void AProjectile::SetProjectileData(const FProjectileDataTableRow* InData)
{
	ensure(InData);
	GetWorld()->GetTimerManager().ClearTimer(InitialLifeSpanTimer);

	if (InData->InitialLifeSpan == 0.f)
	{
		ensure(false);
	}
	auto TimerDelegate = [this]()
		{
			AKDT2GameModeBase* GameMode = Cast<AKDT2GameModeBase>(GetWorld()->GetAuthGameMode());
			ensure(GameMode);
			GameMode->GetProjectilePool().Delete(this);
		};

	GetWorld()->GetTimerManager().SetTimer(InitialLifeSpanTimer, TimerDelegate, InData->InitialLifeSpan, false);
	//InitialLifeSpan = InData->InitialLifeSpan;

	Collider->SetSphereRadius(InData->ColliderSphereRadius);

	StaticMeshComponent->SetStaticMesh(InData->StaticMesh);
	StaticMeshComponent->SetRelativeTransform(InData->StaticMeshTransform);

	ProjectileMovementComponent->Velocity = FVector(1.f, 0.f, 0.f);
	ProjectileMovementComponent->MaxSpeed = InData->ProjectileSpeed;
	ProjectileMovementComponent->InitialSpeed = InData->ProjectileSpeed;
	ProjectileMovementComponent->ProjectileGravityScale = InData->ProjectileGravityScale;
}

void AProjectile::PreRegisterAllComponents()
{
	Super::PreRegisterAllComponents();
}

void AProjectile::PostRegisterAllComponents()
{
	Super::PostRegisterAllComponents();
}

void AProjectile::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	/*if (!DataTableRowHandle.DataTable) { return; }
	if (DataTableRowHandle.IsNull()) { return; }
	FProjectileDataTableRow* Data = DataTableRowHandle.GetRow<FProjectileDataTableRow>(TEXT(""));
	SetProjectileData(Data);*/
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void AProjectile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorld()->GetTimerManager().ClearTimer(InitialLifeSpanTimer);
}

void AProjectile::BeginDestroy()
{
	Super::BeginDestroy();
}

void AProjectile::FinishDestroy()
{
	Super::FinishDestroy();
}

void AProjectile::OnActorHitFunction(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

