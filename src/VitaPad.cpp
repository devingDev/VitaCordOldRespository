
#include <psp2/ctrl.h>
#include "VitaPad.hpp"

VitaPad::VitaPad(){
}

VitaPad::VitaPad(bool initstuff){
	sceCtrlSetSamplingMode(SCE_CTRL_MODE_ANALOG);
	sceCtrlPeekBufferPositive(0, &vitapad, 1);
	left_analog_calibration_x = vitapad.lx;
	left_analog_calibration_y = vitapad.ly;
}


VitaPad::~VitaPad(){
	
}

void VitaPad::Read(){
	sceCtrlPeekBufferPositive(0, &vitapad, 1);
	
	select = start = up = right = down = left = lefttrigger = righttrigger = triangle = circle = cross = square = volup = voldown = false;
	left_analog_moving = right_analog_moving = false;
	left_analog_x =   0;
	left_analog_y =   0;
	right_analog_x =  0;
	right_analog_y =  0;
	
	if(vitapad.buttons & SCE_CTRL_SELECT)
		select = true;
	if(vitapad.buttons & SCE_CTRL_START)
		start = true;
	if(vitapad.buttons & SCE_CTRL_UP)
		up = true;
	if(vitapad.buttons & SCE_CTRL_RIGHT)
		right = true;
	if(vitapad.buttons & SCE_CTRL_DOWN)
		down = true;
	if(vitapad.buttons & SCE_CTRL_LEFT)
		left = true;
	if(vitapad.buttons & SCE_CTRL_LTRIGGER)
		lefttrigger = true;
	if(vitapad.buttons & SCE_CTRL_RTRIGGER)
		righttrigger = true;
	if(vitapad.buttons & SCE_CTRL_L1)
		lefttrigger = true;
	if(vitapad.buttons & SCE_CTRL_R1)
		righttrigger = true;
	if(vitapad.buttons & SCE_CTRL_TRIANGLE)
		triangle = true;
	if(vitapad.buttons & SCE_CTRL_CIRCLE)
		circle = true;
	if(vitapad.buttons & SCE_CTRL_CROSS)
		cross = true;
	if(vitapad.buttons & SCE_CTRL_SQUARE)
		square = true;	
	if(vitapad.buttons & SCE_CTRL_VOLUP)
		volup = true;
	if(vitapad.buttons & SCE_CTRL_VOLDOWN)
		voldown = true;
	
	lx = vitapad.lx;
	ly = vitapad.ly;
	rx = vitapad.rx;
	ry = vitapad.ry;
	 
	 
	left_analog_x = vitapad.lx - left_analog_calibration_x;
	left_analog_y = vitapad.ly - left_analog_calibration_y;
	right_analog_x = vitapad.rx - right_analog_calibration_x;
	right_analog_y = vitapad.ry - right_analog_calibration_y;
	
}


