#include "Spaceship.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GlobalEvents.h"
#include "GlobalVariables.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraComponent.h"
#include "PaperSpriteComponent.h"

ASpaceship::ASpaceship(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SpaceshipSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SpaceshipSprite"));
	SpaceshipSprite->SetupAttachment(RootComponent);
	Shooter = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Shooter"));
	Shooter->SetupAttachment(SpaceshipSprite);

	OnControlsSwitchedEvent.BindUObject(this, &ASpaceship::SwitchControls);
}

void ASpaceship::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentInputType != InputTypesEnum::Mouse)
		return;

	FVector mouseWorldLocation, mouseWorldDirection;
	if (GetWorld()->GetFirstPlayerController()->DeprojectMousePositionToWorld(
		mouseWorldLocation, mouseWorldDirection))
		MoveRight(FQuat::FindBetweenVectors(GetActorUpVector(),
			mouseWorldLocation - GetActorLocation()).Y);
}

void ASpaceship::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis(TEXT("MoveForward"), this, &ASpaceship::MoveForward);
	SwitchControls(CurrentInputType);
}

void ASpaceship::SwitchControls(const InputTypesEnum newInputType)
{
	InputComponent->ClearActionBindings();
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("InputTypesEnum"), true);
	InputComponent->BindAction(FName(TEXT("Fire") + EnumPtr->GetDisplayNameTextByValue(static_cast<int64>(newInputType)).ToString()),
		IE_Pressed, this, &ASpaceship::Shoot);

	if (newInputType != InputTypesEnum::Mouse)
		InputComponent->BindAxis(FName(TEXT("MoveRight")),
			this, &ASpaceship::MoveRight);
	else
		if (InputComponent->AxisBindings.Num() > 1)
			InputComponent->AxisBindings.RemoveAt(1);
}

void ASpaceship::MoveForward(float Delta)
{
	if (GetVelocity().Size() < MaxVelocity) // Limit speed
		SpaceshipSprite->AddImpulse(GetActorUpVector() * ImpulseVelocity * Delta * FApp::GetDeltaTime());
}

void ASpaceship::MoveRight(float Delta)
{
	AddActorWorldRotation(FQuat(FVector::YAxisVector, RotationSpeed * Delta * FApp::GetDeltaTime()));
}

void ASpaceship::Shoot()
{
	Shooter->Activate();
}