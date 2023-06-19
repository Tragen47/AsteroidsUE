#pragma once
#include "GameFramework/Pawn.h"
#include "Spaceship.generated.h"

class UNiagaraComponent;
class UPaperSpriteComponent;

UCLASS()
class ASTEROIDS_API ASpaceship : public APawn
{
	GENERATED_BODY()

	ASpaceship(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, Category = Movement)
	float ImpulseVelocity = 500;
	UPROPERTY(EditAnywhere, Category = Movement)
	float MaxVelocity = 1000;
	UPROPERTY(EditAnywhere, Category = Movement)
	float RotationSpeed = 2.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UPaperSpriteComponent* SpaceshipSprite;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UNiagaraComponent* Shooter;

public:
	UFUNCTION()
	void SwitchControls(const InputTypesEnum newInputType);
	void MoveForward(float);
	void MoveRight(float);
	void Shoot();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
};