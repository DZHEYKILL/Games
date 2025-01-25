#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Character.h"
#include "Engine/DamageEvents.h"
#include "Logging/LogMacros.h"


#include "TPSWeapon.generated.h"




UCLASS()
class TPS_MULTIPLAYER_API ATPSWeapon : public AActor
{
    GENERATED_BODY()

public:
    ATPSWeapon();

    // Начало и остановка стрельбы
    UFUNCTION(BlueprintCallable)
    virtual void StartFire();
    virtual void StopFire();

protected:
    virtual void BeginPlay() override;

    
    void MakeShot();
    void MakeDamage(const FHitResult& HitResult);
    APlayerController* GetPlayerController() const;
    bool GetPlayerViewPont(FVector& ViewLocation, FRotator& ViewRotation) const;
    FVector GetMuzzleWorldLocation() const;
    bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;
    void MakeHit(FHitResult& HitResult, const FVector TraceStart, const FVector TraceEnd) const;

    FTimerHandle ShotTimerHandle;
    // Компоненты оружия
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    USkeletalMeshComponent* WeaponMesh;

    // Параметры оружия
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    FName MuzzleSocketName = "MuzzleSocket";

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    float TraceMaxDistance = 10000.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    float DamageAmount = 10.0f; 
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    float TimeBetweenShots = 0.1f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    float BulletSpread = 1.3f;
};
