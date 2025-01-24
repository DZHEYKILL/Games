// Shoot Them Up Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"

#include "TPSWeapon.generated.h"

UCLASS()
class TPS_MULTIPLAYER_API ATPSWeapon : public AActor
{
	GENERATED_BODY()
	
public:	

	ATPSWeapon();
	UFUNCTION(BlueprintCallable)
	virtual void Fire();

	UPROPERTY(EditAnywhere,BluePrintReadWrite,Category = "Weapon")
	USkeletalMeshComponent* WeaponMesh;
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Weapon")
	FName MuzzleSocketName = "MuzzleSocket";
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Weapon")
	float TraceMaxDistance = 2000.0f;
protected:

	virtual void BeginPlay() override;


void MakeShot();
};