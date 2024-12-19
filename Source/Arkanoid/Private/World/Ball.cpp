// © 2024, Mikhail Efremov. All rights reserved.

#include "World/Ball.h"
#include "Components/ArrowComponent.h"


// Sets default values
ABall::ABall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Создаём компонент и настраиваем его
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	SetRootComponent(StaticMesh);
	
	// Стрелка для удобства определения направления мячика
	ForwardArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Forward Arrow"));
	ForwardArrow->SetupAttachment(StaticMesh);

	// Загружаем статичный меш сферы (заполнять лучше в блюпринтах)
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMeshAsset(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
	if (SphereMeshAsset.Succeeded())
	{
		// Устанавливаем загруженный меш в компонент StaticMesh
		StaticMesh->SetStaticMesh(SphereMeshAsset.Object);
	}
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();

	SetActorScale3D(FVector(InitParameters.Scale));
	
	Power = InitParameters.Power;
	Speed = InitParameters.Speed;
	Direction = GetActorForwardVector().GetSafeNormal();
	
	SetBallState(EBallState::Moving);
}

// Вызывается каждый кадр
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Используем switch для обработки состояния только для примера
	switch (State)
	{
	case EBallState::Idle:
		break;
	case EBallState::Moving:
			Move(DeltaTime);
		break;
	default:
			// Действия по умолчанию, если состояние не определено
			UE_LOG(LogTemp, Error, TEXT("Unknown Ball State"));
		break;
	}
}

void ABall::Move(const float DeltaTime)
{
	const FVector Offset = Direction * Speed * DeltaTime;
	FHitResult HitResult;
	AddActorWorldOffset(Offset, true, &HitResult); // true для проверки столкновений

	// Проверяем столкновения
	if (HitResult.bBlockingHit)
	{
		/*
			Формула для вычисления отраженного вектора выглядит так:
			ReflectedDirection = Direction − 2 * (Direction ⋅ Normal) * Normal
			(в выражении (Direction ⋅ Normal) используется скалярное произведение!)
		*/
		Direction = Direction - 2 * (FVector::DotProduct(Direction, HitResult.Normal)) * HitResult.Normal;
		Direction.Z = 0.f;
		Direction = Direction.GetSafeNormal(); // Нормализуем вектор

		// Увеличиваем скорость, если она меньше максимальной
		if (Speed < InitParameters.MaxSpeed)
		{
			Speed += InitParameters.Speed * 0.1f;
			Speed = FMath::Min(Speed, InitParameters.MaxSpeed); // Ограничиваем скорость максимальным значением
		}

		// выведем скорость для дебага
		// https://www.chrismccole.com/blog/logging-in-ue4-cpp
		// https://unrealcommunity.wiki/logging-lgpidy6i
		UE_LOG(LogTemp, Warning, TEXT("Ball name %s is speed %f"), *GetName(), Speed);
	}
}

void ABall::SetBallState(const EBallState NewState)
{
	State = NewState;
}
