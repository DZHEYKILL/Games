// Shoot Them Up Game

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Weapon/TPSWeapon.h"

#include "TPSWeaponComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TPS_MULTIPLAYER_API UTPSWeaponComponent : public UActorComponent
{

	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTPSWeaponComponent();

	void Fire();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ATPSWeapon> WeaponClass;
	UPROPERTY(EditAnywhere)
	FName WeaponAttachPointName = "WeaponSocket";
	UPROPERTY(EditAnywhere)
	ATPSWeapon* CurrentWeapon;

	void SpawnWeapon();
};