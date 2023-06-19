#include "WorldBorders.h"
#include "DrawDebugHelpers.h"
#include "EngineUtils.h"
#include "PrimitiveSceneInfo.h"
#include "RenderCore.h"

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green,text)
#define printFString(text, fstring) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT(text), fstring))

AWorldBorders::AWorldBorders()
{
    //Register Events
    OnActorBeginOverlap.AddDynamic(this, &AWorldBorders::OnOverlapBegin);
    OnActorEndOverlap.AddDynamic(this, &AWorldBorders::OnOverlapEnd);
}

void AWorldBorders::BeginPlay()
{
    Super::BeginPlay();
    DrawDebugBox(GetWorld(), GetActorLocation(), GetComponentsBoundingBox().GetExtent(), FColor::Purple, true, -1, 0, 5);
}

void AWorldBorders::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor)
{
    // check if Actors do not equal nullptr and that 
    if (OtherActor && (OtherActor != this))
    {
        // print to screen using above defined method when actor enters trigger box
        print("Overlap Begin");
        printFString("Overlapped Actor = %s", *OtherActor->GetName());
    }
}

void AWorldBorders::OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor)
{
	if (OtherActor && (OtherActor != this))
	{
		// print to screen using above defined method when actor leaves trigger box
		print("Overlap Ended");
		printFString("%s has left the Trigger Box", *OtherActor->GetName());

		if (!OtherActor->IsPendingKill() &&
			!OtherActor->IsA<AController>() &&
			OtherActor->IsRootComponentMovable())
		{
			FVector upperRightWorldLocation = GetComponentsBoundingBox().Max;
			FVector lowerLeftWorldLocation = GetComponentsBoundingBox().Min;

			FVector newActorWrappedLocation(OtherActor->GetActorLocation());

			for (int32 i = 0; i < 3; ++i)
			{
				if (OtherActor->GetActorLocation()[i] > upperRightWorldLocation[i])
					newActorWrappedLocation[i] = lowerLeftWorldLocation[i] - OtherActor->GetComponentsBoundingBox().GetExtent()[i];
				if (OtherActor->GetActorLocation()[i] < lowerLeftWorldLocation[i])
					newActorWrappedLocation[i] = upperRightWorldLocation[i] + OtherActor->GetComponentsBoundingBox().GetExtent()[i];
			}

			OtherActor->SetActorLocation(newActorWrappedLocation);
		}
	}
}