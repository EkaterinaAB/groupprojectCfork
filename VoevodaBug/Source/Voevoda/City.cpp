// Fill out your copyright notice in the Description page of Project Settings.


#include "City.h"

City::City() 
{
    int32 unitTypeNumber = FMath::RandRange(0, 2);
    switch (unitTypeNumber) {
    case 0:
        unitType = Archers;
        break;
    case 1:
        unitType = Infantry;
        break;
    case 2:
        unitType = Cavalry;
        break;
    }
}

City::~City()
{
}


void City::replenish_army(AStrategist* player_id) {
    //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("city"));

    if (owner->id == player_id->id || player_id->is_dead()) {
        return;
    }

    int32 replenishAmount = FMath::Min(manpower_growth, player_id->manpower_available)/5;
    int32 wasdebug;
    FString message;
    switch (unitType) {
        case Archers:
            player_id->general.army_size.Archers += replenishAmount;
            wasdebug = player_id->general.army_size.Archers;
            message = FString::Printf(TEXT("Archers ") );
            break;
        case Infantry:
            wasdebug = player_id->general.army_size.Infantry;
            message = FString::Printf(TEXT("Infantry "));
            player_id->general.army_size.Infantry += replenishAmount;
            break;
        case Cavalry:
            wasdebug = player_id->general.army_size.Cavalry;
            message = FString::Printf(TEXT("Cavalry"));
            player_id->general.army_size.Cavalry += replenishAmount;
            break;
     }
     
     owner->manpower_available -= replenishAmount;
     FString message2 = FString::Printf(TEXT("was: %d, become: %d "), manpower_growth, wasdebug+replenishAmount);
     GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, message);
     GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, message2);

}
//void City::SetOwner(AStrategist* player_id) {
//    owner = player_id;
//}
