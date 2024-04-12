// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Projectile.generated.h"

USTRUCT()
struct KDT2_API FProjectileDataTableRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = StaticMeshComponent)
	UStaticMesh* StaticMesh;
	UPROPERTY(EditAnywhere, Category = StaticMeshComponent)
	FTransform StaticMeshTransform;

	UPROPERTY(EditAnywhere, Category = Actor)
	float InitialLifeSpan = 5.f;

	UPROPERTY(EditAnywhere, Category = SphereComponent)
	float ColliderSphereRadius = 32.f;

	UPROPERTY(EditAnywhere, Category = ProjectileMovementComponent)
	float ProjectileSpeed = 2000.f;
	UPROPERTY(EditAnywhere, Category = ProjectileMovementComponent)
	float ProjectileGravityScale = 0.f;

	UPROPERTY(EditAnywhere, Category = Owner)
	float FireDelay = 1.f;
};

UCLASS()
class KDT2_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectile();
	~AProjectile();
	void SetProjectileData(const FProjectileDataTableRow* InData);

protected:
	virtual void PreRegisterAllComponents() override;
	virtual void PostRegisterAllComponents() override;
	virtual void OnConstruction(const FTransform& Transform) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void BeginDestroy() override;
	virtual void FinishDestroy() override;

	UFUNCTION()
	void OnActorHitFunction(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	//UPROPERTY(EditAnywhere, meta = (RowType = "/Script/KDT2.ProjectileDataTableRow"))
	//FDataTableRowHandle DataTableRowHandle;

protected:
	UPROPERTY(VisibleAnywhere)
	USphereComponent* Collider;

	UPROPERTY(EditAnywhere)
	UArrowComponent* ArrowComponent;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMeshComponent;

protected:
	UPROPERTY(EditAnywhere)
	UProjectileMovementComponent* ProjectileMovementComponent;

	FTimerHandle InitialLifeSpanTimer;
};
