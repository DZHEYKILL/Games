// Shoot Them Up Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SkeletalMeshComponent.h"


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
protected:

	virtual void BeginPlay() override;


};
