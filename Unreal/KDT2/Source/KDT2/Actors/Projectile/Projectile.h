// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Actors/Effect/Effect.h"
#include "Projectile.generated.h"

USTRUCT()
struct KDT2_API FProjectileDataTableRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Projectile|StaticMeshComponent")
	UStaticMesh* StaticMesh;
	UPROPERTY(EditAnywhere, Category = "Projectile|StaticMeshComponent")
	TArray<UMaterial*> Materials;

	UPROPERTY(EditAnywhere, Category = "Projectile|StaticMeshComponent")
	FTransform StaticMeshTransform;

	UPROPERTY(EditAnywhere, Category = "Projectile|Actor")
	float InitialLifeSpan = 5.f;

	UPROPERTY(EditAnywhere, Category = "Projectile|SphereComponent")
	float ColliderSphereRadius = 32.f;

	UPROPERTY(EditAnywhere, Category = "Projectile|ProjectileMovementComponent")
	float ProjectileSpeed = 2000.f;
	UPROPERTY(EditAnywhere, Category = "Projectile|ProjectileMovementComponent")
	float ProjectileGravityScale = 0.f;

	UPROPERTY(EditAnywhere, Category = "Projectile|Effect", meta = (RowType = "/Script/KDT2.EffectDataTableRow"))
	FDataTableRowHandle HitEffect;

	UPROPERTY(EditAnywhere, Category = "Projectile|Damage")
	float Damage = 1.f;
	UPROPERTY(EditAnywhere, Category = "Projectile|Damage")
	float DamageRadius = 1000.f;	// DamageRadius가 0이면 단일 대상 공격

	UPROPERTY(EditAnywhere, Category = "Owner")
	float FireDelay = 1.f;
	UPROPERTY(EditAnywhere, Category = "Owner", meta = (RowType = "/Script/KDT2.EffectDataTableRow"))
	FDataTableRowHandle FireEffect;
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

	UFUNCTION()
	void OnReturnToPool(AActor* DestroyedActor);

	UFUNCTION()
	void OnActorPoolBeginDelete();

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
	const FProjectileDataTableRow* ProjectileDataTableRow;

	FScriptDelegate ParentActorDestroyedDelegate;
};
