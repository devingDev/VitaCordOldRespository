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
	int port,i;
	for(port = 0; port < SCE_TOUCH_PORT_MAX_NUM; port++){
		sceTouchPeek(port, &touch[port], 1);
	}
}

