// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_Adult.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/MovementComponent.h"

// Sets default values
AAI_Adult::AAI_Adult()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAI_Adult::BeginPlay()
{
	Super::BeginPlay();
	
	DrawDebugSphere(GetWorld(), GetActorLocation(), 1000, 20, FColor::Red, true, -1);

	//GetCharacterMovement()->MaxWalkSpeed = xxf
}

// Called every frame
void AAI_Adult::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


