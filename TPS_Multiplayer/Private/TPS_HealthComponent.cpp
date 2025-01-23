// Shoot Them Up Game


#include "TPS_HealthComponent.h"
#include "GameFramework/Actor.h"



// Sets default values for this component's properties
UTPS_HealthComponent::UTPS_HealthComponent()
{

	PrimaryComponentTick.bCanEverTick = false;
	
}


// Called when the game starts
void UTPS_HealthComponent::BeginPlay()
{
	Super::BeginPlay();

	SetHealth(MaxHP);
	

	AActor* ComponentOwner = GetOwner();
	if (ComponentOwner)
	{
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UTPS_HealthComponent::OnTakeAnyDamageHandle);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ComponentOwner is nullptr"));
	}
	if (ComponentOwner) {

		AutoHeal = true;

	}
}



void UTPS_HealthComponent::OnTakeAnyDamageHandle(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{

	Health = Health - Damage;
	if (Damage <= 0.0f || IsDead() || !GetWorld())return;

	SetHealth(Health - Damage);
	OnHealthChanged.Broadcast(Health);
	if (IsDead())
	{
	
		AutoHeal = false;
		OnDeath.Broadcast();
	}
	else if (AutoHeal && GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, this, &UTPS_HealthComponent::HealUpdate, HealUpdateTime, true, HealDelay);
	}
	/*
	
	
	if (DamageType)
	{
		if (DamageType->IsA<UTPS_FireDamageType>())
		{

		}
		else if(DamageType->IsA<UTPSIceDamageType>())
		{

		}
	}
	*/


}

void UTPS_HealthComponent::HealUpdate()
{
	SetHealth(Health + HealModifier);
	OnHealthChanged.Broadcast(Health);

	if (FMath::IsNearlyEqual(Health, MaxHP) && GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
	}

}

void UTPS_HealthComponent::SetHealth(float NewHealth)
{
	Health = FMath::Clamp(NewHealth, 0.0f, MaxHP);
	OnHealthChanged.Broadcast(Health);

}
