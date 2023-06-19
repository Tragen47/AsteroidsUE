#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "WorldBorders.generated.h"

UCLASS()
class ASTEROIDS_API AWorldBorders : public ATriggerBox
{
	GENERATED_BODY()

	AWorldBorders();

	void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);
	UFUNCTION()
	void OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor);
};