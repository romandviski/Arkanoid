// © 2024, Mikhail Efremov. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KillZone.generated.h"

class UArrowComponent;
class USceneComponent;
class UBoxComponent;

UCLASS(Blueprintable)
class ARKANOID_API AKillZone : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	USceneComponent* SceneRoot;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	UArrowComponent* ForwardArrow = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* KillBox = nullptr;
	
public:	
	// Sets default values for this actor's properties
	AKillZone();

protected:
	// Функция для обработки пересечения коллайдера
	UFUNCTION()
	void OnKillBoxOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "KillZone | Settings")
	TArray<TSubclassOf<AActor>> IgnoredActors;

};
