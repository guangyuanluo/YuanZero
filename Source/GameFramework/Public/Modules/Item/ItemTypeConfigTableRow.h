﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/ConfigTable/ConfigTableRowBase.h"
#include "Modules/Assets/BackpackTypeConfigTableRow.h"
#include "Modules/Item/ItemTypes.h"
#include "ItemTypeConfigTableRow.generated.h"

/**
* 物品类型配置表
*/
USTRUCT(BlueprintType)
struct GAMEFRAMEWORK_API FItemTypeConfigTableRow : public FConfigTableRowBase
{
	GENERATED_USTRUCT_BODY()

	/**
	* 物品类型id
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ItemTypeConfigTable", meta = (DisplayName = "物品类型Id", DisplayPriority = "1"))
	uint8 ItemTypeId;

	/**
	* 物品类型
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ItemTypeConfigTable", meta = (DisplayName = "物品类型", DisplayPriority = "1"))
	EItemTypeEnum ItemType;

	/**
	* 默认进入的背包类型
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ItemConfigTable|Hide", meta = (DisplayName = "默认进入的背包类型", DisplayPriority = "1"))
	EBackpackTypeEnum DefaultBackpackType = EBackpackTypeEnum::BackpackType_32;

    virtual int GetUniqueId() override;
	virtual int GetRowUniqueId() override;
    virtual FString GetSimpleDescription() override;
};