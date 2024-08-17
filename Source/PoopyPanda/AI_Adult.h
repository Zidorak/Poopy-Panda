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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
private:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI Targeting", meta = (AllowPrivateAccess = "true"))
	AActor* TargetActor;
};
