// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/SolarSystem/Planet.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Sun.h"

// Sets default values
APlanet::APlanet()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	{
		DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));

		PlanetAxis = CreateDefaultSubobject<USceneComponent>(TEXT("PlanetAxis"));
		PlanetStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlanetStaticMeshComponent"));

		CloudAxis = CreateDefaultSubobject<USceneComponent>(TEXT("CloudAxis"));
		CloudStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CloudStaticMeshComponent"));
	}
	SetRootComponent(DefaultSceneRoot);

	PlanetAxis->SetupAttachment(GetRootComponent());
	PlanetStaticMeshComponent->SetupAttachment(PlanetAxis);

	CloudAxis->SetupAttachment(GetRootComponent());
	CloudStaticMeshComponent->SetupAttachment(CloudAxis);
	CloudStaticMeshComponent->SetRelativeScale3D(FVector(1.01, 1.01, 1.01));

	{
		static ConstructorHelpers::FObjectFinder<UStaticMesh> ObjectFinder(TEXT("/Script/Engine.StaticMesh'/Engine/EditorMeshes/EditorSphere.EditorSphere'"));
		ensure(ObjectFinder.Object);
		PlanetStaticMeshComponent->SetStaticMesh(ObjectFinder.Object);
		CloudStaticMeshComponent->SetStaticMesh(ObjectFinder.Object);
	}
}

#if WITH_EDITOR
void APlanet::PreEditChange(FProperty* PropertyThatWillChange)
{
	Super::PreEditChange(PropertyThatWillChange);

	if (PropertyThatWillChange->GetName() == TEXT("SatelliteArray"))
	{
		Temp = SatelliteArray;
	}
	else
	{
		Temp.Empty();
	}
}

void APlanet::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.GetPropertyName() == TEXT("SatelliteArray"))
	{
		const int32 Index = PropertyChangedEvent.GetArrayIndex(TEXT("SatelliteArray"));
		switch (PropertyChangedEvent.ChangeType)
		{
		case EPropertyChangeType::ArrayAdd:
		{
			SatelliteArray[Index].Create(this, nullptr);
			break;
		}
		case EPropertyChangeType::Duplicate:
		{
			SatelliteArray[Index].Create(this, &SatelliteArray[Index]);
			break;
		}
		case EPropertyChangeType::ArrayRemove:
		{
			const int32 Num = Temp.Num();
			for (int32 i = 0; i < Num; ++i)
			{
				if (SatelliteArray.Find(Temp[i]) == INDEX_NONE)
				{
					Temp[i].Destroy();
					break;
				}
			}
			Temp.Empty();
			break;
		}
		case EPropertyChangeType::ArrayClear:
		{
			for (auto& It : Temp)
			{
				It.Destroy();
			}
			Temp.Empty();
			break;
		}
		}
	}
}
#endif

void APlanet::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	const int32 ElementIndex = 0;
	UMaterialInterface* MaterialInterface = PlanetStaticMeshComponent->GetMaterial(ElementIndex);
	PlanetMaterialInstanceDynamic = PlanetStaticMeshComponent->CreateDynamicMaterialInstance(ElementIndex, MaterialInterface);

	CloudStaticMeshComponent->SetVisibility(bCloud);

	if (bNightSide)
	{
		Sun = Cast<ASun>(UGameplayStatics::GetActorOfClass(GetWorld(), ASun::StaticClass()));
		CalculateNightSide();
	}
	else
	{
		PlanetMaterialInstanceDynamic->SetVectorParameterValue(TEXT("LightDirection"), FVector::ZeroVector);
	}
}

// Called when the game starts or when spawned
void APlanet::BeginPlay()
{
	Super::BeginPlay();
}

void APlanet::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void APlanet::BeginDestroy()
{
	Super::BeginDestroy();
}

// Called every frame
void APlanet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CalculateNightSide();

	{
		const double DeltaSpeed = (DeltaTime * PlanetRotationSpeed);
		const FRotator Rotator{ 0., DeltaSpeed, 0. };
		const FQuat Quat = Rotator.Quaternion();
		PlanetStaticMeshComponent->AddLocalRotation(Quat);
	}
	{
		const double DeltaSpeed = (DeltaTime * CloudRotationSpeed);
		const FRotator Rotator{ 0., DeltaSpeed, 0. };
		const FQuat Quat = Rotator.Quaternion();
		CloudStaticMeshComponent->AddLocalRotation(Quat);
	}

	for (auto& It : SatelliteArray)
	{
		const double DeltaSpeed = (DeltaTime * It.RotationSpeed);
		const FRotator Rotator{ 0., DeltaSpeed, 0. };
		const FQuat Quat = Rotator.Quaternion();
		It.Axis->AddLocalRotation(Quat);
	}
}

void APlanet::CalculateNightSide()
{
	if (!bNightSide) { return; }
	if (!IsValid(Sun)) { return; }

	FVector Position = GetActorLocation();
	FVector SunPosition = Sun->GetActorLocation();
	FVector Direction = UKismetMathLibrary::GetDirectionUnitVector(Position, SunPosition);
	PlanetMaterialInstanceDynamic->SetVectorParameterValue(TEXT("LightDirection"), Direction);
}

void FSatellite::Create(class APlanet* InPlanet, FSatellite* InTemplate)
{
	FName AxisName = MakeUniqueObjectName(InPlanet, USceneComponent::StaticClass());
	USceneComponent* AxisTemplate = InTemplate ? InTemplate->Axis : nullptr;
	Axis = NewObject<USceneComponent>(InPlanet, AxisName, RF_Transactional, AxisTemplate);
	Axis->RegisterComponent();
	if (!InTemplate)
	{
		Axis->AttachToComponent(InPlanet->DefaultSceneRoot, FAttachmentTransformRules::SnapToTargetIncludingScale);
	}
	else
	{
		Axis->AttachToComponent(InPlanet->DefaultSceneRoot, FAttachmentTransformRules::KeepWorldTransform);
	}

	FName ChildActorComponentName = MakeUniqueObjectName(InPlanet, UChildActorComponent::StaticClass());
	UChildActorComponent* ChildActorComponentTemplate = InTemplate ? InTemplate->ChildActorComponent : nullptr;
	ChildActorComponent = NewObject<UChildActorComponent>(InPlanet, ChildActorComponentName, RF_Transactional, ChildActorComponentTemplate);
	ChildActorComponent->RegisterComponent();
	if (!InTemplate)
	{
		ChildActorComponent->AttachToComponent(Axis, FAttachmentTransformRules::SnapToTargetIncludingScale);
	}
	else
	{
		ChildActorComponent->AttachToComponent(Axis, FAttachmentTransformRules::KeepWorldTransform);
	}
}

void FSatellite::Destroy()
{
	if (IsValid(Axis))
	{
		Axis->DestroyComponent();
		ChildActorComponent->DestroyComponent();
	}
}
