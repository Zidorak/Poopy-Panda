// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstacleForAI.h"
#include "PandaPlayerCharacter.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AObstacleForAI::AObstacleForAI()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Constructs the components.
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Capsule"));
	RootComponent = BoxCollision;
	BoxCollision->SetGenerateOverlapEvents(true);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(BoxCollision);
}

// Called when the game starts or when spawned
void AObstacleForAI::BeginPlay()
{
	Super::BeginPlay();

	/* Gets the player character reference for future use and access.
	AActor* PlayerRef = UGameplayStatics::GetActorOfClass(GetWorld(), APandaPlayerCharacter::StaticClass());
	APandaPlayerCharacter PlayerCharacterRef = StaticCast<APandaPlayerCharacter>(PlayerRef); */
	
}

// Called every frame
void AObstacleForAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AObstacleForAI::CollisionHit()
{
	TArray<AActor*> Actors;
	BoxCollision->GetOverlappingActors(Actors);

	if (Actors.Num() > 0)
	{
		FString OverlappedActor = Actors[0]->GetActorNameOrLabel();
		UE_LOG(LogTemp, Display, TEXT("%s: Hit the poop"), *OverlappedActor);
		Destroy();
	}
}

void AObstacleForAI::PlayerPickupAmmo()
{
	TArray<AActor*> Actors;
	BoxCollision->GetOverlappingActors(Actors);

	if (Actors.Num() > 0)
	{
		FString OverlappedActor = Actors[0]->GetActorNameOrLabel();
		UE_LOG(LogTemp, Display, TEXT("Ammo Count"));
		Destroy();
	}
}

