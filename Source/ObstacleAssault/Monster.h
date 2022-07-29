// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Monster.generated.h"

/**
 * 
 */
UCLASS()
class OBSTACLEASSAULT_API UMonster : public UObject
{
	GENERATED_BODY()

public:
	UMonster();
	FText name;
	FString index;
	FString Alignment;
	FString ArmorClass;
	FString HitPoints;
	FString Strength;
	FString Dexterity;
	FString Constitution;
	FString Intelligence;
	FString Wisdom;
	FString Charisma;

};
