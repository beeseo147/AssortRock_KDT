// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Trigger/MyTriggerBase.h"
#include "Misc/MISC.h"
#include "TriggerInterface.h"

// Sets default values
AMyTriggerBase::AMyTriggerBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bGenerateOverlapEventsDuringLevelStreaming = true;

	ActiveRadius = CreateDefaultSubobject<USphereComponent>(TEXT("ActiveRadius"));
	Trigger = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger"));
	TriggerObject = CreateDefaultSubobject<UChildActorComponent>(TEXT("TriggerObject"));
	SetRootComponent(ActiveRadius);

	Trigger->SetupAttachment(GetRootComponent());
	TriggerObject->SetupAttachment(GetRootComponent());

	ActiveRadius->SetSphereRadius(600.f);
	Trigger->SetSphereRadius(120.f);

	// FText	: 국가별(한국: 안녕, 영어: Hello) 처리가 가능한 문자열
	// FString	: 문자열(C++ wstring)
	// FName	: 문자열 해슁(특정 타입을 정수로 변환해서 들고 있는 것)
	//			대소문자 구분이 없다
	//			정수로 변환해서 관리
	//			검색 속도를 향상시키기 위해서 사용(문자열 비교보다 정수 비교가 더 빠르기 때문)
	//			Ex) "Hello" -> 00123123003215
	//	unsigned int64 HashValue = HashFunction("Hello");
	ActiveRadius->SetCollisionProfileName(FCollisionPresetNameTable::PlayerDetect);
	Trigger->SetCollisionProfileName(FCollisionPresetNameTable::PlayerDetect);

	{
		// - ActiveRadius
		//		- Trigger
		//		- TriggerObject
	}

	ActiveRadius->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnActiveRadiusBeginOverlap);
	ActiveRadius->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnActiveRadiusEndOverlap);
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnTriggerBeginOverlap);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnTriggerEndOverlap);
}

void AMyTriggerBase::OnActiveRadiusBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Active();
}

void AMyTriggerBase::OnActiveRadiusEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Inactive();
}

void AMyTriggerBase::OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	InTrigger();
}

void AMyTriggerBase::OnTriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	OutTrigger();
}

AActor* AMyTriggerBase::GetTriggerOjbect()
{
	AActor* Actor = TriggerObject->GetChildActor();
	if (!IsValid(Actor))
	{
		ensureAlwaysMsgf(false, TEXT("Actor is nullptr"));
		return nullptr;
	}

	const bool bIsImplemented = Actor->GetClass()->ImplementsInterface(UTriggerInterface::StaticClass());
	if (!bIsImplemented)
	{
		ensureAlwaysMsgf(false, TEXT("Class must ImplementsInterface ITriggerInterface"));
		return nullptr;
	}

	return Actor;
}

void AMyTriggerBase::Active()
{
	AActor* Actor = GetTriggerOjbect();
	if (!Actor) { return; }

	ITriggerInterface* Interface = Cast<ITriggerInterface>(Actor);
	if (Interface)
	{
		Interface->Active();
	}
	else
	{
		ITriggerInterface::Execute_ReceiveActive(Actor);
	}
}

void AMyTriggerBase::Inactive()
{
	AActor* Actor = GetTriggerOjbect();
	if (!Actor) { return; }

	ITriggerInterface* Interface = Cast<ITriggerInterface>(Actor);
	if (Interface)
	{
		Interface->Inactive();
	}
	else
	{
		ITriggerInterface::Execute_ReceiveInactive(Actor);
	}
}

void AMyTriggerBase::InTrigger()
{
	AActor* Actor = GetTriggerOjbect();
	if (!Actor) { return; }

	ITriggerInterface* Interface = Cast<ITriggerInterface>(Actor);
	if (Interface)
	{
		Interface->InTrigger();
	}
	else
	{
		ITriggerInterface::Execute_ReceiveInTrigger(Actor);
	}
}

void AMyTriggerBase::OutTrigger()
{
	AActor* Actor = GetTriggerOjbect();
	if (!Actor) { return; }

	ITriggerInterface* Interface = Cast<ITriggerInterface>(Actor);
	if (Interface)
	{
		Interface->OutTrigger();
	}
	else
	{
		ITriggerInterface::Execute_ReceiveOutTrigger(Actor);
	}
}

void AMyTriggerBase::PreRegisterAllComponents()
{
	Super::PreRegisterAllComponents();

	if (TriggerObjectData.IsNull()) { return; }
	if (TriggerObjectData.RowName == NAME_None) { return; }
	const FTriggerDataTableRow* Data = TriggerObjectData.GetRow<FTriggerDataTableRow>(TEXT(""));
	ensure(Data);
	if (TriggerDataTableRow == Data) { return; }
	TriggerDataTableRow = Data;
	TriggerObject->SetChildActorClass(TriggerDataTableRow->Class);
}

void AMyTriggerBase::PostRegisterAllComponents()
{
	Super::PostRegisterAllComponents();

	AActor* Actor = GetTriggerOjbect();
	if (!Actor) { return; }

	Actor->SetOwner(this);

	if (TriggerDataTableRow->SubData.IsNull()) { return; }
	if (TriggerDataTableRow->SubData.RowName == NAME_None) { return; }

	ITriggerInterface* Interface = Cast<ITriggerInterface>(Actor);
	if (Interface)
	{
		Interface->OnSubData(TriggerDataTableRow->SubData);
	}
	else
	{
		ITriggerInterface::Execute_ReceiveOnSubData(Actor, TriggerObjectData);
	}
}

void AMyTriggerBase::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

// Called when the game starts or when spawned
void AMyTriggerBase::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMyTriggerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

