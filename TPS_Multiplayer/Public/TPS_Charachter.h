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
#include "TPSWeaponComponent.h"
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


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bSprinting;
	UPROPERTY(BlueprintReadOnly)
	float WalkSpeed = 450.0f;
	UPROPERTY(BlueprintReadOnly)
	float SprintSpeed = 800.0f;
	UPROPERTY(BlueprintReadOnly)
	float ScopeSpeed = 250.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* RootSceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UTPS_HealthComponent* HealthComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextRenderComponent* HealthTextComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTPSWeaponComponent* WeaponComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D LandedDamageVelocity = FVector2D(900.0f, 1200.0f);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D LandedDamage = FVector2D(10.0f, 100.0f);

	UPROPERTY(EditAnywhere)
	float YawJOPA = GetActorRotation().Yaw;
	UPROPERTY(EditAnywhere)
	float PitchJOPA = GetActorRotation().Pitch;


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



};
