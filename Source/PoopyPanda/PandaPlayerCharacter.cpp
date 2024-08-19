// Fill out your copyright notice in the Description page of Project Settings.

#include "PandaPlayerCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "engine/Blueprint.h"
#include "engine/World.h"
#include "editor/EditorEngine.h"
#include "Math/UnrealMathUtility.h"

// Generator
APandaPlayerCharacter::APandaPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Constructs Scene components for spawning actors
	SpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Poop Spawn Point"));
	SpawnPoint->SetupAttachment(RootComponent);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(RootComponent);
}

// Begin Play
void APandaPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Gets a ref to the nappy component
	NappyRef = this->FindComponentByTag<UStaticMeshComponent>(TEXT("Nappy"));
}

// Tick
void APandaPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckPooBarScale();

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
	if(DashActive == true && PooBar >= 0.25)
	{DashCharge(DeltaTime);}
}

void APandaPlayerCharacter::StartSprint()
{
	if(Stamina > 0)
	{
		// Sets the max walk speed higher if sprinting, and interpolates the stamina by the usage. 
		IsSprinting = true;
		StaminaDelayTime = 3.f;
		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
		Stamina = FMath::FInterpConstantTo(Stamina, 0.0f, GetWorld()->GetDeltaSeconds(), StaminaExpenseRate);
		UE_LOG(LogTemp, Display, TEXT("Stamina Remaining: %f"), Stamina)
	}
	else
	{
		EndSprint();
	}
	
}

void APandaPlayerCharacter::EndSprint()
{
	IsSprinting = false;
	GetCharacterMovement()->MaxWalkSpeed = DefaultSpeed;
}

int APandaPlayerCharacter::DashCharge(float DeltaTime)
{
	// When held, the timer will go up determining how much charge you will get
	DashHoldTimer = DashHoldTimer + 1 * DeltaTime;
	UE_LOG(LogTemp, Display, TEXT("Held For: %f"), DashHoldTimer);
	
	return DashHoldTimer;
}

void APandaPlayerCharacter::Dash()
{
	DashActive = false;
	const FVector ForwardDir = this->GetActorRotation().Vector();

	// If tapped, sets to the first case, and Caps the timer to 5 seconds if held for longer.
	if(DashHoldTimer > 5)
	{
		DashHoldTimer = 5;
	}
	if(DashHoldTimer < 1 && DashHoldTimer > 0.1)
	{
		DashHoldTimer = 1;
	}
	
	// Converts the delta time float into an int and puts it into a switch.
	switch ((int32)DashHoldTimer)
	{
	case 1:
		if(PooBar >= 0.20)
		{
			DashDistance = 500;
			PooBar -= 0.20;
			LaunchCharacter(ForwardDir * DashDistance, true, true);
		}
		break;

	case 2:
		if(PooBar >= 0.40)
		{
			DashDistance = 1000;
			PooBar -= 0.40;
			LaunchCharacter(ForwardDir * DashDistance, true, true);
		}
		break;

	case 3:
		if(PooBar >= 0.60)
		{
			DashDistance = 1500;
			PooBar -= 0.60;
			LaunchCharacter(ForwardDir * DashDistance, true, true);
		}
		break;

	case 4:
		if(PooBar >= 0.80)
		{
			DashDistance = 2000;
			PooBar -= 0.80;
			LaunchCharacter(ForwardDir * DashDistance, true, true);
		}
		break;

	case 5:
		if (PooBar >= 1)
		{
			DashDistance = 2500;
			PooBar -= 1;
			LaunchCharacter(ForwardDir * DashDistance, true, true);
		}
		break;

		default:
			DashDistance = 0;
		return;
	}
	DashHoldTimer = 0.f;

	UE_LOG(LogTemp, Display, TEXT("Poo Bar Remaining: %f"), PooBar);
} 

void APandaPlayerCharacter::CheckPooBarScale()
{
	FVector CurrentNappyScale = NappyRef->GetComponentScale();
	UE_LOG(LogTemp, Display, TEXT("Nappy Switch Activated"));
	
		if (PooBar <= 0.33)
		{
			FVector NappyScaleSmall = FVector(0.20f, 0.20f, 0.20f);
			FVector NewScaleSmall = FMath::VInterpConstantTo(CurrentNappyScale, NappyScaleSmall, GetWorld()->GetDeltaSeconds(), 2.f);
			NappyRef->SetRelativeScale3D(NewScaleSmall);
			FVector NewLocation = FVector(48.69, 0, -0.4255);
			NappyRef->SetRelativeLocation(NewLocation, false);
			UE_LOG(LogTemp, Display, TEXT("Nappy Set to Small"));
		}
	
		if(PooBar >= 0.34 && PooBar <= 0.66)
		{
			FVector NappyScaleMedium = FVector(0.2625f, 0.2625f, 0.2625f);
			FVector NewScaleMedium = FMath::VInterpConstantTo(CurrentNappyScale, NappyScaleMedium, GetWorld()->GetDeltaSeconds(), 2.f);
			NappyRef->SetRelativeScale3D(NewScaleMedium);
			UE_LOG(LogTemp, Display, TEXT("Nappy Set to Med"));
		}
	
		if(PooBar >= 0.67)
		{
			FVector NappyScaleLarge = FVector(0.457f, 0.4f, 0.4f);
			FVector NewScaleLarge = FMath::VInterpConstantTo(CurrentNappyScale, NappyScaleLarge, GetWorld()->GetDeltaSeconds(), 2.f);
			NappyRef->SetRelativeScale3D(NewScaleLarge);
			FVector NewLocation = FVector(33.92, 0, -0.425);
			NappyRef->SetRelativeLocation(NewLocation, false);
			UE_LOG(LogTemp, Display, TEXT("Nappy Set to Large"));
		}
}

void APandaPlayerCharacter::SpawnPoop()
{
	if(PooBar >= 0.20)
	{
		const FVector SpawnLocation = SpawnPoint->GetComponentLocation();
		const FRotator SpawnRotation = SpawnPoint->GetComponentRotation();
		GetWorld()->SpawnActor<AActor>(ActorToSpawn, SpawnLocation, SpawnRotation);
		PooBar -= 0.20f;

		UE_LOG(LogTemp, Display, TEXT("Poop Spawned"));
	}
}

void APandaPlayerCharacter::ShootPoop()
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

void APandaPlayerCharacter::PickUp(float PickupValue)
{
	PooBar += PickupValue;

	if(PooBar > 1)
	{
		PooBar = PooBarMax;
	}
}

