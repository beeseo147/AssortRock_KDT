// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/StatusBarUserWidget.h"

void UStatusBarUserWidget::SetHP(const float CurrentHP, const float MaxHP)
{
	if (FMath::IsNearlyZero(MaxHP))
	{
		ensure(false);
	}
	const float Percent = CurrentHP / MaxHP;
	HPBar->SetPercent(Percent);
}
