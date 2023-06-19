#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AsteroidsGameMode.generated.h"

UCLASS()
class ASTEROIDS_API AAsteroidsGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	AAsteroidsGameMode();

	virtual void Tick(float DeltaSeconds) override;
};