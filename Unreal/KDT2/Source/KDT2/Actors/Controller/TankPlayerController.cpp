// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Controller/TankPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Data/Input/TankInputDataConfig.h"
#include "Actors/Tank/Tank.h"
#include "Actors/Interface/TankInterface.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	const UTankInputDataConfig* InputDataConfig = GetDefault<UTankInputDataConfig>();
	Subsystem->AddMappingContext(InputDataConfig->InputMappingContext, 0);
}

void ATankPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	ensure(EnhancedInputComponent);

	const UTankInputDataConfig* InputDataConfig = GetDefault<UTankInputDataConfig>();
	EnhancedInputComponent->BindAction(InputDataConfig->Zoom, ETriggerEvent::Started, this, &ThisClass::OnZoomIn);
	EnhancedInputComponent->BindAction(InputDataConfig->Zoom, ETriggerEvent::Completed, this, &ThisClass::OnZoomOut);
	EnhancedInputComponent->BindAction(InputDataConfig->Fire, ETriggerEvent::Triggered, this, &ThisClass::OnFire);
}

void ATankPlayerController::OnZoomIn(const FInputActionValue& InputActionValue)
{
	ITankInterface* Tank = Cast<ITankInterface>(GetPawn());
	ensure(Tank);
	Tank->ZoomIn();
}
void ATankPlayerController::OnZoomOut(const FInputActionValue& InputActionValue)
{
	ITankInterface* Tank = Cast<ITankInterface>(GetPawn());
	ensure(Tank);
	Tank->ZoomOut();
}

void ATankPlayerController::OnFire(const FInputActionValue& InputActionValue)
{
	ITankInterface* Tank = Cast<ITankInterface>(GetPawn());
	ensure(Tank);
	Tank->Fire();
}
