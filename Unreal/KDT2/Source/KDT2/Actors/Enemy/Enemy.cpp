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

	SetRootComponent(BoxComponent);
	SkeletalMeshComponent->SetupAttachment(GetRootComponent());
	SkeletalMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	BoxComponent->SetCollisionProfileName(FCollisionPresetNameTable::Enemy);
}

float AEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	static float HP = 2;
	HP -= Damage;
	if (HP <= 0.f)
	{
		Destroy();
	}

	return Damage;
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

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

