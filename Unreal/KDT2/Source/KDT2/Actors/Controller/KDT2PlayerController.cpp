// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Controller/KDT2PlayerController.h"
#include "Data/Input/BasicInputDataConfig.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
void AKDT2PlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	PlayerCameraManager->ViewPitchMax = 40;
	PlayerCameraManager->ViewPitchMin = -40;
}
void AKDT2PlayerController::BeginPlay()
{
	Super::BeginPlay();

	UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	const UBasicInputDataConfig* BasicInputDataConfig=GetDefault<UBasicInputDataConfig>();
	Subsystem->AddMappingContext(BasicInputDataConfig->InputMappingContext,0);
}

void AKDT2PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	ensure(EnhancedInputComponent);

	const UBasicInputDataConfig* BasicInputDataConfig = GetDefault<UBasicInputDataConfig>();
	EnhancedInputComponent->BindAction(BasicInputDataConfig->Move,ETriggerEvent::Triggered,this,&ThisClass::OnMove);
	EnhancedInputComponent->BindAction(BasicInputDataConfig->Look, ETriggerEvent::Triggered, this, &ThisClass::OnLook);
}

void AKDT2PlayerController::OnMove(const FInputActionValue& InputActionValue)
{
	APawn* ControlledPawn = GetPawn();
	
	const FRotator Rotation = K2_GetActorRotation();
	const FRotator YawRotation = FRotator(0., Rotation.Yaw, 0.0f);
	const FVector ForwardVector = YawRotation.Vector();
	const FVector RightVector = FRotationMatrix(YawRotation).GetScaledAxis(EAxis::Y);

	const FVector ActionValue = InputActionValue.Get<FVector>();
	ControlledPawn->AddMovementInput(ForwardVector, ActionValue.Y);
	ControlledPawn->AddMovementInput(RightVector, ActionValue.X);
}

void AKDT2PlayerController::OnLook(const FInputActionValue& InputActionValue)
{
	const FVector ActionValue = InputActionValue.Get<FVector>();
	AddYawInput(ActionValue.X);
	AddPitchInput(ActionValue.Y);
}
