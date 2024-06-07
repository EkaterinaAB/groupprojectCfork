// Fill out your copyright notice in the Description page of Project Settings.


#include "Scout.h"
#include "MapPainter.h"

Scout::Scout(bool is_player_, AMapPainter*  painter_ptr_){
	is_player = is_player_;
	painter_ptr = painter_ptr;
}

Scout::Scout() {}

void Scout::TickFromStrategist()
{

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

void Scout::execute_scout(Location input) {
	if (!active) {
		target_position = input;
		active = 1;
	}
}


