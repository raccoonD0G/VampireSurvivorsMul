#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "CharacterStat.generated.h"

USTRUCT(BlueprintType)
struct FCharacterStat : public FTableRowBase
{
	GENERATED_BODY()

public:
	FCharacterStat() : MaxHp(0.0f), MovementSpeed(0.0)
	{
		;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float MaxHp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float MovementSpeed;

	FCharacterStat operator+(const FCharacterStat& Other) const
	{
		const float* const ThisPtr = reinterpret_cast<const float* const>(this);
		const float* const OtherPtr = reinterpret_cast<const float* const>(&Other);

		FCharacterStat Result;
		float* ResultPtr = reinterpret_cast<float*>(&Result);
		int32 StatNum = sizeof(FCharacterStat) / sizeof(float);
		for (int32 i = 0; i < StatNum; i++)
		{
			ResultPtr[i] = ThisPtr[i] + OtherPtr[i];
		}

		return Result;
	}
};
