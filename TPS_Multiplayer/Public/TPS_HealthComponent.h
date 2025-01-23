// Shoot Them Up Game

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
//#include "Dev/TPSIceDamageType.h"
//#include "Dev/TPS_FireDamageType.h"
#include "Engine/World.h"
#include "TimerManager.h"

#include "TPS_HealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeath)
DECLARE_MULTICAST_DELEGATE_OneParam(FOneHealthChanged,float)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TPS_MULTIPLAYER_API UTPS_HealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTPS_HealthComponent();

	float GetHealth() {

		return Health;

	}
	UFUNCTION(BlueprintCallable)
	bool IsDead() const { return FMath::IsNearlyZero(Health); }
	UFUNCTION(BlueprintCallable)
	void OnTakeAnyDamageHandle(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	FOnDeath OnDeath;
	FOneHealthChanged OnHealthChanged;


protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.0", ClampMax = "100.0"))
	float MaxHP = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Heal")
	bool AutoHeal;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Heal")
	float HealUpdateTime = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Heal")
	float HealDelay = 3.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Heal")
	float HealModifier = 5.0f;

	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	float Health = 0.0f;
	FTimerHandle HealTimerHandle;

	void HealUpdate();
	void SetHealth(float NewHealth);
		
};
