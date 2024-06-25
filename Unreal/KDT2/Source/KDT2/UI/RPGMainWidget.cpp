// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RPGMainWidget.h"

void URPGMainWidget::SetHP(const float CurrentHP, const float MaxHP)
{
	PlayerStatusBar->SetHP(CurrentHP, MaxHP);
}
