// Fill out your copyright notice in the Description page of Project Settings.

#include "CoreConditionGroup.h"
#include "CoreConditionProgress.h"
#include "Engine/ActorChannel.h"
#include "Net/UnrealNetwork.h"
#include "BooleanAlgebraUtil.h"

UCoreConditionGroup::UCoreConditionGroup(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    ProgressClass = UCoreConditionGroupProgress::StaticClass();
}

class UCoreConditionProgress* UCoreConditionGroup::GenerateConditionProgress(AActor* ProgressOwner) {
    auto ConditionGroupProgress = Cast<UCoreConditionGroupProgress>(Super::GenerateConditionProgress(ProgressOwner));
    
    for (int Index = 0; Index < ConditionList.Conditions.Num(); ++Index) {
        auto ChildCondition = ConditionList.Conditions[Index];
        ConditionGroupProgress->ChildProgresses.Add(ChildCondition->GenerateConditionProgress(ProgressOwner));
    }

    return ConditionGroupProgress;
}

void UCoreConditionGroupProgress::OnStart_Implementation() {
    Super::OnStart_Implementation();
    
    for (auto ChildProgress : ChildProgresses) {
        ChildProgress->OnConditionProgressSatisfyUpdate.AddDynamic(this, &UCoreConditionGroupProgress::OnChildConditionSatisfyChange);
    }

    for (auto ChildProgress : ChildProgresses) {
        ChildProgress->OnStart();
    }
}

void UCoreConditionGroupProgress::OnEnd_Implementation() {
    Super::OnEnd_Implementation();

    for (auto ChildProgress : ChildProgresses) {
        ChildProgress->OnConditionProgressSatisfyUpdate.RemoveDynamic(this, &UCoreConditionGroupProgress::OnChildConditionSatisfyChange);
    }

    for (auto ChildProgress : ChildProgresses) {
        ChildProgress->OnEnd();
    }
}

bool UCoreConditionGroupProgress::IsComplete_Implementation() {
    bool HaveComplete = true;

    TArray<BooleanAlgebraEnum> LoopGroupRelations;
    for (auto ChildProgress : ChildProgresses) {
        if (!ChildProgress) {
            return false;
        }
        LoopGroupRelations.Add(ChildProgress->Condition->Relation);
    }
    FBooleanAlgebraNodeInfo GroupExecuteRoot = UBooleanAlgebraUtil::RelationsGenerate(LoopGroupRelations);
    TFunction<bool(int)> CheckFunction = [this](int ProgressIndex) {
        auto Progress = ChildProgresses[ProgressIndex];
        auto Condition = Progress->Condition;

        bool bLastSatisfy = Progress->IsComplete();
        return bLastSatisfy != Condition->bNot;
    };

    HaveComplete = UBooleanAlgebraUtil::ExecuteConditionRelationTree(GroupExecuteRoot, CheckFunction);

    return HaveComplete;
}

void UCoreConditionGroupProgress::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    FDoRepLifetimeParams Params;
    Params.Condition = COND_OwnerOnly;

    DOREPLIFETIME_WITH_PARAMS_FAST(UCoreConditionGroupProgress, ChildProgresses, Params);
}

void UCoreConditionGroupProgress::GetProgressesWithChildren(TArray<UCoreConditionProgress*>& OutProgresses) {
    Super::GetProgressesWithChildren(OutProgresses);

    for (auto ChildProgress : ChildProgresses) {
        ChildProgress->GetProgressesWithChildren(OutProgresses);
    }
}

void UCoreConditionGroupProgress::OnChildConditionSatisfyChange(UCoreConditionProgress* Progress, bool NewSatisfy) {
    RefreshSatisfy();
}

void UCoreConditionGroupProgress::OnChildProgressPostNetReceive(UCoreConditionProgress* Progress) {
    OnConditionProgressPostNetReceive.Broadcast(this);
}

void UCoreConditionGroupProgress::OnRep_ChildProgresses(const TArray<UCoreConditionProgress*>& OldChildProgresses) {
    for (auto ChildProgress : OldChildProgresses) {
        if (ChildProgress) {
            ChildProgress->OnConditionProgressPostNetReceive.RemoveDynamic(this, &UCoreConditionGroupProgress::OnChildProgressPostNetReceive);
        }
    }
    for (auto ChildProgress : ChildProgresses) {
        if (ChildProgress) {
            ChildProgress->OnConditionProgressPostNetReceive.AddDynamic(this, &UCoreConditionGroupProgress::OnChildProgressPostNetReceive);
        }
    }
}