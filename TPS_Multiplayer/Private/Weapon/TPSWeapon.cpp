#include "Weapon/TPSWeapon.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Character.h"


//DEFINE_LOG_CATEGORY(LogWeapon);


ATPSWeapon::ATPSWeapon()
{
    PrimaryActorTick.bCanEverTick = true;

    WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
    SetRootComponent(WeaponMesh);
}


void ATPSWeapon::BeginPlay()
{
    Super::BeginPlay();
    check(WeaponMesh);
}


APlayerController* ATPSWeapon::GetPlayerController() const
{
    const auto Player = Cast<ACharacter>(GetOwner());
    if (!Player) return nullptr;

    return Player->GetController<APlayerController>();
}


void ATPSWeapon::StartFire()
{
   
    MakeShot();
    GetWorldTimerManager().SetTimer(ShotTimerHandle,this,&ATPSWeapon::MakeShot,TimeBetweenShots,true);
}


void ATPSWeapon::StopFire()
{
    GetWorldTimerManager().ClearTimer(ShotTimerHandle);
}


void ATPSWeapon::MakeShot()
{
    //if (!GetWorld) return;
    /*
    FVector TraceStart, TraceEnd;
    if (!GetTraceData(TraceStart, TraceEnd))return;

    
    FVector ViewLoction;
    FRotator ViewRotation;
    GetPlayerViewPont(ViewLoction,ViewRotation);
    

    //const FTransform SocketTransform = WeaponMesh->GetSocketTransform(MuzzleSocketName);
    const FVector TraceStart = ViewLoction;
    const FVector ShootDirection = ViewRotation.Vector();//SocketTransform.GetRotation().GetForwardVector();
    const FVector TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;

    

    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(GetOwner());
    
    FHitResult HitResult;
    (GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParams));
    */
    FVector TraceStart, TraceEnd;
    if (!GetTraceData(TraceStart, TraceEnd))return;

    FHitResult HitResult;
    MakeHit(HitResult, TraceStart, TraceEnd);

    if(HitResult.bBlockingHit)
    {
        MakeDamage(HitResult);

        DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), HitResult.ImpactPoint, FColor::Red, false, 3.0f, 0, 3.0f);
        DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 24, FColor::Red, false, 5.0f);

        //UE_LOG(LogWeapon, Display, TEXT("Bone: %s"), *HitResult.BoneName.ToString());
    }
    else
    {
        DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), TraceEnd, FColor::Red, false, 3.0f, 0, 3.0f);
    }
}


void ATPSWeapon::MakeDamage(const FHitResult& HitResult)
{
    const auto DamageActor = HitResult.GetActor();
    if (!DamageActor) return;


    const auto  Controller = GetPlayerController();
    DamageActor->TakeDamage(DamageAmount, FDamageEvent(), Controller, this);
}

bool ATPSWeapon::GetPlayerViewPont(FVector& ViewLocation, FRotator& ViewRotation) const
{
    const auto Controller = GetPlayerController();
    if (!Controller) return false;


    Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
    return true;
}

FVector ATPSWeapon::GetMuzzleWorldLocation() const 
{
    return WeaponMesh->GetSocketLocation(MuzzleSocketName);
}

bool ATPSWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
    FVector ViewLoction;
    FRotator ViewRotation;
    if(!GetPlayerViewPont(ViewLoction, ViewRotation)) return false;

    TraceStart = ViewLoction;
    const auto HalfRad = FMath::DegreesToRadians(BulletSpread);
    const FVector ShootDirection = FMath::VRandCone( ViewRotation.Vector(),HalfRad);
    TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
    return true;
}

void ATPSWeapon::MakeHit(FHitResult& HitResult, const FVector TraceStart,const FVector TraceEnd) const
{
    if (!GetWorld()) return;
    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(GetOwner());

    (GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParams));
}
