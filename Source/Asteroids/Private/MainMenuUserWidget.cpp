#include "MainMenuUserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "GlobalEvents.h"
#include "GlobalVariables.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"

void UMainMenuUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Continue->OnClicked.AddDynamic(this, &UMainMenuUserWidget::OnPauseSwitched);
	NewGame->OnClicked.AddDynamic(this, &UMainMenuUserWidget::OnNewGameClicked);
	Controls->OnClicked.AddDynamic(this, &UMainMenuUserWidget::OnControlsSwitchClicked);
	Quit->OnClicked.AddDynamic(this, &UMainMenuUserWidget::OnQuitClicked);
	
	InitializeInputComponent();
	InputComponent->BindAction(TEXT("Pause"), IE_Pressed, this, &UMainMenuUserWidget::OnPauseSwitched);
}

void UMainMenuUserWidget::NativeDestruct()
{
	Continue->OnClicked.RemoveAll(this);
	NewGame->OnClicked.RemoveAll(this);
	Controls->OnClicked.RemoveAll(this);
	Quit->OnClicked.RemoveAll(this);

	Super::NativeDestruct();
}

void UMainMenuUserWidget::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("InputTypesEnum"), true);
	ControlsSwitchBlock->SetText(
		FText::FromStringTable(TEXT("/Game/InputTypesStringTable.InputTypesStringTable"),
		EnumPtr->GetDisplayNameTextByValue(static_cast<uint8>(CurrentInputType)).ToString()));
}

void UMainMenuUserWidget::OnPauseSwitched()
{
	const bool bPause = !UGameplayStatics::IsGamePaused(GetWorld());
	UGameplayStatics::SetGamePaused(GetWorld(), bPause);
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = bPause || CurrentInputType == InputTypesEnum::Mouse;
	SetVisibility(bPause ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
}

void UMainMenuUserWidget::OnNewGameClicked()
{
	Continue->bIsEnabled = true;
	OnPauseSwitched();

	GetWorld()->GetFirstPlayerController()->GetPawn()->Destroy();
	GetWorld()->GetAuthGameMode()->RestartPlayer(GetWorld()->GetFirstPlayerController());
}

void UMainMenuUserWidget::OnControlsSwitchClicked()
{	
	CurrentInputType = static_cast<InputTypesEnum>((static_cast<uint8>(CurrentInputType) + 1) % static_cast<uint8>(InputTypesEnum::MAX));
	SynchronizeProperties();

	OnControlsSwitchedEvent.ExecuteIfBound(CurrentInputType);
}

void UMainMenuUserWidget::OnQuitClicked()
{
	FGenericPlatformMisc::RequestExit(false);
}