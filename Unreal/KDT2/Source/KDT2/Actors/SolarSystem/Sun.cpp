// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/SolarSystem/Sun.h"

// Sets default values
ASun::ASun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bool bCDO = HasAnyFlags(EObjectFlags::RF_ClassDefaultObject);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SunPowerTimelineComponent = CreateDefaultSubobject<UTimelineComponent>(TEXT("SunPower Timeline"));
	SetRootComponent(StaticMeshComponent);

	{
		static ConstructorHelpers::FObjectFinder<UStaticMesh> ObjectFinder(TEXT("/Script/Engine.StaticMesh'/Engine/EditorMeshes/EditorSphere.EditorSphere'"));
		ensure(ObjectFinder.Object);
		StaticMeshComponent->SetStaticMesh(ObjectFinder.Object);
	}
	{
		static ConstructorHelpers::FObjectFinder<UMaterial> ObjectFinder(TEXT("/Script/Engine.Material'/Game/KDT2/Blueprint/SolarSystem/MT_Sun.MT_Sun'"));
		ensure(ObjectFinder.Object);
		SunMaterial = ObjectFinder.Object;
		StaticMeshComponent->SetMaterial(0, SunMaterial);
	}

	{
		static ConstructorHelpers::FObjectFinder<UCurveFloat> ObjectFinder(TEXT("/Script/Engine.CurveFloat'/Game/KDT2/Blueprint/SolarSystem/Curve_SunPower.Curve_SunPower'"));
		ensure(ObjectFinder.Object);

		FOnTimelineFloat Delegate;
		Delegate.BindUFunction(this, TEXT("OnSunPower"));

		SunPowerTimelineComponent->AddInterpFloat(ObjectFinder.Object, Delegate);
		SunPowerTimelineComponent->SetPlayRate(0.5f);
		SunPowerTimelineComponent->SetLooping(true);
	}

	{
		PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("Sun light"));
		PointLight->SetupAttachment(GetRootComponent());
		PointLight->Intensity = 10.f;
		PointLight->AttenuationRadius = 1000000000.f;
		PointLight->bUseInverseSquaredFalloff = false;
		PointLight->LightFalloffExponent = 0.0001f;
	}
}

void ASun::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	MID = StaticMeshComponent->CreateDynamicMaterialInstance(0, SunMaterial);
}

// Called when the game starts or when spawned
void ASun::BeginPlay()
{
	Super::BeginPlay();

	SunPowerTimelineComponent->Play();
}

// Called every frame
void ASun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASun::OnSunPower(float InPower)
{
	UE_LOG(LogTemp, Warning, TEXT("Power: %f"), InPower);
	MID->SetScalarParameterValue(TEXT("Power"), InPower * 50.f);
}

