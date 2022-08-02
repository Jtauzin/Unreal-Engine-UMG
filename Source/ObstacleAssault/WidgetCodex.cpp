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
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &UWidgetCodex::OnResponseRecieved);
	Request->SetURL("https://www.dnd5eapi.co/api/monsters");
	Request->SetVerb("GET");
	Request->ProcessRequest();
	CodexLabel->SetVisibility(ESlateVisibility::Collapsed);
	MonsterButton->SetVisibility(ESlateVisibility::Collapsed);
}

void UWidgetCodex::OnResponseRecieved(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bIsConnectionSuccessful)
{
	TSharedPtr<FJsonObject> ResponseObj;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	FJsonSerializer::Deserialize(Reader, ResponseObj);
	TArray<TSharedPtr<FJsonValue>> ResultArray = ResponseObj->GetArrayField("results");
	TArray<UMonster*> Monsters;
	for (int32 i = 0; i < ResultArray.Num(); i++) {
		UMonster* Monster = NewObject<UMonster>();
		Monster->Name = FText::FromString(*ResultArray[i]->AsObject()->GetStringField("name"));
		Monster->Index = FText::FromString(*ResultArray[i]->AsObject()->GetStringField("index")).ToString();
		Monsters.Add(Monster);
	}
	ListView->SetListItems(Monsters);
}
