// © 2024, Mikhail Efremov. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LifeComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ARKANOID_API ULifeComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "LifeComponent | Settings")
	int32 Life = 1;

public:
	ULifeComponent();

	/**
	 * Устанавливает количество жизней.
	 * @param NewLife Новое количество жизней.
	 */
	void SetLife(const int32 NewLife);
	/**
	 * Фиксирует урон.
	 * @param DamageAmount Количество урона.
	 */
	void TakeDamage(const int32 DamageAmount = 1);
	UFUNCTION(BlueprintCallable)
	bool IsAlive() const;
};
