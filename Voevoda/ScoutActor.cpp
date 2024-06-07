// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoutActor.h"
#include "MapPainter.h"

// Sets default values
AScoutActor::AScoutActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

AScoutActor::AScoutActor(bool is_player_) : AScoutActor() {

	is_player = is_player_;
}




// Called when the game starts or when spawned
void AScoutActor::BeginPlay()
{
	Super::BeginPlay();

	for (TActorIterator<AMapPainter> ActorItr(GetWorld()); ActorItr;
		++ActorItr) {
		painter_ptr = Cast<AMapPainter>(*ActorItr);
	}

}


// Called every frame
void AScoutActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (active && mission_time > passed_time) {
		passed_time++;
	}
	else if (active) {
		active = 0;
		passed_time = 0;
	}

	if (is_player && active) {
		painter_ptr->UpdateRhombVision(target_position.X, target_position.Y, 5, Seen);
	}

}

void AScoutActor::execute_scout(Location input) {
	if (!active) {
		target_position = input;
		active = 1;
	}
}


