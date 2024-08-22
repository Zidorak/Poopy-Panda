// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AI_Adult.generated.h"

UCLASS()
class POOPYPANDA_API AAI_Adult : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAI_Adult();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	void Stunned();
	UFUNCTION(BlueprintCallable)
	void StunnedEnd();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float StunnedTime = 3.f;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
    	float WalkingSpeed = 200;
	
private:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI Targeting", meta = (AllowPrivateAccess = "true"))
	AActor* TargetActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Movement", meta = (AllowPrivateAccess = "true"))
	float DefaultMovementSpeed = 250.f;

	// Function varaibles for timer;
	FTimerHandle TimerForDifficultyIncrease;
	int32 TimerCount = 0;
	void OnTimer();
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

};

