// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Modules/Condition/CoreCondition.h"
#include "Modules/Money/MoneyTypeNumPair.h"
#include "PlayerDeductMoneyCondition.generated.h"

/**
 * 玩家扣除货币
 */
UCLASS(BlueprintType, meta = (DisplayName = "玩家扣除货币", Category = "任务条件"))
class GAMEFRAMEWORK_API UPlayerDeductMoneyCondition : public UCoreCondition
{
public:
	GENERATED_UCLASS_BODY()

	/**
	* 货币
	*/
	UPROPERTY(Category = "ConditionSystem", EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "扣除货币"))
	TArray<FMoneyTypeNumPair> Money;
};
