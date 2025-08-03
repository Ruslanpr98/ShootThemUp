// Shoot Them Up Game. All RIghts Reserved.


#include "AI/EQS/EnvQueryTest_PIckUpCouldBeTaken.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_ActorBase.h"
#include "PickUps/STUBasePickUp.h"

UEnvQueryTest_PIckUpCouldBeTaken::UEnvQueryTest_PIckUpCouldBeTaken(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    Cost = EEnvTestCost::Low;
    ValidItemType = UEnvQueryItemType_ActorBase::StaticClass();
    SetWorkOnFloatValues(false);
}

void UEnvQueryTest_PIckUpCouldBeTaken::RunTest(FEnvQueryInstance &QueryInstance) const {

    const auto DataOwner = QueryInstance.Owner.Get();
    BoolValue.BindData(DataOwner, QueryInstance.QueryID);
    bool WantsBeTakeable = BoolValue.GetValue();
    
    for (FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
    {
        const auto ItemActor = GetItemActor(QueryInstance, It.GetIndex());
        const auto PickUpActor = Cast<ASTUBasePickUp>(ItemActor);

        if (!PickUpActor) continue;
        const auto CouldBeTaken = PickUpActor->CouldBeTaken();
        It.SetScore(TestPurpose, FilterType, CouldBeTaken, WantsBeTakeable);
    }
}