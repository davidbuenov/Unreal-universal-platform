/**
 * @file DBVUniversalPlatform.cpp
 * @author David Bueno Vallejo (davidbuenov@gmail.com)
 * @brief Library that offers an Universal Platform for Unreal Engine 5 games.
 * @version 0.1
 * @date 2022-08-11
 * If you love you can contribute to the project in: https://www.paypal.com/donate/?hosted_button_id=J5DXQN5VCBTVE
 * Web of the project in Github: https://github.com/davidbuenov/Unreal-universal-platform
 *
 *
 * @copyright https://creativecommons.org/licenses/by-sa/4.0/
 *
 */

#include "DBVUniversalPlatform.h"

// Sets default values
ADBVUniversalPlatform::ADBVUniversalPlatform()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ADBVUniversalPlatform::BeginPlay()
{
	Super::BeginPlay();

	FVector Origin; // Origin of the movement, initially the Actor position.
	Origin = GetActorLocation();
	// Calculate the distance between the Actor position and the destination
	MaximumDistance = FVector::Distance(Destination, Origin);
	// Calculates the Vector of movement.
	VDirection = Destination - Origin;
	Distance = 0;
	// Initiate the Rotation Distance
	RotationDistance = FRotator(0, 0, 0);
}

// Called every frame
void ADBVUniversalPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isActive)
	{
		MovePlatform(DeltaTime);
		if (isBalance)
		{
			BalancePlatform(DeltaTime);
		}
		else
		{
			RotatePlatform(DeltaTime);
		}
	}
}
/**
 * @brief This method moves the platform using the vector VDirection
 * calculated with the initial position of the Actor and the Destination
 * The speed of movement is given by Velocity.
 * By default it will go back to the origin after reaching the destination
 * Changing the value of velocity to 0 it can be stopped
 *
 * @param DeltaTime
 */
void ADBVUniversalPlatform::MovePlatform(float DeltaTime)
{
	FVector pos = GetActorLocation();				 // Current position
	FVector inc = VDirection * Velocity * DeltaTime; // Diference with the previous frame
	// Calculate the distance between positions of the two frames.
	Distance += FVector::Distance(pos + inc, pos);
	SetActorLocation(pos+inc); // Update the position of the Actor
	
	if (Distance >= MaximumDistance)
	{
		// If the Actor reach its destination we change the Direction Vector
		VDirection = -VDirection;
		// And we set distance to 0, to begin the travel in the opposite direction
		Distance = 0;
	}
}
// The Actor rotates according to the values of Rotation Velocity.
void ADBVUniversalPlatform::RotatePlatform(float DeltaTime)
{
	// We update the rotation velocity
	AddActorLocalRotation(RotationVelocity * DeltaTime);
}
/**
 * @brief To balance the platform, the RotationVelocity should set one of the
 * three parameter to rotate by one of the axis (pitch,yaw or roll).
 * When some of them reach the MaximumRotationDistance, the rotation will reverse.
 *
 * @param DeltaTime
 */
void ADBVUniversalPlatform::BalancePlatform(float DeltaTime)
{
	RotationDistance += RotationVelocity * DeltaTime;
	AddActorLocalRotation(RotationVelocity * DeltaTime);
	// Check if the rotation has got the maximum value
	if (RotationDistance.Pitch > MaximumRotationDistance || RotationDistance.Pitch < -MaximumRotationDistance ||
		RotationDistance.Yaw > MaximumRotationDistance || RotationDistance.Yaw < -MaximumRotationDistance ||
		RotationDistance.Roll > MaximumRotationDistance || RotationDistance.Roll < -MaximumRotationDistance)
	{
		// If some of the rotations got the final RotationDistance, the Velocity is inverted.
		RotationVelocity.Pitch = -RotationVelocity.Pitch;
		RotationVelocity.Yaw = -RotationVelocity.Yaw;
		RotationVelocity.Roll = -RotationVelocity.Roll;
		RotationDistance = FRotator(0, 0, 0);
	}
}
