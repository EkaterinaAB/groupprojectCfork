#include "GameWorld.h"
#include "CoreMinimal.h"
#include "EngineUtils.h"
#include "GameFramework/Actor.h"

AGameWorld::AGameWorld() {

    SupplyArmyInteractorInstance = SupplyArmyInteractor();
    PrimaryActorTick.bCanEverTick = true;

}
AGameWorld::~AGameWorld() {

}
void AGameWorld::Tick(float DeltaTime) {

    Super::Tick(DeltaTime);

    //SupplyArmyInteractorInstance.StartSupplyArmyEvent(strategists, structures, GetWorld()->GetTimeSeconds());
    SupplyArmyInteractorInstance.StartSupplyArmyEvent2(strategists, structures);
    //FString message = FString::Printf(TEXT("x: %d, y: %d"), playerCharacter->Strategist->general.position.x, playerCharacter->Strategist->general.position.y);
    //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, message);
}

void AGameWorld::InitializePointers() {

    for (TActorIterator<AMapPainter> ActorItr(GetWorld()); ActorItr;
        ++ActorItr) {
        painter_ptr = Cast<AMapPainter>(*ActorItr);
        map_ptr = &(painter_ptr->map);
    }

    for (TActorIterator<AMyPlayerCharacter> ActorItr(GetWorld()); ActorItr; ++ActorItr)
    {
        playerCharacter = Cast<AMyPlayerCharacter>(*ActorItr);
    }

}

void AGameWorld::BeginPlay() {
    Super::BeginPlay();

    InitializePointers();
    //painter_ptr->BeginPlayFunction();


    if (painter_ptr) {
        for (auto& general_pos : map_ptr->GeneralsInitPos) {
            AStrategist* Strategist = NewObject<AStrategist>(this);
            Strategist->general.position = general_pos;
            strategists.Add(Strategist);
        }
        for (int32 id = 0; id < map_ptr->CitiesInitPos.Num(); id++) {
            City* new_city = NewObject<City>(this);
            new_city->position = map_ptr->CitiesInitPos[id];
            //new_city->SetOwner();
            new_city->owner = strategists[id];
            structures.Add(new_city);
        }
    }
    else {
        UE_LOG(LogTemp, Warning, TEXT("painter_ptr is nullptr."));
    }


    if (playerCharacter) {

        playerCharacter->InitializeStrategist();
        SupplyArmyInteractorInstance.SetMapAndPlayerCharacter(playerCharacter, strategists, structures);

        //AStrategist new_strategist(playerCharacter->Strategist);
    }
    else {
        UE_LOG(LogTemp, Warning, TEXT("playerCharacter is nullptr."));
    }

   FString message = FString::Printf(TEXT("Strategists size: %d, Structures size: %d"), strategists.Num(), structures.Num());
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, message);
    FString message2= FString::Printf(TEXT("x: %d, y: %d"),playerCharacter->Strategist->general.position.x, playerCharacter->Strategist->general.position.y);
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, message2);
}

//for (auto& castle_pos : map_ptr->CastlesInitPos) {
 //    AStructure new_castle(castle_pos);
 //    structures.Add(&new_castle);
 //}
        //for (auto& castle_pos : map_ptr->CastlesInitPos) {
        //    AStructure new_castle(castle_pos);
        //    structures.Add(&new_castle);
        //}
/* AStrategist new_strategist(general_pos);
            strategists.Add(&new_strategist);*/