#pragma once
#include "Blueprint/UserWidget.h"
#include "MainMenuUserWidget.generated.h"

class UButton;
class UTextBlock;

UCLASS()
class ASTEROIDS_API UMainMenuUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	virtual void SynchronizeProperties() override;
public:

	UPROPERTY(meta = (BindWidget))
	UButton* Continue;
	UPROPERTY(meta = (BindWidget))
	UButton* NewGame;
	UPROPERTY(meta = (BindWidget))
	UButton* Controls;
	UPROPERTY(meta = (BindWidget))
	UButton* Quit;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
	UTextBlock* ControlsSwitchBlock;

	UFUNCTION()
	void OnPauseSwitched();
	UFUNCTION()
	void OnNewGameClicked();
	UFUNCTION()
	void OnControlsSwitchClicked();
	UFUNCTION()
	void OnQuitClicked();
};