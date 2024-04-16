// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/StatusComponent.h"

void UStatusComponent::SetStatusData(const FStatusDataTableRow* InData)
{
	ensure(InData);

	StatusDataTableRow = InData;

	HP = InData->HP;
}

// Sets default values for this component's properties
UStatusComponent::UStatusComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

float UStatusComponent::ProcessDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	HP = HP - DamageAmount;
	if (HP <= 0.f)
	{
		AActor* Actor = GetOwner();
		Actor->Destroy();
	}
	return HP;
}


// Called when the game starts
void UStatusComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UStatusComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

FStatusDataTableRow::FStatusDataTableRow()
	: StatusComponentClass(UStatusComponent::StaticClass())
{
}

FStatus2DataTableRow::FStatus2DataTableRow()
{
	StatusComponentClass = UStatusComponent2::StaticClass();
}
