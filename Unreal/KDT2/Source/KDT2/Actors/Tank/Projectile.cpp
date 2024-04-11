// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Tank/Projectile.h"
#include "MISC/MISC.h"

// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	InitialLifeSpan = 5.f;

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

void AProjectile::SetProjectileData(const FProjectileDataTableRow* InData)
{
	ensure(InData);

	Collider->SetSphereRadius(InData->ColliderSphereRadius);

	StaticMeshComponent->SetStaticMesh(InData->StaticMesh);
	StaticMeshComponent->SetRelativeTransform(InData->StaticMeshTransform);

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

void AProjectile::OnActorHitFunction(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

