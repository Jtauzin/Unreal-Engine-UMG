// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Http.h"
#include  "Json.h"
#include "WidgetListItem.generated.h"

/**
 * 
 */
UCLASS()
class OBSTACLEASSAULT_API UWidgetListItem : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

protected:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* NameLabel;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Alignment;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* ArmorClass;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* HitPoints;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Strength;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Dexterity;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Constitution;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Intelligence;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Wisdom;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Charisma;
	UPROPERTY(meta = (BindWidget))
		class UButton* InfoButton;

	UFUNCTION()
		void OnMonsterInfoClicked();

private:
	void OnResponseRecieved(FHttpRequestPtr request, FHttpResponsePtr response, bool connectionSuccessful);
	void MakeHttpRequest(FString myUrl);
	void AdjustVisibility(ESlateVisibility ourVisibility);
	FString Index;
};
