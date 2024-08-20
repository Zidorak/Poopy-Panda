// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterTRUE.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
APlayerCharacterTRUE::APlayerCharacterTRUE()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Constructs Scene components for spawning actors
	SpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Poop Spawn Point"));
	SpawnPoint->SetupAttachment(RootComponent);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void APlayerCharacterTRUE::BeginPlay()
{
	Super::BeginPlay();

	// Gets a ref to the nappy component
	NappyRef = this->FindComponentByTag<UStaticMeshComponent>(TEXT("Nappy"));
	
}

// Called every frame
void APlayerCharacterTRUE::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(CheckNappyNow == true)
	{
		CheckPooBarScale();
	}
	

	// If the stamina is less than max and not sprinting, does a short delay before interpolating the stamina back to max
	if (Stamina < MaxStamina && IsSprinting == false)
	{
		StaminaDelayTime -= 1 * DeltaTime;
		if(StaminaDelayTime <= 0)
		{
			StaminaDelayTime = 0;
			Stamina = FMath::FInterpConstantTo(Stamina, MaxStamina, DeltaTime, StaminaRegenRate);
			UE_LOG(LogTemp, Display, TEXT("Stamina Remaining: %f"), Stamina);
		}
	}

	// If player is charging dash, calls the function to generate the float timer
	if(DashActive == true && PooBar >= 0.20)
	{DashCharge(DeltaTime);}

}

// Called to bind functionality to input
void APlayerCharacterTRUE::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlayerCharacterTRUE::StartSprint()
{
	if(Stamina > 0)
	{
		// Sets the max walk speed higher if sprinting, and interpolates the stamina by the usage. 
		IsSprinting = true;
		StaminaDelayTime = 3.f;
		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
		Stamina = FMath::FInterpConstantTo(Stamina, 0.0f, GetWorld()->GetDeltaSeconds(), StaminaExpenseRate);
	}
	else
	{
		EndSprint();
	}
	
}

void APlayerCharacterTRUE::EndSprint()
{
	IsSprinting = false;
	GetCharacterMovement()->MaxWalkSpeed = DefaultSpeed;
}

int APlayerCharacterTRUE::DashCharge(float DeltaTime)
{
	// When held, the timer will go up determining how much charge you will get
	DashHoldTimer = DashHoldTimer + 1 * DeltaTime;
	UE_LOG(LogTemp, Display, TEXT("Held For: %f"), DashHoldTimer);
	
	return DashHoldTimer;
}

void APlayerCharacterTRUE::Dash()
{
	DashActive = false;
	const FVector ForwardDir = this->GetActorRotation().Vector();

	// If tapped, sets to the first case, and Caps the timer to 5 seconds if held for longer.
	if(DashHoldTimer > 5)
	{
		DashHoldTimer = 5 ;
	}

	// Converts the delta time float into an int and puts it into a switch.
	switch ((int32)DashHoldTimer)
	{
	case 1:
		if(PooBar >= 0.20)
		{
			DashDistance = 1000;
			PooBar -= 0.20;
			LaunchCharacter(ForwardDir * DashDistance, true, true);
		}
		break;

	case 2:
		if(PooBar >= 0.40)
		{
			DashDistance = 1500;
			PooBar -= 0.40;
			LaunchCharacter(ForwardDir * DashDistance, true, true);
		}
		break;

	case 3:
		if(PooBar >= 0.60)
		{
			DashDistance = 2000;
			PooBar -= 0.60;
			LaunchCharacter(ForwardDir * DashDistance, true, true);
		}
		break;

	case 4:
		if(PooBar >= 0.80)
		{
			DashDistance = 2500;
			PooBar -= 0.80;
			LaunchCharacter(ForwardDir * DashDistance, true, true);
		}
		break;

	case 5:
		if (PooBar == 1)
		{
			DashDistance = 3000;
			PooBar -= 1;
			LaunchCharacter(ForwardDir * DashDistance, true, true);
		}
		break;

		default:
		return;
	}
	DashHoldTimer = 0.f;
} 

void APlayerCharacterTRUE::CheckPooBarScale()
{
	const FVector CurrentNappyScale = NappyRef->GetComponentScale();
	
		if (PooBar <= 0.33)
		{
			NappyRef->SetStaticMesh(Nappy1);
		
			UE_LOG(LogTemp, Display, TEXT("Nappy Set to Small"));
		}
	
		if(PooBar >= 0.34 && PooBar <= 0.66)
		{
			NappyRef->SetStaticMesh(Nappy2);
			
			UE_LOG(LogTemp, Display, TEXT("Nappy Set to Med"));
		}
	
		if(PooBar >= 0.67)
		{
			NappyRef->SetStaticMesh(Nappy3);
			
			UE_LOG(LogTemp, Display, TEXT("Nappy Set to Large"));
		}
}

void APlayerCharacterTRUE::SpawnPoop()
{
	if(PooBar >= 0.20)
	{
		const FVector SpawnLocation = SpawnPoint->GetComponentLocation();
		const FRotator SpawnRotation = SpawnPoint->GetComponentRotation();
		GetWorld()->SpawnActor<AActor>(ActorToSpawn, SpawnLocation, SpawnRotation);
		PooBar -= 0.20f;;
	}
}

void APlayerCharacterTRUE::ShootPoop()
{
	if(PooAmmo > 0)
	{
		const FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
		const FRotator SpawnRotation = ProjectileSpawnPoint->GetComponentRotation();
		GetWorld()->SpawnActor<AActor>(ProjectileActorToSpawn, SpawnLocation, SpawnRotation);
		PooAmmo -= 1;

		UE_LOG(LogTemp, Display, TEXT("Ammo Left %i"), PooAmmo);
	}
}

void APlayerCharacterTRUE::PickUp(float PickupValue)
{
	PooBar += PickupValue;

	if(PooBar > 1)
	{
		PooBar = PooBarMax;
	}
}

