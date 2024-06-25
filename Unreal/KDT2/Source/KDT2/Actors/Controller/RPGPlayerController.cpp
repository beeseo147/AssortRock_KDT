// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGPlayerController.h"
#include "Data/Input/RPGInputDataConfig.h"
#include "GameFramework/SpringArmComponent.h"
#include "Subsystem/Subsystem.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/MISC.h"

void ARPGPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	const URPGInputDataConfig* RPGInputDataConfig = GetDefault<URPGInputDataConfig>();
	Subsystem->AddMappingContext(RPGInputDataConfig->InputMappingContext, 0);

	SetControlRotation(RPGSaveGame->ControllerRotation);
}

void ARPGPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ARPGPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	ensure(EnhancedInputComponent);

	const URPGInputDataConfig* InputDataConfig = GetDefault<URPGInputDataConfig>();
	EnhancedInputComponent->BindAction(InputDataConfig->ZoomWheel, ETriggerEvent::Triggered, this, &ThisClass::OnZoomWheel);
}

void ARPGPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	PawnSpringArm->TargetArmLength = FMath::Lerp(PawnSpringArm->TargetArmLength,
		TargetArmLength, DeltaSeconds * 3.f);
}

void ARPGPlayerController::OnPossess(APawn* aPawn)
{
	UInventorySubsystem* InventorySubsystem = ULocalPlayer::GetSubsystem<UInventorySubsystem>(GetLocalPlayer());
	InventorySubsystem->MakeInventory();

	RPGSaveGame = Cast<URPGSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("RPG"), 0));
	if (!RPGSaveGame)
	{
		RPGSaveGame = Cast<URPGSaveGame>(UGameplayStatics::CreateSaveGameObject(URPGSaveGame::StaticClass()));
	}
	ensure(RPGSaveGame);

	InventorySubsystem->Load(this, RPGSaveGame);

	Super::OnPossess(aPawn);

	UClass* WidgetClass = FindObject<UClass>(ANY_PACKAGE, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/KDT2/Blueprint/RPG/UI/UI_RPGMain.UI_RPGMain_C'"));
	RPGMainWidget = CreateWidget<URPGMainWidget>(GetWorld(), WidgetClass);
	RPGMainWidget->AddToViewport();

	AKDT2Character* KDT2Character = Cast<AKDT2Character>(aPawn);
	if (IsValid(KDT2Character))
	{
		UDataSubsystem* DataSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UDataSubsystem>();
		const FCharacterDataTableRow* CharacterDataTableRow = DataSubsystem->FindChacter(TEXT("Soldier3"));

		KDT2Character->SetData(CharacterDataTableRow);
	}

	PawnSpringArm = aPawn->GetComponentByClass<USpringArmComponent>();
	PawnSpringArm->TargetArmLength = RPGSaveGame->TargetArmLength;
	TargetArmLength = RPGSaveGame->TargetArmLength;
}

void ARPGPlayerController::OnUnPossess()
{
	APawn* AA = GetPawn();

	Super::OnUnPossess();

	RPGSaveGame->ControllerRotation = GetControlRotation();
	RPGSaveGame->TargetArmLength = TargetArmLength;

	UInventorySubsystem* InventorySubsystem = ULocalPlayer::GetSubsystem<UInventorySubsystem>(GetLocalPlayer());
	InventorySubsystem->Save(RPGSaveGame);
	InventorySubsystem->ClearInventory();

	UGameplayStatics::SaveGameToSlot(RPGSaveGame, TEXT("RPG"), 0);
}

void ARPGPlayerController::OnZoomWheel(const FInputActionValue& InputActionValue)
{
	const float ActionValue = InputActionValue.Get<float>();

	TargetArmLength += ActionValue * -50.f;
	TargetArmLength = FMath::Clamp(TargetArmLength, 150.f, 1200.f);
}
