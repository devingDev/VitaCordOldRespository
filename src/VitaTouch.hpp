#ifndef VITATOUCH_HPP
#define VITATOUCH_HPP

#include <psp2/touch.h>
#include <string.h>

class VitaTouch{
	public:
		VitaTouch();
		void readTouch();
		SceTouchData touch_old[SCE_TOUCH_PORT_MAX_NUM];
		SceTouchData touch[SCE_TOUCH_PORT_MAX_NUM];

	private:
		void initTouch();
		
};








#endif