// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstacleForAI.h"

#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "LevelInstance/LevelInstanceTypes.h"

// Sets default values
AObstacleForAI::AObstacleForAI()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Constructs the components.
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Capsule"));
	RootComponent = BoxCollision;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(BoxCollision);

}

// Called when the game starts or when spawned
void AObstacleForAI::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AObstacleForAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AObstacleForAI::CollisionHit()
{
	TArray<AActor*> Actors;
	GetOverlappingActors(Actors);

	if (Actors.Num() > 0)
	{
		LegoSteppedOn();
	}
}

void AObstacleForAI::LegoSteppedOn()
{
	UE_LOG(LogTemp, Display, TEXT("LegoSteppedOn"));
	Destroy();
}


