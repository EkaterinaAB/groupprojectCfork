#pragma once

#include "Strategist.h"
#include "Structure.h"
#include "City.h"
#include "MyPlayerCharacter.h"
#include "UStructureInfoWidget.h"

class AMyPlayerCharacter;

class VOEVODA_API SupplyArmyInteractor 
{
private:

    AMyPlayerCharacter* PlayerCharacter = nullptr;
    //TMap<TPair<int32, int32>, float> LastSupplyTimeMap;
    TMap<TPair<int32, int32>, int32> LastSupplyTimeMap2;
    //void HandleIfTrue(AStrategist* strategist, AStructure* structure, float Time);
    void HandleIfTrue2(AStrategist* strategist, AStructure* structure);

public:

    ///void SetMapAndPlayerCharacter2(AMyPlayerCharacter* PlayerCharacter_, TArray<AStrategist*>& strategists, TArray<AStructure*>& structures);
    //void StartSupplyArmyEvent(TArray<AStrategist*>& strategists, TArray<AStructure*>& structures, float Time);

    void StartSupplyArmyEvent2(TArray<AStrategist*>& strategists, TArray<AStructure*>& structures);

   // SupplyArmyInteractor(TArray<AStrategist*> &strategists, TArray<AStructure*> &structures);

    //void SetHUD(ASupplyArmyHUD* Hud);
  /*  void SetPlayerCharacter(AMyPlayerCharacter* PlayerCharacter_, TArray<AStructure*>& structures);
 
    void SetMap(TArray<AStrategist*>& strategists, TArray<AStructure*>& structures);*/

    void SetMapAndPlayerCharacter(AMyPlayerCharacter* PlayerCharacter_, TArray<AStrategist*>& strategists, TArray<AStructure*>& structures);

     SupplyArmyInteractor() = default;
    ~SupplyArmyInteractor() = default;

};