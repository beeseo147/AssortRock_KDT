// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StatusBarUserWidget.h"
#include "RPGMainWidget.generated.h"

/**
 * 
 */
UCLASS()
class KDT2_API URPGMainWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetHP(const float CurrentHP, const float MaxHP);

protected:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UStatusBarUserWidget* PlayerStatusBar;
};
