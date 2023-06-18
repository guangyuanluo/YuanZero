// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Modules/Condition/CoreCondition.h"
#include "Modules/Unit/UnitIDContainer.h"
#include "CloseToNPCCondition.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, meta = (DisplayName = "靠近NPC"))
class GAMEFRAMEWORK_API UCloseToNPCCondition : public UCoreCondition
{
public:
	GENERATED_UCLASS_BODY()

	/**
	* @brief 靠近哪个npc
	*/
	UPROPERTY(Category = "ConditionSystem", EditAnywhere, BlueprintReadWrite)
	FUnitIDContainer UnitIDContainer;

	/**
	* @brief 半径
	*/
	UPROPERTY(Category = "ConditionSystem", EditAnywhere, BlueprintReadWrite)
	float Radius;
};
