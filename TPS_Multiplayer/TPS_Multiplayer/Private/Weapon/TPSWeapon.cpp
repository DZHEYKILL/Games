#include "Weapon/TPSWeapon.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Character.h"


DEFINE_LOG_CATEGORY(LogWeapon);

// �����������: ��������� �������� �� ���������
ATPSWeapon::ATPSWeapon()
{
    PrimaryActorTick.bCanEverTick = true;

    WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
    SetRootComponent(WeaponMesh);
}

// ����� BeginPlay
void ATPSWeapon::BeginPlay()
{
    Super::BeginPlay();
    check(WeaponMesh);
}

// ��������� ����������� ������
APlayerController* ATPSWeapon::GetPlayerController() const
{
    const auto Player = Cast<ACharacter>(GetOwner());
    if (!Player) return nullptr;

    return Player->GetController<APlayerController>();
}

// ������ ��������
void ATPSWeapon::StartFire()
{
    MakeShot();
    // ���� ����� �������� ������ ��� ������������� ���������:
    // GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ATPSWeapon::MakeShot, TimeBetweenShots, true);
}

// ��������� ��������
void ATPSWeapon::StopFire()
{
    GetWorldTimerManager().ClearTimer(ShotTimerHandle);
}

// ������ ������ ��������
void ATPSWeapon::MakeShot()
{
    //if (!GetWorld) return;

    const auto Player = Cast<ACharacter>(GetOwner());
    if (!Player) return;

    const auto Controller = Player->GetController<APlayerController>();
    if (!Controller) return;

    FVector ViewLoction;
    FRotator ViewRotation;
    Controller->GetPlayerViewPoint(ViewLoction,ViewRotation);
    // ��������� ������������� �������� �����
    const FTransform SocketTransform = WeaponMesh->GetSocketTransform(MuzzleSocketName);
    const FVector TraceStart = ViewLoction;
    const FVector ShootDirection = ViewRotation.Vector();//SocketTransform.GetRotation().GetForwardVector();
    const FVector TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;

    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(GetOwner());
    
    FHitResult HitResult;
    if (GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility))
    {
        // ��������� �����
        MakeDamage(HitResult);

        // ��������� ����� ���������
        DrawDebugLine(GetWorld(), SocketTransform.GetLocation(), HitResult.ImpactPoint, FColor::Red, false, 3.0f, 0, 3.0f);
        DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 24, FColor::Red, false, 5.0f);

        UE_LOG(LogWeapon, Display, TEXT("Bone: %s"), *HitResult.BoneName.ToString());
    }
    else
    {
        DrawDebugLine(GetWorld(), SocketTransform.GetLocation(), TraceEnd, FColor::Red, false, 3.0f, 0, 3.0f);
    }
}

// ��������� �����
void ATPSWeapon::MakeDamage(const FHitResult& HitResult)
{
    const auto DamageActor = HitResult.GetActor();
    if (!DamageActor) return;


    const auto  Controller = GetPlayerController();
    DamageActor->TakeDamage(DamageAmount, FDamageEvent(), GetPlayerController(), this);
}
