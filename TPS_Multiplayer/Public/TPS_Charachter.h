// Shoot Them Up Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/SceneComponent.h"
#include "Components/TextRenderComponent.h" 
#include "Engine/DamageEvents.h"
#include "GameFramework/Controller.h"
#include "Weapon/TPSWeapon.h"

#include "TPS_HealthComponent.h"
#include "TPS_Charachter.generated.h"

UCLASS()
class TPS_MULTIPLAYER_API ATPS_Charachter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATPS_Charachter();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float ForwardButtonFloat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RightButtonFloat;


	UPROPERTY(EditAnywhere)
	USceneComponent* RootSceneComponent;

	UPROPERTY(EditAnywhere)
	UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UTPS_HealthComponent* HealthComponent;

	UPROPERTY(EditAnywhere)
	UTextRenderComponent* HealthTextComponent;

	UPROPERTY(EditAnywhere)
	FVector2D LandedDamageVelocity = FVector2D(900.0f, 1200.0f);
	UPROPERTY(EditAnywhere)
	FVector2D LandedDamage = FVector2D(10.0f, 100.0f);

	UPROPERTY(EditAnywhere)
	TSubclassOf<ATPSWeapon> WeaponClass;

	UFUNCTION(BlueprintCallable)
	void OnGroundLanded(const FHitResult& Hit);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	 
	void MoveForward (float Amount);
	void MoveRight (float Amount);

	void LookUp (float Amount);
	void Turn(float Amount);
	
	void Sprint();
	void StopSprint();
	void OnDeath();

	void OnHealthChanged(float Health);

	void SpawnWeapon();

};
