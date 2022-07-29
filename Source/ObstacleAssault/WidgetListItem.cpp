// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetListItem.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Monster.h"

void UWidgetListItem::NativeOnListItemObjectSet(UObject* ListItemObject) {
	UMonster* monster = Cast<UMonster>(ListItemObject);
	NameLabel->SetText(monster->name);
	index = monster->index;
	InfoButton->OnClicked.RemoveDynamic(this, &UWidgetListItem::OnMonsterInfoClicked);
	InfoButton->OnClicked.AddDynamic(this, &UWidgetListItem::OnMonsterInfoClicked);
	adjustVisibility(ESlateVisibility::Collapsed);
}

void UWidgetListItem::OnMonsterInfoClicked() {
	if (Alignment->GetVisibility() == ESlateVisibility::Collapsed)
	{
		FString myUrl = "https://www.dnd5eapi.co/api/monsters/" + index;
		MakeHttpRequest(myUrl);
	}
	else
	{
		adjustVisibility(ESlateVisibility::Collapsed);
	}
}

void UWidgetListItem::OnResponseRecieved(FHttpRequestPtr request, FHttpResponsePtr response, bool connectionSuccessful) {
	TSharedPtr<FJsonObject> responseObj;
	TSharedRef<TJsonReader<>> reader = TJsonReaderFactory<>::Create(response->GetContentAsString());
	FJsonSerializer::Deserialize(reader, responseObj);
	UWidgetListItem::Alignment->SetText(FText::FromString("Alignment: " + responseObj->GetStringField("alignment")));
	UWidgetListItem::ArmorClass->SetText(FText::FromString("Armor Class: " + responseObj->GetStringField("armor_class")));
	UWidgetListItem::HitPoints->SetText(FText::FromString("Hit Points: " + responseObj->GetStringField("hit_points")));
	UWidgetListItem::Strength->SetText(FText::FromString("Strength: " + responseObj->GetStringField("strength")));
	UWidgetListItem::Dexterity->SetText(FText::FromString("Dexterity: " + responseObj->GetStringField("dexterity")));
	UWidgetListItem::Constitution->SetText(FText::FromString("Constitution: " + responseObj->GetStringField("constitution")));
	UWidgetListItem::Intelligence->SetText(FText::FromString("Intelligence: " + responseObj->GetStringField("intelligence")));
	UWidgetListItem::Wisdom->SetText(FText::FromString("Wisdom: " + responseObj->GetStringField("wisdom")));
	UWidgetListItem::Charisma->SetText(FText::FromString("Charisma: " + responseObj->GetStringField("charisma")));
	adjustVisibility(ESlateVisibility::Visible);
}

void UWidgetListItem::MakeHttpRequest(FString myUrl) {
	FHttpRequestRef request = FHttpModule::Get().CreateRequest();
	request->OnProcessRequestComplete().BindUObject(this, &UWidgetListItem::OnResponseRecieved);
	request->SetURL(myUrl);
	request->SetVerb("GET");
	request->ProcessRequest();
}

void UWidgetListItem::adjustVisibility(ESlateVisibility ourVisibility) {
	UWidgetListItem::Alignment->SetVisibility(ourVisibility);
	UWidgetListItem::ArmorClass->SetVisibility(ourVisibility);
	UWidgetListItem::HitPoints->SetVisibility(ourVisibility);
	UWidgetListItem::Strength->SetVisibility(ourVisibility);
	UWidgetListItem::Dexterity->SetVisibility(ourVisibility);
	UWidgetListItem::Constitution->SetVisibility(ourVisibility);
	UWidgetListItem::Intelligence->SetVisibility(ourVisibility);
	UWidgetListItem::Wisdom->SetVisibility(ourVisibility);
	UWidgetListItem::Charisma->SetVisibility(ourVisibility);
}
