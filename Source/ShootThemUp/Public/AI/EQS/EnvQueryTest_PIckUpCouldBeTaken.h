// Shoot Them Up Game. All RIghts Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EnvQueryTest_PIckUpCouldBeTaken.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API UEnvQueryTest_PIckUpCouldBeTaken : public UEnvQueryTest
{
	GENERATED_BODY()
public:
    UEnvQueryTest_PIckUpCouldBeTaken(const FObjectInitializer& ObjectInitializer);

    virtual void RunTest(FEnvQueryInstance& QueryInstance) const override;
	
};
