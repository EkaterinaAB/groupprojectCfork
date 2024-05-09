#include "SupplyArmyInteractor.h"
#include "HAL/PlatformProcess.h"



void SupplyArmyInteractor::HandleIfTrue2(AStrategist* strategist, AStructure* structure) {


    TPair<int32, int32> Pair = TPair<int32, int32>(strategist->id, structure->id);
    if (!LastSupplyTimeMap2.Contains(Pair)) {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("pair problem HandleIfTrue2"));
        return;
    }

    LastSupplyTimeMap2[Pair]++;

    //FString message = FString::Printf(TEXT("LastSupplyTimeMap2[Pair]: %d "), LastSupplyTimeMap2[Pair]);
    //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, message);
   // FString message2 = FString::Printf(TEXT("1: %d, 2: %d "), strategist->id, structure->id);
   // GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, message2);

   if (LastSupplyTimeMap2[Pair] >= 100) {
       // GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("citySupplyArmyInteractor2222222"));
        City* city = Cast<City>(structure);
        if (!city) {
            return;
        }
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("citySupplyArmyInteractor"));
        city->replenish_army(strategist);
        LastSupplyTimeMap2[Pair] = -1.;
    }

}


void SupplyArmyInteractor::SetMapAndPlayerCharacter(AMyPlayerCharacter* PlayerCharacter_, TArray<AStrategist*>& strategists, TArray<AStructure*>& structures) {

    PlayerCharacter = PlayerCharacter_;
    int32  PlayerCharacterId = PlayerCharacter->Strategist->id;

    for (AStructure* structure : structures) {
        for (AStrategist* strategist : strategists) {
            TPair<int32, int32> Pair = TPair<int32, int32>(strategist->id, structure->id);
            LastSupplyTimeMap2.Add(Pair, -1);
        }

        TPair<int32, int32> Pair = TPair<int32, int32>(PlayerCharacterId, structure->id);
        LastSupplyTimeMap2.Add(Pair, -1);

    }
}



void SupplyArmyInteractor::StartSupplyArmyEvent2(TArray<AStrategist*>& strategists, TArray<AStructure*>& structures)
{
    if (LastSupplyTimeMap2.Num() == 0 || !PlayerCharacter) {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("null"));
        return;
    }


    for (AStructure* structure : structures) {
        for (AStrategist* strategist : strategists) {
            if (strategist->general.position == structure->position) {
                HandleIfTrue2(strategist, structure);
            }
            else {
                TPair<int32, int32> Pair = TPair<int32, int32>(strategist->id, structure->id);
                if (LastSupplyTimeMap2.Contains(Pair))
                {
                    LastSupplyTimeMap2[Pair] = -1;
                }
                else
                {
                    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("pair problem"));
                    FString message = FString::Printf(TEXT("strategist: %d, structure: %d"), (strategists.Num(), structures.Num()));
                    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, message);
                    return;
                }
            }
        }
        if (PlayerCharacter && PlayerCharacter->Strategist->general.position == structure->position) {
            //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("on  structure"));
            HandleIfTrue2(PlayerCharacter->Strategist, structure);
            //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("on  structure"));
        }
        else if (PlayerCharacter) {
            //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("not on  structure"));
            TPair<int32, int32> Pair = TPair<int32, int32>(PlayerCharacter->Strategist->id, structure->id);
            LastSupplyTimeMap2[Pair] = -1;
           // GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("not on  structure"));
        }
    }
}
//void SupplyArmyInteractor::SetPlayerCharacter(AMyPlayerCharacter* PlayerCharacter_, TArray<AStructure*>& structures)
//{
//    PlayerCharacter = PlayerCharacter_;
//    int32  PlayerCharacterId = PlayerCharacter->Strategist->id;
//
//    for (AStructure* structure : structures) {
//            TPair<int32, int32> Pair = TPair<int32, int32>(PlayerCharacterId, structure->id);
//            LastSupplyTimeMap.Add(Pair, -1.0f);
//    }
//}
//void SupplyArmyInteractor::HandleIfTrue(AStrategist* strategist, AStructure* structure, float Time) {
//
//    //if (SupplyArmyHUD && strategist->id == 0) {
//    //    SupplyArmyHUD->DisplayHUD();
//    //}
//    TPair<int32, int32> Pair = TPair<int32, int32>(strategist->id, structure->id);
//
//
//    if (LastSupplyTimeMap[Pair] == -1.0f) {
//
//        LastSupplyTimeMap[Pair] = Time;
//        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("HandleIfTrue"));
//        FString message = FString::Printf(TEXT("time: %d, "), Time);
//        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, message);
//    }
//    else if (Time - LastSupplyTimeMap[Pair] >= 3.0f) {
//        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("citySupplyArmyInteractor2222222"));
//        City* city = Cast<City>(structure);
//        if (!city) {
//            return;
//        }
//        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("citySupplyArmyInteractor33333"));
//        city->replenish_army(strategist);
//        LastSupplyTimeMap[Pair] = -1.0f;
//    }
//
//}
//void SupplyArmyInteractor::SetMapAndPlayerCharacter2(AMyPlayerCharacter* PlayerCharacter_, TArray<AStrategist*>& strategists, TArray<AStructure*>& structures) {
//
//    PlayerCharacter = PlayerCharacter_;
//    int32  PlayerCharacterId = PlayerCharacter->Strategist->id;
//
//    for (AStructure* structure : structures) {
//        for (AStrategist* strategist : strategists) {
//            TPair<int32, int32> Pair = TPair<int32, int32>(strategist->id, structure->id);
//            LastSupplyTimeMap.Add(Pair, -1.0f);
//        }
//
//        TPair<int32, int32> Pair = TPair<int32, int32>(PlayerCharacterId, structure->id);
//        LastSupplyTimeMap.Add(Pair, -1.0f);
//
//    }
//}
//SupplyArmyInteractor::SupplyArmyInteractor(TArray<AStrategist*>& strategists, TArray<AStructure*>& structures) {
//    //if (SupplyArmyHUD) {
//    //    SupplyArmyHUD->DisplayHUD();
//    //}
//    for (AStructure* structure : structures) {
//        for (AStrategist* strategist : strategists) {
//            TPair<int32, int32> Pair = TPair<int32, int32>(strategist->id, structure->id);
//            LastSupplyTimeMap.Add(Pair, -1.0f);
//        }
//    }
//}
//void SupplyArmyInteractor::StartSupplyArmyEvent(TArray<AStrategist*>& strategists, TArray<AStructure*>& structures, float Time)
//{
//    if (LastSupplyTimeMap.Num() == 0 || !PlayerCharacter) {
//        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("null"));
//        return;
//    }
//
//    FString message3 = FString::Printf(TEXT("time: %d, "), Time);
//    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, message3);
//
//    for (AStructure* structure : structures) {
//        for (AStrategist* strategist : strategists) {
//            if (strategist->general.position == structure->position) {
//                HandleIfTrue(strategist, structure, Time);
//            }
//            else {
//                TPair<int32, int32> Pair = TPair<int32, int32>(strategist->id, structure->id);
//                if (LastSupplyTimeMap.Contains(Pair))
//                {
//                    LastSupplyTimeMap[Pair] = -1.0f;
//                }
//                else
//                {
//                    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("pair problem"));
//                    FString message = FString::Printf(TEXT("strategist: %d, structure: %d"), (strategists.Num(), structures.Num()));
//                    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, message);
//                    return;
//                }
//            }
//        }
//
//        if (PlayerCharacter && PlayerCharacter->Strategist->general.position == structure->position) {
//            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("on  structure"));
//            HandleIfTrue(PlayerCharacter->Strategist, structure, Time);
//            //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("on  structure"));
//        }
//        else if (PlayerCharacter) {
//            //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("not on  structure"));
//            TPair<int32, int32> Pair = TPair<int32, int32>(PlayerCharacter->Strategist->id, structure->id);
//            LastSupplyTimeMap[Pair] = -1.0f;
//        }
//    }
//}