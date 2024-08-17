#include "GrabberComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UGrabberComponent::UGrabberComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabberComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UGrabberComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UPhysicsHandleComponent* PhysicsHandle =  GetPhysicsHandle();

	if (PhysicsHandle && PhysicsHandle->GetGrabbedComponent())
	{
		// Sets the distance to how far away an object should be grabbed
		FVector TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;
		PhysicsHandle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
	}
}

void UGrabberComponent::Grab()
{
	// Gets the physics handle
	UPhysicsHandleComponent *PhysicsHandle = GetPhysicsHandle();
	if(PhysicsHandle == nullptr)
	{return;}

	FHitResult HitResult;
	bool HasHit = GetGrabbableInReach(HitResult);

	// If the trace has hit, sets the physics to be activated
	if(HasHit)
	{
		//Responds to physics better by waking up rigid body
		UPrimitiveComponent* HitComponent = HitResult.GetComponent();
		HitComponent->SetSimulatePhysics(true);
		HitComponent->WakeAllRigidBodies();
		AActor* HitActor = HitResult.GetActor();
		HitActor->Tags.Add("Grabbed");
		HitActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		//Activates the grabbing physics.
		PhysicsHandle->GrabComponentAtLocationWithRotation(HitResult.GetComponent(), NAME_None, HitResult.ImpactPoint, GetComponentRotation());
	}
}

void UGrabberComponent::Release()
{
	UPhysicsHandleComponent* PhysicsHandle = UGrabberComponent::GetPhysicsHandle();

	if (PhysicsHandle && PhysicsHandle->GetGrabbedComponent())
	{
		AActor* GrabbedActor = PhysicsHandle->GetGrabbedComponent()->GetOwner();
		GrabbedActor->Tags.Remove("Grabbed");
		PhysicsHandle->ReleaseComponent();
	}
}

UPhysicsHandleComponent* UGrabberComponent::GetPhysicsHandle() const
{
	UPhysicsHandleComponent* Result = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (Result == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Grabber Requires a UphyisicsHandleComponent"))
	}
	return Result;
}

bool UGrabberComponent::GetGrabbableInReach(FHitResult& OutHitResult) const
{
	// Creates debug variables for tracing
	FVector StartTrace = GetComponentLocation();
	FVector EndTrace = StartTrace + GetForwardVector() * MaxGrabDistance;

	// Creates a sweeper sphere trace
	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);
	return  GetWorld()->SweepSingleByChannel(OutHitResult, StartTrace, EndTrace,
		FQuat::Identity,
		ECC_GameTraceChannel2,
		Sphere);
}
