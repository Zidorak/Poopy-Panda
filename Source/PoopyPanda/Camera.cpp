// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera.h"

#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ACamera::ACamera()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACamera::BeginPlay()
{
	Super::BeginPlay();
	
	USceneComponent* LensCoverSpawnPoint = GetOwner()->FindComponentByClass<USceneComponent>();
	SpawnPointRef = LensCoverSpawnPoint;
}

// Called every frame
void ACamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACamera::CoveredInPoop()
{
	const FVector SpawnLocation = SpawnPointRef->GetComponentLocation();
	const FRotator SpawnRotation = SpawnPointRef->GetComponentRotation();
	GetWorld()->SpawnActor<AActor>(LensCoverActor, SpawnLocation, SpawnRotation);
}

