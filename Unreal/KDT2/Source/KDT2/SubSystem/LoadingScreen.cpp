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
		//widget class net set
		UE_LOG(LogTemp, Warning, TEXT("OnPreLoadMap"));
		check(false);
		return;
	}
	UUserWidget* Widget = CreateWidget(GetWorld(), WidgetClass);
	if (IsMoviePlayerEnabled())
	{
		FLoadingScreenAttributes LoadingScreen;
		//LoadingScreen.bAutoCompleteWhenLoadingCompletes = true;
		LoadingScreen.MinimumLoadingScreenDisplayTime = 4.f;
		//LoadingScreen.WidgetLoadingScreen = Widget->TakeWidget();
		LoadingScreen.WidgetLoadingScreen = FLoadingScreenAttributes::NewTestLoadingScreenWidget();
		GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
	}
	/*else
	{
		Widget->AddToViewport();
	}*/
}
