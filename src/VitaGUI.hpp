#ifndef VITAGUI_HPP
#define VITAGUI_HPP

#include <vita2d.h>
#include "GUIElements.hpp"
#include "Discord.hpp"
#include <vector>
#include <string>

#define MAX_DRAW_HEIGHT 800
#define MIN_DRAW_HEIGHT -800

#define MESSAGE_AUTHOR_TEXT_SIZE_PIXEL 15
#define MESSAGE_CONTENT_TEXT_SIZE_PIXEL 30
#define CHANNEL_TITLE_TEXT_SIZE_PIXEL 20
#define CHANNEL_TOPIC_TEXT_SIZE_PIXEL 12
#define GUILD_TITLE_TEXT_SIZE_PIXEL 25

#define CLICKED_DM_ICON 50000

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
		void setDirectMessageBoxes();
		void setDirectMessageMessagesBoxes();
		void updateBoxes();
		void NextFont();
		
		void SetStateToLastState();
		
		typedef struct{
			std::string name;
			int id;
			vita2d_texture *icon;
		} emoji_icon;
		
	
	private:
		Discord *discordPtr;
		int currentFont = 0;
		int lastState = 0;
		vita2d_font *vita2dFont;
		//vita2d_font *vita2dFontSymbola;
		//vita2d_font *vita2dFontSymbolaHint;
		//vita2d_font *vita2dFontSeguiemEmoji;
		//vita2d_font *vita2dFontLastResort;
		//vita2d_font *vita2dFontOpenSansEmoji;
		//vita2d_pgf *pgf;
		vita2d_texture *backgroundImage;
		vita2d_texture *loginFormImage;
		vita2d_texture *loadingImage;
		vita2d_texture *guildsBGImage;
		vita2d_texture *dmIconImage;
		std::vector<rectangle> rectangles;
		std::string loadingScreenString;
		//std::vector<std::string> guildNames;
		//std::vector<std::string> channelNames;
		//std::vector<std::string> channelTopics;
		//std::vector<std::string> userNames;
		
		std::vector<inputbox> loginInputs;
		std::vector<box> guildBoxes;
		std::vector<box> channelBoxes;
		std::vector<messagebox> messageBoxes;
		std::vector<box> directMessageBoxes;
		std::vector<box> directMessageMessagesBoxes;
		
		std::vector<emoji_icon> emojis;
		
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
		
		
		int directMessageScrollX = 0;
		int directMessageScrollY = 0;
		int directMessageScrollYMin = -1280;
		int directMessageScrollYMax = 0;
		
		
		int directMessageMessagesScrollX = 0;
		int directMessageMessagesScrollY = 0;
		int directMessageMessagesScrollYMin = -1280;
		int directMessageMessagesScrollYMax = 0;
		
		float loadingImageAngle = 0;
		
		int state = 0;  // 0 login , 1 loading , 2 guilds , 3 channels , 4 channellobby , 5 friends , 6 dms , 7 dmchannellobby , 15 settings , 85818764 stuff..
	
		std::string wordWrap(std::string wrapthiss, int abwidth);
	
	
};






#endif

