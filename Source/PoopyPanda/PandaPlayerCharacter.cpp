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
}

void APandaPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (BoostActive == true)
	{
		FVector CurrentLocation = GetActorLocation();
		FVector TargetLocation = GetTransform().GetRotation().GetForwardVector() + BoostOffset;
		float speed = FVector::Distance(CurrentLocation, TargetLocation) / BoostTime;

		FVector NewLocation = FMath::VInterpTo(CurrentLocation, TargetLocation, DeltaTime, speed);
		SetActorLocation(NewLocation, true);
	}
}

void APandaPlayerCharacter::StartSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}

void APandaPlayerCharacter::EndSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = DefaultSpeed;
}

void APandaPlayerCharacter::Dash()
{
	const FVector ForwardDir = this->GetActorRotation().Vector();
	LaunchCharacter(ForwardDir * DashDistance, true, true);
}


