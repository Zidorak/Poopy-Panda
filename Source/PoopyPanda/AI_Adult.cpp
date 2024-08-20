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
	UE_LOG(LogTemp, Log, TEXT("Timer Tick: %d"), TimerCount);

	switch(TimerCount)
	{
		case 1:
			if (TimerCount == 60)
			{
				GetCharacterMovement()->MaxWalkSpeed = 300.0f;
				UE_LOG(LogTemp, Display, TEXT("Set Speed to min"));
			}
		break;

		case 2:
			if (TimerCount == 180)
			{
				GetCharacterMovement()->MaxWalkSpeed = 350.0f;
				UE_LOG(LogTemp, Display, TEXT("Set Speed to med"));
			}
		break;

		case 3:
		if (TimerCount == 300)
			{
				GetCharacterMovement()->MaxWalkSpeed = 400.0f;
			UE_LOG(LogTemp, Display, TEXT("Set Speed to high"));
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

		
				







