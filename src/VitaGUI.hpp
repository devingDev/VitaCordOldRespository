#ifndef VITAGUI_HPP
#define VITAGUI_HPP

#include <vita2d.h>
#include "GUIElements.hpp"
#include "Discord.hpp"
#include <vector>
#include <string>

#define MAX_DRAW_HEIGHT 550
#define MIN_DRAW_HEIGHT -800

#define MAX_FONT_SIZE 32

#define MESSAGE_AUTHOR_TEXT_SIZE_PIXEL 15
#define MESSAGE_CONTENT_TEXT_SIZE_PIXEL 24
#define CHANNEL_TITLE_TEXT_SIZE_PIXEL 18
#define CHANNEL_TOPIC_TEXT_SIZE_PIXEL 14
#define GUILD_TITLE_TEXT_SIZE_PIXEL 18


#define MESSAGE_INPUT_HEIGHT 72

#define GUILD_HEIGHT 64
#define CHANNEL_HEIGHT 64
#define DMICONX 128
#define DMICONY 30
#define DMICONX2 128+64
#define DMICONY2 30+64


#define CLICKED_DM_ICON 50000

#define MAX_EMOJI 2500;

class VitaGUI{
	public:
		VitaGUI();
		~VitaGUI();
		void Draw();
		void AddRectangle(float x , float y , float w , float h , unsigned int color);
		void RemoveRectangle(int index);
		int scroll(int x , int y , int posx  , int posy);
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
		
		std::vector<emoji_icon> emojis;
		
		void setUserInfo();
	
	private:
		Discord *discordPtr;
		int currentFont = 0;
		int lastState = 0;
		vita2d_font *vita2dFont[MAX_FONT_SIZE];
		vita2d_font *vita2dFontSmall;
		vita2d_font *vita2dFontNormal;
		vita2d_font *vita2dFontBig;
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
		vita2d_texture *statbarIconImage;
		vita2d_texture *sidepanelStateIconImage;
		vita2d_texture *messageInputImage;
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
		
		void loadEmojiFiles();
		
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
	
		int wordWrap(std::string wrapthiss, int abwidth , std::string &output);  // return value is amount of linebreaks
		
		std::string panelUsername , panelUserDiscriminator;
	
	
};






#endif

