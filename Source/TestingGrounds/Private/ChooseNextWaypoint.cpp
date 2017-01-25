            // Fill out your copyright notice in the Description page of Project Settings.

#include "TestingGrounds.h"
#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "PatrolRoute.h"
#include "BehaviorTree/BehaviorTreeComponent.h"


UChooseNextWaypoint::UChooseNextWaypoint()
{
    // TODO: what needs to be initialised?
}


EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

    // get patrol points
    auto AIOwner = OwnerComp.GetAIOwner();
    auto ControlledPawn = AIOwner->GetPawn();
    
    // TODO: what happens if there is more then 1 compent attached?
    auto PatrolComponent = ControlledPawn->FindComponentByClass<UPatrolRoute>();
    if( !ensure(PatrolComponent)) { return EBTNodeResult::Failed; }
    
    auto PatrolPoints = PatrolComponent->GetPatrolPoints();
    if ( PatrolPoints.Num() == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("Guard [%s] has no Patrol Points defined"), *ControlledPawn->GetName() );
        return EBTNodeResult::Failed;
    }

    // Set Next Waypoint
    auto BlackboardComp = OwnerComp.GetBlackboardComponent();
    auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
    BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[Index]);
    
    // Cycle waypoint index
    auto NewIndex = (Index + 1) % PatrolPoints.Num();
    BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, NewIndex );


    return EBTNodeResult::Succeeded;
}
