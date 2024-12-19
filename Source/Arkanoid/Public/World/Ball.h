// © 2024, Mikhail Efremov. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ball.generated.h"

class UStaticMeshComponent;
class UArrowComponent;

// Используем enum только для примера, легко заменяется на bool
UENUM(BlueprintType)
enum class EBallState : uint8
{
	Idle,       // Шарик находится на ракетке
	Moving,     // Шарик движется
};

USTRUCT(BlueprintType)
struct FInitParameters
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, meta = (ToolTip = "Стартовый размер"))
	float Scale;
	UPROPERTY(EditDefaultsOnly, meta = (ToolTip = "Начальная сила"))
	int32 Power;
	UPROPERTY(EditDefaultsOnly, meta = (ToolTip = "Начальная скорость"))
	float Speed;
	UPROPERTY(EditDefaultsOnly, meta = (ToolTip = "Максимальная скорость"))
	float MaxSpeed;

	// Конструктор структуры по умолчанию
	FInitParameters()
	{
		Scale  = 1.0f;
		Power = 1;
		Speed = 500.0f;
		MaxSpeed = 2500.0f;
	}
};

UCLASS(Blueprintable)
class ARKANOID_API ABall : public AActor
{
	GENERATED_BODY()

private:
	// Переменные указатели под части нашего актора
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMesh = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	UArrowComponent* ForwardArrow = nullptr;

	// Переменные для работы
	int32 Power = 1;
	float Speed = 0.0f;
	FVector Direction = FVector::ZeroVector;
	EBallState State = EBallState::Idle;
	
public:	
	ABall();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ball | Settings")
	FInitParameters InitParameters;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	/**
	 * Функция для обработки движения шарика.
	 * @param DeltaTime Время, прошедшее с последнего кадра.
	 */
	void Move(const float DeltaTime);
	/**
	 * Функция для смены статуса шарика.
	 * @param NewState Новый назначаемый мячику статус.
	 */
	void SetBallState(const EBallState NewState);
};
