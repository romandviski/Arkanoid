// © 2024, Mikhail Efremov. All rights reserved.

#include "Components/LifeComponent.h"


ULifeComponent::ULifeComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void ULifeComponent::SetLife(const int32 NewLife)
{
	Life = FMath::Abs(NewLife);
}

void ULifeComponent::TakeDamage(const int32 DamageAmount)
{
	Life = FMath::Max(Life - DamageAmount, 0);
}

bool ULifeComponent::IsAlive() const
{
	return Life > 0;
}
