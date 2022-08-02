// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Http.h"
#include  "Json.h"
#include "WidgetCodex.generated.h"

/**
 * 
 */
UCLASS()
class OBSTACLEASSAULT_API UWidgetCodex : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* CodexLabel;
	UPROPERTY(meta = (BindWidget))
		class UButton* MonsterButton;
	UPROPERTY(meta = (BindWidget))
		class UListView* ListView;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UWidgetCodex> EntryClass;

	UFUNCTION()
		void OnMonsterButtonClicked();

	void NativeConstruct() override;

private:
	void OnResponseRecieved(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bIsConnectionSuccessful);
};
