// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PoopyPandaCharacter.h"
#include "PandaPlayerCharacter.generated.h"


UCLASS()
class POOPYPANDA_API APandaPlayerCharacter : public APoopyPandaCharacter
{
	GENERATED_BODY()

public:
	APandaPlayerCharacter();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void StartSprint();
	UFUNCTION(BlueprintCallable)
	void EndSprint();
	UFUNCTION(BlueprintCallable)
	void Dash();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float DefaultSpeed = 500.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float SprintSpeed = 800.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float DashDistance = 1500;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(EditAnywhere, Category = "Boost")
	float BoostOffset = 50;
	
	UPROPERTY(EditAnywhere, Category = "Boost")
	float BoostTime = 3;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Boost", meta = (AllowPrivateAccess = "true"))
	bool BoostActive = false;
};
