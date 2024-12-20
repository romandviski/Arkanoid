// © 2024, Mikhail Efremov. All rights reserved.

#include "World/KillZone.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"

AKillZone::AKillZone()
{
PrimaryActorTick.bCanEverTick = false;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Root"));
	SetRootComponent(SceneRoot);
	
	ForwardArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Forward Arrow"));
	ForwardArrow->SetupAttachment(SceneRoot);

	KillBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Kill Box"));
	KillBox->SetupAttachment(SceneRoot);
	KillBox->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	KillBox->SetBoxExtent(FVector(50.0f, 500.0f, 50.0f));
	KillBox->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f));
	// Привязываем функцию к событию пересечения, диспатчеры подробнее посмотрим при наполнении каретки 
	if (KillBox)
	{
		KillBox->OnComponentBeginOverlap.AddDynamic(this, &AKillZone::OnKillBoxOverlap);
	}
}

void AKillZone::OnKillBoxOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	// Проверяем, что пересекший актор не является самим KillZone
	if (OtherActor && OtherActor != this)
	{
		// Проверяем, что актор не находится в списке игнорируемых
		for (const auto& IgnoredClass : IgnoredActors)
		{
			if (OtherActor->IsA(IgnoredClass))
				return; // Игнорируем актор
		}
		UE_LOG(LogTemp, Warning, TEXT("Actor %s entered the kill zone and was destroyed!"), *OtherActor->GetName());

		// Уничтожаем пересекший актор
		OtherActor->Destroy();
	}
}
