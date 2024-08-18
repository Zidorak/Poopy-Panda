// Fill out your copyright notice in the Description page of Project Settings.


#include "PoopProjectile.h"

#include "Projects.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
APoopProjectile::APoopProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Constructs the components
	sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	RootComponent = sphere;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	mesh->SetupAttachment(sphere);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));

}

// Called when the game starts or when spawned
void APoopProjectile::BeginPlay()
{
	Super::BeginPlay();

	ProjectileMovement->InitialSpeed = 1000.f;
	ProjectileMovement->MaxSpeed = 1000.f;
}

// Called every frame
void APoopProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APoopProjectile::CollisionHit()
{
	UE_LOG(LogTemp, Display, TEXT("BULLS - HIT"));
	Destroy();
}