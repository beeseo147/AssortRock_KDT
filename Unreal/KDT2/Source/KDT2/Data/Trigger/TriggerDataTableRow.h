// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "TriggerDataTableRow.generated.h"

USTRUCT(BlueprintType)
struct KDT2_API FTriggerDataTableRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> Class;

	UPROPERTY(EditAnywhere)
	FDataTableRowHandle SubData;
};