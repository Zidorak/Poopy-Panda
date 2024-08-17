// Fill out your copyright notice in the Description page of Project Settings.


#include "PandaPlayerCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

APandaPlayerCharacter::APandaPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APandaPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	Stamina = 100.f;
}

void APandaPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
}

void APandaPlayerCharacter::StartSprint()
{
	if(Stamina > 0)
	{
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

void APandaPlayerCharacter::Dash()
{
	if (PooBar >= 25)
	{
		const FVector ForwardDir = this->GetActorRotation().Vector();
		LaunchCharacter(ForwardDir * DashDistance, true, true);
		PooBar -= 25;

		UE_LOG(LogTemp, Display, TEXT("Poo Bar Remaining: %f"), PooBar);
	}
}



