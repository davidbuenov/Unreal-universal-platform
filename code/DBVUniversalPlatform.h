/**
 * @file DBVUniversalPlatform.h
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


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DBVUniversalPlatform.generated.h"

UCLASS()
class CURSOUMA2_API ADBVUniversalPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADBVUniversalPlatform();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="DBV")
	bool isActive=true; // if not active will not move.
	/**
	 * Attributes related to movement
	 */

	//Calculated show current distance from origin
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="DBV|Movement")
	double Distance; 
	
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="DBV|Movement")
	double MaximumDistance; 
	
	//Calculated at the beginning. It can be changed during the game.
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="DBV|Movement")
	FVector VDirection; 

	// Set the destination of the platform used to calculate initial MaxDistance and VDirection
	UPROPERTY(EditAnywhere,Category="DBV|Movement")
	FVector Destination=FVector(0,0,500); 

	//Speed of movement
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="DBV|Movement")
	float Velocity=0.3; 

	/**
	 * Attributes related to rotation
	 */
	
	// Speed of rotation or balance
	UPROPERTY(EditAnywhere,Category="DBV|Rotation")
	FRotator RotationVelocity; 
	/**
	 * Attributes related to balance
	 */

	// if true will balance, if false will rotate
	UPROPERTY(EditAnywhere,Category="DBV|Balance")
	bool isBalance= false; 

	//Maximum Rotation Distance must be set.
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="DBV|Balance")
	double MaximumRotationDistance=180;

	// Calculated. Will change between 0 and MaxRotationDistance
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="DBV|Rotation")
	FRotator RotationDistance;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	 void MovePlatform(float DeltaTime);
	 void RotatePlatform(float DeltaTime);
	 void BalancePlatform(float DeltaTime);

	 /**
	  * Private attributes
	  * 
	  */
	 
};
