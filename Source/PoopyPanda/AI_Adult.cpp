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

	GetWorld()->GetTimerManager().SetTimer(TimerForDifficultyIncrease, this, &AAI_Adult::OnTimer, 1.0f, true);
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

void AAI_Adult::OnTimer()
{
	++TimerCount;

	switch(TimerCount)
	{
		case 1:
			if (TimerCount == 60)
			{
				StunnedTime = 2.f;
				WalkingSpeed = 250.f;
				GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed;
			}
		break;

		case 2:
			if (TimerCount == 120)
			{
				StunnedTime = 1.f;
				WalkingSpeed = 300.f;
				GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed;
			}
		break;

		case 3:
		if (TimerCount == 180)
			{
				StunnedTime = 0.2f;
				WalkingSpeed = 350.f;
				GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed;
			}
		break;
		
	default:
			break;
	}

	if(TimerCount == 310)
		{
			GetWorld()->GetTimerManager().ClearTimer(TimerForDifficultyIncrease);
		}
	
}

void AAI_Adult	::EndPlay(const EEndPlayReason::Type EndPlayReason)
{

	Super::EndPlay(EndPlayReason);
	
	GetWorld()->GetTimerManager().ClearTimer(TimerForDifficultyIncrease);
}

		
				







