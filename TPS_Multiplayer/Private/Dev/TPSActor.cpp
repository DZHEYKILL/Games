// Shoot Them Up Game

/*

#include "Dev/TPSActor.h"
#include "DrawDebugHelpers.h"

// Sets default values
ATPSActor::ATPSActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);

}

// Called when the game starts or when spawned
void ATPSActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATPSActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 24, SphereColor );
	UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, GetActorLocation(), Radius, DamageType, {}, this, NULL, DoFullDamage);

}
*/

