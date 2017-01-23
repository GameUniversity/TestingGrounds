            // Fill out your copyright notice in the Description page of Project Settings.

#include "TestingGrounds.h"
#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
// TODO: review includes
#include "AIController.h"
#include "GameFramework/Pawn.h"
#include "PatrollingGuard.h" // TODO remove comp
#include "BehaviorTree/BehaviorTreeComponent.h"


UChooseNextWaypoint::UChooseNextWaypoint()
{
    // TODO: what needs to be initialised?
}


EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

    // TODO: protect against empty tatrol route


    // get patrol points
    auto AIOwner = OwnerComp.GetAIOwner();
    auto ControlledPawn = AIOwner->GetPawn();
    auto PatrollingGuard =Cast<APatrollingGuard>(ControlledPawn);
    auto PatrolPoints = PatrollingGuard->GetPatrolPoints();

    // Set Next Waypoint
    auto BlackboardComp = OwnerComp.GetBlackboardComponent();
    auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
    BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[Index]);
    
    // Cycle waypoint index
    auto NewIndex = (Index + 1) % PatrolPoints.Num();
    BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, NewIndex );


    return EBTNodeResult::Succeeded;
}
