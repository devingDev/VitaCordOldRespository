#include "VitaTouch.hpp"


VitaTouch::VitaTouch(){
	initTouch();
}
void VitaTouch::initTouch(){
	sceTouchSetSamplingState(SCE_TOUCH_PORT_FRONT, 1);
	sceTouchSetSamplingState(SCE_TOUCH_PORT_BACK, 1);
	sceTouchEnableTouchForce(SCE_TOUCH_PORT_FRONT);
	sceTouchEnableTouchForce(SCE_TOUCH_PORT_BACK);
	
}

void VitaTouch::readTouch(){
	memcpy(touch_old, touch, sizeof(touch_old));
	int port;
	for(port = 0; port < SCE_TOUCH_PORT_MAX_NUM; port++){
		sceTouchPeek(port, &touch[port], 1);
	}
	if (touch[SCE_TOUCH_PORT_FRONT].reportNum >= 1){
		lastTouchPoint.x = touch[SCE_TOUCH_PORT_FRONT].report[0].x / 2;  // 1920 touch => 960 display
		lastTouchPoint.y = touch[SCE_TOUCH_PORT_FRONT].report[0].y / 2;
	}else{
		lastTouchPoint = emptyTouchPoint;
	}
}

vector2 VitaTouch::getTouchPoint(){
	return lastTouchPoint;
}

