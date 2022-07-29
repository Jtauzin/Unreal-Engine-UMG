// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetCodex.h"
#include <Components/TextBlock.h>
#include <Components/Button.h>
#include <Components/ListView.h>
#include "Monster.h"

void UWidgetCodex::NativeConstruct()
{
	Super::NativeConstruct();
	FScriptDelegate ourDelagate;
	MonsterButton->OnClicked.AddDynamic(this, &UWidgetCodex::OnMonsterButtonClicked);
}

void UWidgetCodex::OnMonsterButtonClicked()
{
	FHttpRequestRef request = FHttpModule::Get().CreateRequest();
	request->OnProcessRequestComplete().BindUObject(this, &UWidgetCodex::OnResponseRecieved);
	request->SetURL("https://www.dnd5eapi.co/api/monsters");
	request->SetVerb("GET");
	request->ProcessRequest();
	CodexLabel->SetVisibility(ESlateVisibility::Collapsed);
	MonsterButton->SetVisibility(ESlateVisibility::Collapsed);
}

void UWidgetCodex::OnResponseRecieved(FHttpRequestPtr request, FHttpResponsePtr response, bool connectionSuccessful)
{
	TSharedPtr<FJsonObject> responseObj;
	TSharedRef<TJsonReader<>> reader = TJsonReaderFactory<>::Create(response->GetContentAsString());
	FJsonSerializer::Deserialize(reader, responseObj);
	TArray<TSharedPtr<FJsonValue>> resultArray = responseObj->GetArrayField("results");
	TArray<UMonster*> monsters;
	for (int32 i = 0; i < resultArray.Num(); i++) {
		UMonster* monster = NewObject<UMonster>();
		monster->name = FText::FromString(*resultArray[i]->AsObject()->GetStringField("name"));
		monster->index = FText::FromString(*resultArray[i]->AsObject()->GetStringField("index")).ToString();
		monsters.Add(monster);
	}
	ListView->SetListItems(monsters);
}
