// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Weapon/Weapon.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Data/Input/WeaponInputDataConfig.h"
#include "Animation/RPGAnimInstance.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	SetRootComponent(SkeletalMeshComponent);
}

void AWeapon::SetData(const FDataTableRowHandle& InDataTableRowHandle)
{
	DataTableRowHandle = InDataTableRowHandle;

	if (DataTableRowHandle.IsNull()) { return; }
	if (DataTableRowHandle.RowName == NAME_None) { return; }
	FWeaponDataTableRow* Data = DataTableRowHandle.GetRow<FWeaponDataTableRow>(TEXT(""));
	SetData(Data);
}

void AWeapon::SetData(const FWeaponDataTableRow* InData)
{
	ensure(InData);

	WeaponDataTableRow = InData;

	SkeletalMeshComponent->SetSkeletalMesh(InData->WeaponSkeletalMesh);
	SkeletalMeshComponent->SetAnimClass(InData->WeaponAnimClass);

	ensure(Owner);
	USkeletalMeshComponent* OwnerMesh = Owner->GetComponentByClass<USkeletalMeshComponent>();
	ensure(OwnerMesh);
	OwnerMesh->SetAnimClass(InData->OwnerAnimClass);
}

void AWeapon::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	//SetData(DataTableRowHandle);
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	//SetData(DataTableRowHandle);
	
	APawn* OwnerPawn = Cast<APawn>(Owner);
	ensure(OwnerPawn);
	if (OwnerPawn)
	{
		APlayerController* PC = Cast<APlayerController>(OwnerPawn->GetController());
		if (PC)
		{
			UEnhancedInputLocalPlayerSubsystem* Subsystem =
				ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());

			const UWeaponInputDataConfig* InputDataConfig = GetDefault<UWeaponInputDataConfig>();
			Subsystem->AddMappingContext(InputDataConfig->InputMappingContext, 0);

			EnableInput(PC);

			UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
			ensure(EnhancedInputComponent);

			EnhancedInputComponent->BindAction(InputDataConfig->Attack, ETriggerEvent::Started, this, &ThisClass::OnAttack);
		}
	}
}

void AWeapon::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	APawn* OwnerPawn = Cast<APawn>(Owner);
	ensure(OwnerPawn);
	if (OwnerPawn)
	{
		APlayerController* PC = Cast<APlayerController>(OwnerPawn->GetController());
		if (PC)
		{
			UEnhancedInputLocalPlayerSubsystem* Subsystem =
				ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());

			const UWeaponInputDataConfig* InputDataConfig = GetDefault<UWeaponInputDataConfig>();
			Subsystem->RemoveMappingContext(InputDataConfig->InputMappingContext);
		}
	}
}

void AWeapon::OnAttack(const FInputActionValue& InputActionValue)
{
	bool bMontagePlaying = false;
	if (WeaponDataTableRow->WeaponAttackMontage)
	{
		UAnimInstance* AnimInstance = SkeletalMeshComponent->GetAnimInstance();
		if (AnimInstance->Montage_IsPlaying(nullptr)) { return; }
		AnimInstance->Montage_Play(WeaponDataTableRow->WeaponAttackMontage, WeaponDataTableRow->BaseAnimPlayRate);
	}
	if (WeaponDataTableRow->OwnerAttackMontage)
	{
		USkeletalMeshComponent* OwnerMesh = Owner->GetComponentByClass<USkeletalMeshComponent>();
		ensure(OwnerMesh);
		UAnimInstance* AnimInstance = OwnerMesh->GetAnimInstance();
		if (AnimInstance->Montage_IsPlaying(nullptr)) { return; }
		AnimInstance->Montage_Play(WeaponDataTableRow->OwnerAttackMontage, WeaponDataTableRow->BaseAnimPlayRate);
	}
}

void AWeapon::SetDamaged()
{
	if (WeaponDataTableRow->WeaponDamagedMontage)
	{
		UAnimInstance* AnimInstance = SkeletalMeshComponent->GetAnimInstance();
		AnimInstance->StopAllMontages(0.25f);
		AnimInstance->Montage_Play(WeaponDataTableRow->WeaponDamagedMontage, WeaponDataTableRow->BaseAnimPlayRate);
	}
	if (WeaponDataTableRow->OwnerDamagedMontage)
	{
		USkeletalMeshComponent* OwnerMesh = Owner->GetComponentByClass<USkeletalMeshComponent>();
		ensure(OwnerMesh);
		UAnimInstance* AnimInstance = OwnerMesh->GetAnimInstance();
		AnimInstance->StopAllMontages(0.25f);
		AnimInstance->Montage_Play(WeaponDataTableRow->OwnerDamagedMontage, WeaponDataTableRow->BaseAnimPlayRate);
	}
}

void AWeapon::SetDie()
{
	{
		URPGAnimInstance* Anim = Cast<URPGAnimInstance>(SkeletalMeshComponent->GetAnimInstance());
		if (IsValid(Anim))
		{
			Anim->SetDie();
		}
	}
	{
		USkeletalMeshComponent* OwnerMesh = Owner->GetComponentByClass<USkeletalMeshComponent>();
		URPGAnimInstance* Anim = Cast<URPGAnimInstance>(OwnerMesh->GetAnimInstance());
		if (IsValid(Anim))
		{
			Anim->SetDie();
		}
	}
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

