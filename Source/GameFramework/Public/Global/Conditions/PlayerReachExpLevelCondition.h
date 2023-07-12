// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Modules/Condition/CoreCondition.h"
#include "Modules/Exp/ExpTypeContainer.h"
#include "PlayerReachExpLevelCondition.generated.h"

/**
 * 玩家达到经验等级条件
 */
UCLASS(BlueprintType, meta = (DisplayName = "玩家达到经验等级", Category = "通用条件"))
class GAMEFRAMEWORK_API UPlayerReachExpLevelCondition : public UCoreCondition
{
public:
	GENERATED_UCLASS_BODY()

	/**
	* 经验类型
	*/
	UPROPERTY(Category = "ConditionSystem", EditAnywhere, BlueprintReadWrite)
	FExpTypeContainer ExpTypeContainer;

	/**
	* 经验等级
	*/
	UPROPERTY(Category = "ConditionSystem", EditAnywhere, BlueprintReadWrite)
	int32 ExpLevel;
};
