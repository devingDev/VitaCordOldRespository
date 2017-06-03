#ifndef VITATOUCH_HPP
#define VITATOUCH_HPP

#include <psp2/touch.h>
#include <string.h>
#include "mathtools.hpp"

#define SLEEP_CLICK_NORMAL 150000
#define SLEEP_CLICK_EXTENDED 350000

class VitaTouch{
	public:
		VitaTouch();
		void readTouch();
		SceTouchData touch_old[SCE_TOUCH_PORT_MAX_NUM];
		SceTouchData touch[SCE_TOUCH_PORT_MAX_NUM];
		vector2 getClickPoint();
		vector2 lastClickPoint;
		bool clicking;
		bool scrolling;
		int scrollDirX ;
		int scrollDirY;

	private:
		void initTouch();
		
		vector2 emptyClickPoint;
		
};








#endif