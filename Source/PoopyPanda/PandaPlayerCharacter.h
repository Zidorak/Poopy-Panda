// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PoopyPandaCharacter.h"
#include "PandaPlayerCharacter.generated.h"

class AObstacleForAI;

UCLASS()
class POOPYPANDA_API APandaPlayerCharacter : public APoopyPandaCharacter
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
	UFUNCTION(BlueprintCallable)
	int DashCharge(float DeltaTime);
	UFUNCTION(BlueprintCallable)
	void CheckScoreForMovement();
	UFUNCTION(BlueprintCallable)
	void SpawnPoop();

	// Main Movement Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float DefaultSpeed = 350.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float SprintSpeed = 800.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float DashDistance = 2000;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats", meta = (AllowPrivateAccess = "true"))
	float PooBar = 0.f;
	
	// Dash Variables
#pragma region Dash
	UPROPERTY(EditAnywhere, Category = "Boost")
	float DashOffset = 50;
	UPROPERTY(EditAnywhere, Category = "Boost")
	float DashTime = 3;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Boost", meta = (AllowPrivateAccess = "true"))
	bool DashActive = false;
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

	
	
};