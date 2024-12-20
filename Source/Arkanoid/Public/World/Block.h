// © 2024, Mikhail Efremov. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Block.generated.h"

class ULifeComponent;

UCLASS()
class ARKANOID_API ABlock : public AActor
{
	GENERATED_BODY()

private:
	// Переменные указатели под части нашего актора
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components,
		meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMesh = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components,
		meta = (AllowPrivateAccess = "true"))
	ULifeComponent* LifeComponent = nullptr;

	// Переменные для работы с нашим актором
	TSubclassOf<AActor> BonusClass = nullptr;
	
public:	
	ABlock();

protected:
	// Функция для обработки столкновения
	UFUNCTION()
	void OnStaticMeshHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:	
	void Init(const FVector NewScale, const int32 LifeAmount,
		const TSubclassOf<AActor> NewBonusClass = nullptr);
	
};
