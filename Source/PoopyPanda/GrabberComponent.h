// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "GrabberComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class POOPYPANDA_API UGrabberComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabberComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void Grab();

	UFUNCTION(BlueprintCallable)
	void Release();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, Category = "Grab Mechanic")
	float MaxGrabDistance = 400;

	UPROPERTY(EditAnywhere, Category = "Grab Mechanic")
	float GrabRadius = 100;

	UPROPERTY(EditAnywhere, Category = "Grab Mechanic")
	float HoldDistance = 200;

	UPhysicsHandleComponent*  GetPhysicsHandle() const;
	bool GetGrabbableInReach(FHitResult& OutHitResult) const;
		
};
