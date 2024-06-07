// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "MapPainter.h"
#include "Math/Vector2D.h"
#include "Location.h"
#include "GameFramework/Actor.h"
#include "ScoutActor.generated.h"

class AMapPainter;

UCLASS()
class VOEVODA_API AScoutActor : public AActor
{
	GENERATED_BODY()
	
public:	
	int32 missions_spy;
	bool active = 0;
	bool is_player = 0;
	int32 passed_time = 0;
	int32 mission_time = 1000;
	Location  target_position;
	AMapPainter* painter_ptr;

	AScoutActor(bool is_player_);

	//void execute_scout(FVector2D input);
	void execute_scout(Location input);

	// Sets default values for this actor's properties
	AScoutActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
