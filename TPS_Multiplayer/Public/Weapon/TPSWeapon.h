// Shoot Them Up Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TPSWeapon.generated.h"

UCLASS()
class TPS_MULTIPLAYER_API ATPSWeapon : public AActor
{
	GENERATED_BODY()
	
public:	

	ATPSWeapon();


	//UPROPERTY(EditAnywhere,BluePrintReadWrite,Category = "Weapon")
	//USkeletalMeshComponent ATPSWeapon = ;
protected:

	virtual void BeginPlay() override;


};
