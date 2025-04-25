#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "MonsterStat.generated.h"

USTRUCT(BlueprintType)
struct FMonsterStat : public FTableRowBase
{
	GENERATED_BODY()

public:
	FMonsterStat() : Attack(0.0f)
	{
		;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float Attack;

	FMonsterStat operator+(const FMonsterStat& Other) const
	{
		const float* const ThisPtr = reinterpret_cast<const float* const>(this);
		const float* const OtherPtr = reinterpret_cast<const float* const>(&Other);

		FMonsterStat Result;
		float* ResultPtr = reinterpret_cast<float*>(&Result);
		int32 StatNum = sizeof(FMonsterStat) / sizeof(float);
		for (int32 i = 0; i < StatNum; i++)
		{
			ResultPtr[i] = ThisPtr[i] + OtherPtr[i];
		}

		return Result;
	}
};
