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

    // Получение контроллера игрока
    APlayerController* GetPlayerController() const;

    // Таймер для стрельбы
    FTimerHandle ShotTimerHandle;

    // Компоненты оружия
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    USkeletalMeshComponent* WeaponMesh;

    // Параметры оружия
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    FName MuzzleSocketName = "MuzzleSocket";

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    float TraceMaxDistance = 2000.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    float DamageAmount = 10.0f; // Значение по умолчанию
};
