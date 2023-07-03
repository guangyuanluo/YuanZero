// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Modules/Condition/CoreCondition.h"
#include "Modules/Condition/CoreConditionList.h"
#include "Modules/Condition/CoreConditionProgress.h"
#include "CoreConditionGroup.generated.h"

/**
 * 条件组
 */
UCLASS(BlueprintType, meta = (DisplayName = "条件组"))
class GAMEFRAMEWORK_API UCoreConditionGroup : public UCoreCondition {
public:
	GENERATED_UCLASS_BODY()

	/**
	* @brief 子条件
	*/
	UPROPERTY(Category = "ConditionSystem", EditAnywhere, BlueprintReadWrite)
	FCoreConditionList ConditionList;

	virtual class UCoreConditionProgress* GenerateConditionProgress(AActor* ProgressOwner) override;
	//~ Begin UObject Interface
#if WITH_EDITOR
	virtual void PostEditImport() override;
	virtual void PostDuplicate(bool bDuplicateForPIE) override;
#endif
	// End UObject
};

/**
 * 条件组进度
 */
UCLASS(BlueprintType)
class GAMEFRAMEWORK_API UCoreConditionGroupProgress : public UCoreConditionProgress {
public:
	GENERATED_BODY()

	virtual void OnInitialize_Implementation() override;
	virtual void OnUninitialize_Implementation() override;
	virtual bool IsComplete_Implementation(bool& IsValid) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void GetProgressesWithChildren(TArray<UCoreConditionProgress*>& OutProgresses) override;

private:
	friend class UCoreConditionGroup;

	UPROPERTY(ReplicatedUsing = OnRep_ChildProgresses)
	TArray<UCoreConditionProgress*> ChildProgresses;

	UFUNCTION()
	void OnChildConditionSatisfyChange(UCoreConditionProgress* Progress, bool NewSatisfy);

	UFUNCTION()
	void OnChildProgressPostNetReceive(UCoreConditionProgress* Progress);

	UFUNCTION()
	void OnRep_ChildProgresses(const TArray<UCoreConditionProgress*>& OldChildProgresses);
};