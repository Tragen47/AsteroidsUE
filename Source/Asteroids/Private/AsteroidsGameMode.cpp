#include "AsteroidsGameMode.h"
#include "EngineUtils.h"
#include "PrimitiveSceneInfo.h"
#include "RenderCore.h"

AAsteroidsGameMode::AAsteroidsGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AAsteroidsGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	/*for (FActorIterator It(GetWorld()); It; ++It)
	{
		AActor* A = *It;
		if (A && !A->IsPendingKill() && A != this && 
			!A->IsA<AController>() && ShouldReset(A) &&
			A->IsRootComponentMovable() &&
			A->WasRecentlyRendered(0.1f))                                               
		{
			FVector upperRightWorldLocation, upperRightWorldDirection;
			FVector lowerLeftWorldLocation, lowerLeftWorldDirection;
			const FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
			GetWorld()->GetFirstPlayerController()->DeprojectScreenPositionToWorld(
				ViewportSize.X, 0, upperRightWorldLocation, upperRightWorldDirection);
			GetWorld()->GetFirstPlayerController()->DeprojectScreenPositionToWorld(
				0, ViewportSize.Y, lowerLeftWorldLocation, lowerLeftWorldDirection);

			FVector newActorWrappedLocation(A->GetActorLocation());

			for (int32 i = 0; i < 3; ++i)
			{
				if (A->GetActorLocation()[i] > upperRightWorldLocation[i])
					newActorWrappedLocation[i] = lowerLeftWorldLocation[i];
				if (A->GetActorLocation()[i] < lowerLeftWorldLocation[i])
					newActorWrappedLocation[i] = upperRightWorldLocation[i];
			}

			A->SetActorLocation(newActorWrappedLocation);
		}
	}*/
}