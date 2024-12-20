// © 2024, Mikhail Efremov. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spawner.generated.h"

class UArrowComponent;
class USceneComponent;


UCLASS(Blueprintable)
class ARKANOID_API ASpawner : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components,
		meta = (AllowPrivateAccess = "true"))
	USceneComponent* SceneRoot;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components,
		meta = (AllowPrivateAccess = "true"))
	UArrowComponent* ForwardArrow = nullptr;

	// Идентификатор для повторяющегося таймера
	FTimerHandle TimerHandle;
	
	UPROPERTY()
	AActor* SpawnedActor = nullptr;
	
public:	
	// Sets default values for this actor's properties
	ASpawner();

protected:
	virtual void BeginPlay() override;
	
public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner | Settings")
	TSubclassOf<AActor> SpawnedActorClass = nullptr; // Класс для спавна
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner | Settings")
	float SpawnInterval = 3.0f; // Интервал спавна
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner | Settings")
	float ActorLifespan = 20.0f; // Время жизни актора

	UFUNCTION(BlueprintCallable, Category = "Spawner | Functions")
	void StartSpawning();
	UFUNCTION(BlueprintCallable, Category = "Spawner | Functions")
	void StopSpawning();
	UFUNCTION(BlueprintCallable, Category = "Spawner | Functions")
	void SpawnActor();
	
};
