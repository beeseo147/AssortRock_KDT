// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

USTRUCT()
struct KDT2_API FWeaponDataTableRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Weapon")
	USkeletalMesh* WeaponSkeletalMesh;
	UPROPERTY(EditAnywhere, Category = "Weapon")
	TSubclassOf<UAnimInstance> WeaponAnimClass;
	UPROPERTY(EditAnywhere, Category = "Weapon")
	TSubclassOf<UAnimInstance> OwnerAnimClass;

	UPROPERTY(EditAnywhere, Category = "Weapon|Montage")
	UAnimMontage* WeaponAttackMontage;
	UPROPERTY(EditAnywhere, Category = "Weapon|Montage")
	UAnimMontage* OwnerAttackMontage;

	UPROPERTY(EditAnywhere, Category = "Weapon|Montage")
	UAnimMontage* WeaponDamagedMontage;
	UPROPERTY(EditAnywhere, Category = "Weapon|Montage")
	UAnimMontage* OwnerDamagedMontage;

	UPROPERTY(EditAnywhere, Category = "Weapon|Montage")
	float BaseAnimPlayRate = 1.f;
};

UCLASS()
class KDT2_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();
	virtual void SetData(const FDataTableRowHandle& InDataTableRowHandle);
	virtual void SetData(const FWeaponDataTableRow* InData);

	void SetDamaged();
	void SetDie();

protected:
	virtual void OnConstruction(const FTransform& Transform) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

protected:
	void OnAttack(const FInputActionValue& InputActionValue);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, meta = (RowType = "/Script/KDT2.EnemyDataTableRow"))
	FDataTableRowHandle DataTableRowHandle;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* SkeletalMeshComponent;

protected:
	const FWeaponDataTableRow* WeaponDataTableRow = nullptr;
};
