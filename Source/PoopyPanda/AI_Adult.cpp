// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_Adult.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Actor.h"

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

	GetCharacterMovement()->MaxWalkSpeed = DefaultMovementSpeed;

	UCapsuleComponent* CapsuleCollision = AAI_Adult::GetCapsuleComponent();
}

// Called every frame
void AAI_Adult::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAI_Adult::Stunned()
{
	GetCharacterMovement()->MaxWalkSpeed = 0.0f;
}

void AAI_Adult::StunnedEnd()
{
	GetCharacterMovement()->MaxWalkSpeed = DefaultMovementSpeed;
}






