// Fill out your copyright notice in the Description page of Project Settings.


#include "PandaPlayerCharacter.h"

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


