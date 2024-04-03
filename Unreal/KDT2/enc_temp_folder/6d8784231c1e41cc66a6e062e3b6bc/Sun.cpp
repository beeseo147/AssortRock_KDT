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
		static ConstructorHelpers::FObjectFinder<UStaticMesh> ObjectFinder(TEXT("/Script/Engine.StaticMesh'/Engine/EngineMeshes/Sphere.Sphere'"));
		//ensure(ObjectFinder.Object);
		StaticMeshComponent->SetStaticMesh(ObjectFinder.Object);
	}//액터의 StaticMeshComponent에 찾은 Sphere 스태틱 메쉬를 할당합니다.
	{
		static ConstructorHelpers::FObjectFinder<UMaterial> ObjectFinder(TEXT("/Script/Engine.Material'/Game/KDT2/BluePrint/SolarSystem/MT_Sun.MT_Sun'"));
		ensure(ObjectFinder.Object);
		SunMaterial = ObjectFinder.Object;
		StaticMeshComponent->SetMaterial(0, SunMaterial);
	}//액터의 메시 컴포넌트에 StaticMeshComponent에 찾은 MT_Sun 메테리얼(0번)을 할당합니다.

	{
		static ConstructorHelpers::FObjectFinder<UCurveFloat> ObjectFinder(TEXT("/Script/Engine.CurveFloat'/Game/KDT2/BluePrint/SolarSystem/Curve_SunPower.Curve_SunPower'"));
		ensure(ObjectFinder.Object);

		FOnTimelineFloat Delegate;//Delegate는 함수 포인터
		Delegate.BindUFunction(this, TEXT("OnSunPower"));

		SunPowerTimelineComponent->AddInterpFloat(ObjectFinder.Object, Delegate);
		SunPowerTimelineComponent->SetPlayRate(0.5f);
		SunPowerTimelineComponent->SetLooping(true);
		//타임 라인이 반복 되고
		//0.5초마다
		//Float형의 interp을 생성한다
	}
	{
		PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("Sun Light"));
		PointLight->SetupAttachment(GetRootComponent());
		PointLight->Intensity = 10.0f;
		PointLight->AttenuationRadius = 1000000.0f;
		PointLight->bUseInverseSquaredFalloff = false;
		PointLight->LightFalloffExponent = 0.0001f;
	}
}
//AActor.h에 있는 초기 생성 OnConstruction
void ASun::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	MID = StaticMeshComponent->CreateDynamicMaterialInstance(0, SunMaterial);
}//UMaterialInstanceDynamic MID에 스태틱 메쉬 컴포넌트에 SunMaterial을 할당합니다.(사실 위에 했던거)
//Blueprint에서 사용한 CreateDynamicMaterialInstance를 함수에서 사용

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

