#ifndef VITAGUI_HPP
#define VITAGUI_HPP

#include <vita2d.h>
#include "GUIElements.hpp"
#include "Discord.hpp"
#include <vector>
#include <string>

class VitaGUI{
	public:
		VitaGUI();
		~VitaGUI();
		void Draw();
		void AddRectangle(float x , float y , float w , float h , unsigned int color);
		void RemoveRectangle(int index);
		int scroll(int x , int y);
		int click(int x , int y);
		std::vector<std::string> loginTexts;
		std::string loadingString = "";
		
		void SetState(int s);
		int GetState();
		
		void passDiscordPointer(Discord *ptr);
		void setGuildBoxes();
		void setChannelBoxes();
		void setMessageBoxes();
		void updateBoxes();
		void NextFont();
		
	
	private:
		Discord *discordPtr;
		int currentFont = 0;
		vita2d_font *vita2dFont;
		vita2d_font *vita2dFontSymbola;
		vita2d_font *vita2dFontSymbolaHint;
		vita2d_font *vita2dFontSeguiemEmoji;
		vita2d_font *vita2dFontLastResort;
		vita2d_font *vita2dFontOpenSansEmoji;
		//vita2d_pgf *pgf;
		vita2d_texture *backgroundImage;
		vita2d_texture *loginFormImage;
		vita2d_texture *loadingImage;
		vita2d_texture *guildsBGImage;
		std::vector<rectangle> rectangles;
		std::string loadingScreenString;
		//std::vector<std::string> guildNames;
		//std::vector<std::string> channelNames;
		//std::vector<std::string> channelTopics;
		//std::vector<std::string> userNames;
		
		std::vector<inputbox> loginInputs;
		std::vector<box> guildBoxes;
		std::vector<box> channelBoxes;
		std::vector<box> messageBoxes;
		
		int guildScrollX = 0;
		int guildScrollY = 0;
		int guildScrollYMin = -1280;
		int guildScrollYMax = 0;
		
		int channelScrollX = 0;
		int channelScrollY = 0;
		int channelScrollYMin = -1280;
		int channelScrollYMax = 0;
		
		int messageScrollX = 0;
		int messageScrollY = 0;
		int messageScrollYMin = -1280;
		int messageScrollYMax = 0;
		
		float loadingImageAngle = 0;
		
		int state = 0;  // 0 login , 1 loading , 2 guilds , 3 channels , 4 channellobby , 5 friends , 6 dms , 7 settings , 8 stuff..
	
	
	
};






#endif

