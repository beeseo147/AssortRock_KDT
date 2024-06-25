// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Character/KDT2Character.h"
#include "Components/KDT2CharacterMovementComponent.h"
#include "Actors/Weapon/Weapon.h"
#include "Actors/Controller/RPGPlayerController.h"

// Sets default values
AKDT2Character::AKDT2Character(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UKDT2CharacterMovementComponent>(Super::CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponChildActorComponent = CreateDefaultSubobject<UChildActorComponent>(TEXT("WeaponChildActorComponent"));
	WeaponChildActorComponent->SetupAttachment(GetRootComponent());
	WeaponChildActorComponent->SetChildActorClass(AWeapon::StaticClass());
}

void AKDT2Character::SetData(const FDataTableRowHandle& InDataTableRowHandle)
{
	DataTableRowHandle = InDataTableRowHandle;

	if (DataTableRowHandle.IsNull()) { return; }
	if (DataTableRowHandle.RowName == NAME_None) { return; }

	CharacterDataTableRow = DataTableRowHandle.GetRow<FCharacterDataTableRow>(TEXT(""));
	SetData(CharacterDataTableRow);
}

void AKDT2Character::SetData(const FCharacterDataTableRow* InData)
{
	CharacterDataTableRow = InData;
	GetMesh()->SetSkeletalMesh(CharacterDataTableRow->SkeletalMesh);
	GetMesh()->SetRelativeTransform(CharacterDataTableRow->SkeletalMeshTransform);
	//GetMesh()->SetAnimClass(CharacterDataTableRow->AnimClass);

	AWeapon* Weapon = Cast<AWeapon>(WeaponChildActorComponent->GetChildActor());
	if (IsValid(Weapon))
	{
		Weapon->SetOwner(this);
		Weapon->SetActorRelativeTransform(CharacterDataTableRow->SkeletalMeshTransform);
		if (CachedWeaponData)
		{
			Weapon->SetData(CachedWeaponData);
		}
		else if (!CharacterDataTableRow->WeaponData.IsNull() &&
			CharacterDataTableRow->WeaponData.RowName != NAME_None)
		{
			Weapon->SetData(CharacterDataTableRow->WeaponData);
		}
	}

	{
		FStatusDataTableRow* StatusDataTableRow = CharacterDataTableRow->StatusData.GetRow<FStatusDataTableRow>(TEXT(""));
		if (!StatusComponent)
		{
			StatusComponent = NewObject<UStatusComponent>(this, StatusDataTableRow->StatusComponentClass, TEXT("StatusComponent"));
			StatusComponent->RegisterComponent();
		}

		Cast<UCharacterMovementComponent>(GetMovementComponent())->MaxWalkSpeed = StatusDataTableRow->Speed;
		StatusComponent->SetStatusData(StatusDataTableRow);

		{
			RPGMainWidget = Cast<ARPGPlayerController>(GetController())->RPGMainWidget;
			RPGMainWidget->SetHP(StatusComponent->HP, StatusDataTableRow->HP);
		}
	}

}

void AKDT2Character::SetWeaponData(const FWeaponDataTableRow* InData)
{
	AActor* WeaponActor = WeaponChildActorComponent->GetChildActor();
	if (IsValid(WeaponActor))
	{
		if (CharacterDataTableRow == nullptr)
		{
			CachedWeaponData = InData;
			return;
		}
		AWeapon* Weapon = Cast<AWeapon>(WeaponActor);
		Weapon->SetOwner(this);
		Weapon->SetActorRelativeTransform(CharacterDataTableRow->SkeletalMeshTransform);
		Weapon->SetData(InData);
	}
}

float AKDT2Character::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	Damage = StatusComponent->ProcessDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	RPGMainWidget->SetHP(StatusComponent->HP, StatusComponent->StatusDataTableRow->HP);

	return Damage;
}

void AKDT2Character::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	//SetData(DataTableRowHandle);
}

void AKDT2Character::PostRegisterAllComponents()
{
	Super::PostRegisterAllComponents();

	//SetData(DataTableRowHandle);
}

// Called when the game starts or when spawned
void AKDT2Character::BeginPlay()
{
	Super::BeginPlay();
	
}

void AKDT2Character::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	ARPGPlayerController* RPGPlayerController = Cast<ARPGPlayerController>(Controller);
	ensure(RPGPlayerController);

	SetActorLocation(RPGPlayerController->RPGSaveGame->PlayerLocation);
	SetActorRotation(RPGPlayerController->RPGSaveGame->PlayerRotation);
}

void AKDT2Character::UnPossessed()
{
	ARPGPlayerController* RPGPlayerController = Cast<ARPGPlayerController>(Controller);
	ensure(RPGPlayerController);

	RPGPlayerController->RPGSaveGame->PlayerLocation = GetActorLocation();
	RPGPlayerController->RPGSaveGame->PlayerRotation = GetActorRotation();

	Super::UnPossessed();
}

void AKDT2Character::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

// Called every frame
void AKDT2Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	/*StatusComponent->HP -= DeltaTime;

	RPGMainWidget->SetHP(StatusComponent->HP, StatusComponent->StatusDataTableRow->HP);*/
}

// Called to bind functionality to input
void AKDT2Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

