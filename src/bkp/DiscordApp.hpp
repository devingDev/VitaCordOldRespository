#ifndef DISCORDAPP_HPP
#define DISCORDAPP_HPP


#include <psp2/kernel/processmgr.h>

#include "VitaTouch.hpp"
#include "VitaPad.hpp"
#include "VitaIME.hpp"
#include "Discord.hpp"
#include "VitaGUI.hpp"


class DiscordApp{
	
	public:
		void Start();
		void loadUserDataFromFile();
		void saveUserDataToFile(std::string m , std::string p , std::string t);
		
	private:
		VitaGUI vitaGUI;
		Discord discord;
		VitaIME vitaIME;
		VitaPad vitaPad;
		VitaTouch vitaTouch;
		int clicked = -1;
		int scrolled = -1;
		int vitaState = 0;
	
};



#endif




