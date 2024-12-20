// © 2024, Mikhail Efremov. All rights reserved.


#include "World/Spawner.h"
#include "Components/ArrowComponent.h"

ASpawner::ASpawner()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Root"));
	SetRootComponent(SceneRoot);
	
	ForwardArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Forward Arrow"));
	ForwardArrow->SetupAttachment(SceneRoot);
	//ForwardArrow->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f));
}

void ASpawner::BeginPlay()
{
	Super::BeginPlay();
	
	// Запускаем таймер для спавна актора
	StartSpawning();
}

void ASpawner::StartSpawning()
{
	if (!GetWorldTimerManager().IsTimerActive(TimerHandle))
	{
		GetWorldTimerManager().SetTimer(TimerHandle, this, &ASpawner::SpawnActor, SpawnInterval, true);
		UE_LOG(LogTemp, Warning, TEXT("Spawning started!"));
	}
}

void ASpawner::StopSpawning()
{
	if (GetWorldTimerManager().IsTimerActive(TimerHandle))
	{
		GetWorldTimerManager().ClearTimer(TimerHandle);
		UE_LOG(LogTemp, Warning, TEXT("Spawning stopped!"));
	}
}

void ASpawner::SpawnActor()
{
	if (!SpawnedActorClass)
	{
		UE_LOG(LogTemp, Error, TEXT("SpawnedActorClass is not set!"));
		return;
	}
	
	if (const auto World = GetWorld())
	{
		SpawnedActor = World->SpawnActor<AActor>(SpawnedActorClass, GetActorLocation(), GetActorRotation());

		// Ограничиваем время жизни шарика
		if (SpawnedActor)
		{
			SpawnedActor->SetLifeSpan(ActorLifespan);
		}
	}
}
