// Shoot Them Up Game

#include "TPSWeaponComponent.h"

#include "TPS_Charachter.h"
#include "Weapon/TPSWeapon.h"
#include "GameFramework/Character.h"


// Sets default values for this component's properties
UTPSWeaponComponent::UTPSWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}



// Called when the game starts
void UTPSWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	SpawnWeapon();
	
}
	void UTPSWeaponComponent::SpawnWeapon()
	{

		if (!GetWorld()) return;

		ACharacter* Charachter = Cast<ACharacter>(GetOwner());
		if (!Charachter) return;

		CurrentWeapon = GetWorld()->SpawnActor<ATPSWeapon>(WeaponClass);
		CurrentWeapon->SetActorEnableCollision(false);
		if (!CurrentWeapon) return;
		
		FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
		CurrentWeapon->AttachToComponent(Charachter->GetMesh(), AttachmentRules, WeaponAttachPointName);
		
	}

void UTPSWeaponComponent::Fire()
{
	if (!CurrentWeapon)return;
	CurrentWeapon->Fire();

	

}

