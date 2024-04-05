#include "LoadingScreen.h"
#include "Blueprint/UserWidget.h"
#include "MoviePlayer.h"

void ULoadingScreenSubSystem::SetLoadingScreenClass(TSubclassOf<UUserWidget> InWidgetClass)
{
	WidgetClass = InWidgetClass;
}

void ULoadingScreenSubSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &ThisClass::OnPreLoadMap);
}

void ULoadingScreenSubSystem::OnPreLoadMap(const FString& MapName)
{
	if (!WidgetClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("Widget class not set"));
		//check(false);
		return;
	}

	//UUserWidget* Widget = CreateWidget(GetWorld(), WidgetClass);
	if (IsMoviePlayerEnabled())
	{
		FLoadingScreenAttributes LoadingScreen;
		LoadingScreen.MinimumLoadingScreenDisplayTime = 1.f;
		//LoadingScreen.bAllowEngineTick = true;
		//LoadingScreen.WidgetLoadingScreen = Widget->TakeWidget();
		LoadingScreen.WidgetLoadingScreen = FLoadingScreenAttributes::NewTestLoadingScreenWidget();;
		GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
	}
	//else
	//{
	//	Widget->AddToViewport();
	//}
}
