// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerInterface.h"

void ITriggerInterface::Active()
{
	AActor* Actor = Cast<AActor>(this);
	if (!Actor)
	{
		ensure(false);
		return;
	}
	Execute_ReceiveActive(Actor);
}

void ITriggerInterface::Inactive()
{
	AActor* Actor = Cast<AActor>(this);
	if (!Actor)
	{
		ensure(false);
		return;
	}
	Execute_ReceiveInactive(Actor);
}

void ITriggerInterface::InTrigger()
{
	AActor* Actor = Cast<AActor>(this);
	if (!Actor)
	{
		ensure(false);
		return;
	}
	Execute_ReceiveInTrigger(Actor);
}

void ITriggerInterface::OutTrigger()
{
	AActor* Actor = Cast<AActor>(this);
	if (!Actor)
	{
		ensure(false);
		return;
	}
	Execute_ReceiveOutTrigger(Actor);
}

void ITriggerInterface::OnSubData(const FDataTableRowHandle& InTableRowBase)
{
	AActor* Actor = Cast<AActor>(this);
	if (!Actor)
	{
		ensure(false);
		return;
	}
	Execute_ReceiveOnSubData(Actor, InTableRowBase);
}
