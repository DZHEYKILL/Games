// Shoot Them Up Game


#include "TPS_Charachter.h"


//DEFINE_LOG_CATEGORY_STATIC(BaseCharacterLog)

// Sets default values
ATPS_Charachter::ATPS_Charachter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;


	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArmComponent->SetupAttachment(GetMesh(), "FX_Head");
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);


	HealthComponent = CreateDefaultSubobject<UTPS_HealthComponent>("HealthComponent");

	HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthText");
	HealthTextComponent->SetupAttachment(GetRootComponent());
}



// Called when the game starts or when spawned
void ATPS_Charachter::BeginPlay()
{
	Super::BeginPlay();
	
	check(HealthComponent);
	check(HealthTextComponent);
	check(GetCharacterMovement());

	LandedDelegate.AddDynamic(this, &ATPS_Charachter::OnGroundLanded);

	//OnTakeAnyDamage.AddDynamic(this, &ATPS_Charachter::OnTakeAnyDamageHandle);

	//TakeDamage(0.1f, FDamageEvent{}, GetController(), this);

	HealthComponent->OnDeath.AddUObject(this, &ATPS_Charachter::OnDeath);
	HealthComponent->OnHealthChanged.AddUObject(this, &ATPS_Charachter::OnHealthChanged);
}

// Called every frame
void ATPS_Charachter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector Velocity = ATPS_Charachter::GetVelocity();

	//const auto Health = HealthComponent->GetHealth();
	

	//TakeDamage(0.1f, FDamageEvent{}, GetController(), this);
}

// Called to bind functionality to input
void ATPS_Charachter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{

	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward",this,&ATPS_Charachter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight",this,&ATPS_Charachter::MoveRight);

	PlayerInputComponent->BindAxis("LookUp",this,&ATPS_Charachter::LookUp);
	PlayerInputComponent->BindAxis("Turn",this,&ATPS_Charachter::Turn);

	PlayerInputComponent->BindAction("Jump", IE_Pressed,this, &ATPS_Charachter::Jump);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed,this, &ATPS_Charachter::Sprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released,this, &ATPS_Charachter::StopSprint);
}

void ATPS_Charachter::MoveForward(float Amount) 
{
	AddMovementInput(GetActorForwardVector(), Amount, false);
	ForwardButtonFloat = Amount;

}
void ATPS_Charachter::MoveRight(float Amount) 
{

	AddMovementInput(GetActorRightVector(), Amount, false);
	RightButtonFloat = Amount;

}

void ATPS_Charachter::LookUp(float Amount) 
{
	AddControllerYawInput(Amount);

}
void ATPS_Charachter::Turn(float Amount) 
{

	AddControllerPitchInput(Amount);

}

void ATPS_Charachter::Sprint()
{
	GetCharacterMovement()->MaxWalkSpeed = 900.0f;
}

void ATPS_Charachter::StopSprint()
{

	GetCharacterMovement()->MaxWalkSpeed = 750.0f;
}

void ATPS_Charachter::OnDeath() 
{

	GetCharacterMovement()->DisableMovement();

	SetLifeSpan(5.0f);

	

	if (Controller)
	{
		Controller->ChangeState(NAME_Spectating);
	}
	

}

void ATPS_Charachter::OnHealthChanged(float Health)
{
	HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
}

void ATPS_Charachter::OnGroundLanded(const FHitResult& Hit)
{
	const auto FallVelocityZ = GetCharacterMovement()->Velocity.Z;


	if (FallVelocityZ < LandedDamageVelocity.X) return;
	
	const auto FinalDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, FallVelocityZ);

	TakeDamage(FinalDamage, FDamageEvent{}, nullptr, nullptr);
}