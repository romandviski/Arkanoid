// © 2024, Mikhail Efremov. All rights reserved.


#include "World/Block.h"
#include "Components/LifeComponent.h"

ABlock::ABlock()
{
	PrimaryActorTick.bCanEverTick = false;
	// Создаём компонент и настраиваем его
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh")); 
	SetRootComponent(StaticMesh);

	LifeComponent = CreateDefaultSubobject<ULifeComponent>(TEXT("Life Component")); 
	
	StaticMesh->OnComponentHit.AddDynamic(this, &ABlock::OnStaticMeshHit);
}

void ABlock::OnStaticMeshHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor != this) // Проверяем, что столкновение произошло с другим актором
	{
		if (BonusClass)
		{
			GetWorld()->SpawnActor<AActor>(BonusClass, GetActorLocation(), GetActorRotation());
		}
		
		Destroy();
	}	
}

void ABlock::Init(const FVector NewScale, const int32 LifeAmount, const TSubclassOf<AActor> NewBonusClass)
{
	SetActorScale3D(NewScale);
	BonusClass = NewBonusClass;
}
