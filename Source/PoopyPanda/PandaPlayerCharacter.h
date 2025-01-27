// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StarterCharacter.h"
#include "PandaPlayerCharacter.generated.h"

class AObstacleForAI;

UCLASS()
class POOPYPANDA_API APandaPlayerCharacter : public AStarterCharacter
{
	GENERATED_BODY()

public:
	APandaPlayerCharacter();

protected:
	virtual void BeginPlay() override;

	// Functions
	UFUNCTION(BlueprintCallable)
	void StartSprint();
	UFUNCTION(BlueprintCallable)
	void EndSprint();
	UFUNCTION(BlueprintCallable)
	void Dash();
	UFUNCTION()
	int DashCharge(float DeltaTime);
	UFUNCTION(BlueprintCallable)
	void CheckPooBarScale();
	UFUNCTION(BlueprintCallable)
	void SpawnPoop();
	UFUNCTION(BlueprintCallable)
	void ShootPoop();
	UFUNCTION(BlueprintCallable)
	void PickUp(float PickupValue);
	
	// Main Movement Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float DefaultSpeed = 350.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float SprintSpeed = 800.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	float DashDistance = 2000;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
	float PooBar = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
	float PooBarMax = 1.f;
	UPROPERTY(editanywhere, blueprintReadWrite, Category = "Player Stats")
	int32 PooAmmo = 0;
	int32 MaxPooAmmo = 3;

private:
	
	// Dash Variables
#pragma region Dash
	UPROPERTY(EditAnywhere, Category = "Boost")
	float DashOffset = 50;
	UPROPERTY(EditAnywhere, Category = "Boost")
	float DashTime = 3;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Boost", meta = (AllowPrivateAccess = "true"))
	bool DashActive = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Boost", meta = (AllowPrivateAccess = "true"))
	float DashHoldTimer = 0;;
#pragma endregion
	
	// Stamina Variables
#pragma region Stamina
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats", meta = (AllowPrivateAccess = "true"))
	float Stamina = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats", meta = (AllowPrivateAccess = "true"))
	float MaxStamina = 100.f;
	float StaminaRegenRate = 5.f;
	float StaminaExpenseRate = 15.f;
	float StaminaDelayTime = 3.f;
	bool IsSprinting = false;
#pragma endregion
	
	// Poop Spawn classes
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	USceneComponent* SpawnPoint;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> ActorToSpawn;

	// Shoot Poop Classes
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> ProjectileActorToSpawn;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* NappyRef;

	
};