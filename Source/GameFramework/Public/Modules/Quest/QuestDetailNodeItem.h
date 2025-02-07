// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Modules/Quest/QuestDetailNode.h"
#include "Modules/Condition/CoreConditionList.h"
#include "Modules/Unit/UnitIDContainer.h"
#include "QuestDetailNodeItem.generated.h"

/**
 * 
 */
UCLASS()
class GAMEFRAMEWORK_API UQuestDetailNodeItem : public UQuestDetailNode
{
	GENERATED_UCLASS_BODY()
	
public:
	/**
	* 名字
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Quest", meta = (DisplayName = "名字"))
	FString Name;

	/**
	* 描述
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Quest", meta = (DisplayName = "描述"))
	FString Description;

	/**
	* @brief 提交NPC
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Quest", meta = (DisplayName = "提交NPC"))
	FUnitIDContainer CommitNPC;

	/**
	* 条件
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Quest", meta = (DisplayName = "条件"))
	FCoreConditionList ConditionList;

	/**
	* 任务进行中，占有NPC交谈剧情
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Quest", meta = (DisplayName = "交谈剧情"))
	TSoftObjectPtr<class UScenario> TalkingScenario;

	/**
	* 任务完成自动播放剧情
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Quest", meta = (DisplayName = "任务完成自动播放剧情"))
	bool bAutoPlayScenario = false;

	/**
	* 剧情
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Quest", meta = (DisplayName = "任务完成剧情"))
	TSoftObjectPtr<class UScenario> Scenario;

	/**
	* 奖励
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Quest", meta = (DisplayName = "奖励") )
	TArray<class UCoreReward*> Rewards;

	virtual FString GetNodeTitle_Implementation() override;
	virtual FString GetNodeTypeName_Implementation() override;

	//~ Begin UObject Interface
#if WITH_EDITOR
	virtual void PostEditImport() override;
	virtual void PostDuplicate(bool bDuplicateForPIE) override;
	virtual void PostRename(UObject* OldOuter, const FName OldName) override;
	virtual void PostLoad() override;
#endif
	// End UObject
};