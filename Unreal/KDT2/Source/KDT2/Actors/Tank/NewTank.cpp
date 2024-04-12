// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Tank/NewTank.h"
#include "Projectile.h"
#include "MISC/MISC.h"
#include "Blueprint/UserWidget.h"
#include "Actors/GameMode/KDT2GameModeBase.h"
// Sets default values
ANewTank::ANewTank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	CameraSpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArmComponent"));
	DefaultCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("DefaultCamera"));
	{
		ConstructorHelpers::FObjectFinder<USkeletalMesh> Asset{ TEXT("/Script/Engine.SkeletalMesh'/Game/KDT2/Blueprint/Tank/VigilanteContent/Vehicles/West_Tank_M1A1Abrams/SK_West_Tank_M1A1Abrams.SK_West_Tank_M1A1Abrams'") };
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
	CameraSpringArmComponent->SetupAttachment(SkeletalMeshComponent, TEXT("turret_jntSocket"));
	DefaultCamera->SetupAttachment(CameraSpringArmComponent);

	ZoomCamera->SetupAttachment(SkeletalMeshComponent, TEXT("gun_1_jntSocket"));

	SetRootComponent(BoxComponent);

	const TSet<UActorComponent*>& Components = GetComponents();
	for (auto* It : Components)
	{
		if (It != SkeletalMeshComponent)
		{
			SkeletalMeshComponent->AddTickPrerequisiteComponent(It);
		}
	}
}

// Called when the game starts or when spawned
void ANewTank::BeginPlay()
{
	Super::BeginPlay();
	ensure(UI);
	ZoomInWidget = CreateWidget<UUserWidget>(GetWorld(), UI);
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

