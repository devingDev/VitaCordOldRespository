#ifndef VITAGUI_HPP
#define VITAGUI_HPP

#include <vita2d.h>
#include "GUIElements.hpp"
#include <vector>
#include <string>

class VitaGUI{
	public:
		VitaGUI();
		~VitaGUI();
		void Draw();
		void AddRectangle(float x , float y , float w , float h , unsigned int color);
		void RemoveRectangle(int index);
		int click(int x , int y);
		std::vector<std::string> loginTexts;
		std::string loadingString = "";
		
		void SetState(int s);
		int GetState();
		
	
	private:
		vita2d_pgf *pgf;
		vita2d_texture *backgroundImage;
		vita2d_texture *loginFormImage;
		vita2d_texture *loadingImage;
		std::vector<rectangle> rectangles;
		std::string loadingScreenString;
		std::vector<std::string> guildNames;
		std::vector<std::string> channelNames;
		std::vector<std::string> channelTopics;
		std::vector<std::string> userNames;
		
		std::vector<inputbox> loginInputs;
		
		float loadingImageAngle;
		
		int state ;  // 0 login , 1 loading , 2 guilds , 3 channels , 4 channellobby , 5 friends , 6 dms , 7 settings , 8 stuff..
	
	
	
};






#endif