#include "VitaGUI.hpp"
#include "log.hpp"
#include <istream>
#include <sstream>
#include <iterator>
#include <algorithm>   // for reverse
#include <psp2/io/dirent.h> 


static int max(int a , int b){
	return ( (a>b)? (a) : (b) );
}

void VitaGUI::NextFont(){
	// REMOVED 
	
	//currentFont ++;
	//if(currentFont > 4){
	//	currentFont = 0;
	//}else if(currentFont < 0){
	//	currentFont = 0;
	//}
	//
	//switch(currentFont){
	//	case 0:
	//		vita2dFont = vita2dFontSymbola;
	//		break;
	//	case 1:
	//		vita2dFont = vita2dFontSymbolaHint;
	//		break;
	//	case 2:
	//		vita2dFont = vita2dFontSeguiemEmoji;
	//		break;
	//	case 3:
	//		vita2dFont = vita2dFontLastResort;
	//		break;	
	//	case 4:
	//		vita2dFont = vita2dFontOpenSansEmoji;
	//		break;	
	//	default:
	//		vita2dFont = vita2dFontOpenSansEmoji;
	//		break;
	//}
}

VitaGUI::VitaGUI(){
	vita2d_init();
	vita2d_set_clear_color(RGBA8(0x40, 0x40, 0x40, 0xFF));
	//pgf = vita2d_load_default_pgf();
	
	//pgf = vita2d_load_custom_pgf("app0:assets/font/seguiemj.pgf");
	//vita2dFontSymbola = vita2d_load_font_file("app0:assets/font/symbola.ttf");
	//vita2dFontSymbolaHint = vita2d_load_font_file("app0:assets/font/symbolahint.ttf");
	//vita2dFontSeguiemEmoji = vita2d_load_font_file("app0:assets/font/seguiemj.ttf");
	//vita2dFontLastResort = vita2d_load_font_file("app0:assets/font/lastresort.ttf");
	//vita2dFontOpenSansEmoji = vita2d_load_font_file("app0:assets/font/opensansemoji.ttf");
	
	for(int f = 0; f < MAX_FONT_SIZE ; f++){
		vita2dFont[f] = vita2d_load_font_file("app0:assets/font/droidsans.ttf");
	}
	
	vita2dFontSmall = vita2d_load_font_file("app0:assets/font/droidsans.ttf");
	vita2dFontNormal = vita2d_load_font_file("app0:assets/font/droidsans.ttf");
	vita2dFontBig = vita2d_load_font_file("app0:assets/font/droidsans.ttf");
	
	std::string bgPath = "app0:assets/images/Vitacord-Background-8BIT.png";
	backgroundImage = vita2d_load_PNG_file(bgPath.c_str());
	loginFormImage = vita2d_load_PNG_file("app0:assets/images/Vitacord-LoginForm-8BIT.png");
	loadingImage = vita2d_load_PNG_file("app0:assets/images/Vitacord-Loading-8BIT.png");
	guildsBGImage = vita2d_load_PNG_file("app0:assets/images/Vitacord-GuildsBG-8BIT.png");
	dmIconImage = vita2d_load_PNG_file("app0:assets/images/Vitacord-DMIcon-8BIT.png");
	statbarIconImage = vita2d_load_PNG_file("app0:assets/images/Vitacord-statbar-icon.png");
	sidepanelStateIconImage = vita2d_load_PNG_file("app0:assets/images/Vitacord-sidebar-default-usericon.png");
	messageInputImage = vita2d_load_PNG_file("app0:assets/images/Vitacord-messager-input.png");
	
	loginInputs.clear();
	
	inputbox emailI;
	emailI.x = 431;
	emailI.y = 139;
	emailI.w = 375;
	emailI.h = 50;
	loginInputs.push_back(emailI);
	
	inputbox passwordI;
	passwordI.x = 431;
	passwordI.y = 219;
	passwordI.w = 375;
	passwordI.h = 50;
	loginInputs.push_back(passwordI);
	
	inputbox loginI;
	loginI.x = 449;
	loginI.y = 335;
	loginI.w = 349;
	loginI.h = 58;
	loginInputs.push_back(loginI);
	
	loginTexts.clear();
	loginTexts.push_back(" ");
	loginTexts.push_back(" ");
	
	
	// L8R
	
	
	
	loadEmojiFiles();
	
	
	
}
void VitaGUI::loadEmojiFiles(){
	// EMOJI LOADER:
	emojis.clear();
	emojis.push_back(emoji_icon());
}

VitaGUI::~VitaGUI(){
	vita2d_fini();
	vita2d_free_texture(backgroundImage);
	vita2d_free_texture(loginFormImage);
	vita2d_free_texture(loadingImage);
	vita2d_free_font(vita2dFontSmall);
	vita2d_free_font(vita2dFontNormal);
	vita2d_free_font(vita2dFontBig);
	//vita2d_free_pgf(pgf);
}
void VitaGUI::updateBoxes(){
	
	
}

void VitaGUI::Draw(){

	vita2d_start_drawing();
	vita2d_clear_screen();

	
	if(state == 0){
		vita2d_draw_rectangle(0, 0, 960, 544, RGBA8(114, 137, 217, 255));
		vita2d_draw_texture( loginFormImage , 161, 53 );
		//vita2d_pgf_draw_text(pgf, 420, 154, RGBA8(255,255,255,255), 2.0f, loginTexts[0].c_str());
		//vita2d_pgf_draw_text(pgf, 420, 250, RGBA8(255,255,255,255), 2.0f, loginTexts[1].c_str());
		vita2d_font_draw_text(vita2dFont[18] , 438, 181, RGBA8(255,255,255,255), 18, loginTexts[0].c_str());
		vita2d_font_draw_text(vita2dFont[18] , 438, 261, RGBA8(255,255,255,255), 18, loginTexts[1].c_str());
		
	}else if(state == 1){
		vita2d_draw_rectangle(0, 0, 960, 544, RGBA8(114, 137, 217, 255));
		//vita2d_draw_texture_rotate(loginFormImage, 128 , 64, loadingImageAngle);
		vita2d_draw_texture_rotate(loadingImage, 416 , 208, loadingImageAngle);
		//vita2d_pgf_draw_text(pgf, 150, 300, RGBA8(255,255,255,255), 2.0f, loadingString.c_str());
		vita2d_font_draw_text(vita2dFont[20] , 150, 300, RGBA8(255,255,255,255), 20, loadingString.c_str());
		loadingImageAngle += 0.08f;
		
	}else if(state == 2){
		setGuildBoxes();
		vita2d_draw_rectangle(0, 0, 960, 544, RGBA8(54, 57, 62, 255)); // Background

		
		
		
		
		/// SIDEPANEL
		// BG
		vita2d_draw_rectangle(0, 30, 230, 449, RGBA8(46, 49, 54, 255));
		
		// GUILDS
		for(int i = 0 ; i < guildBoxes.size() ; i++){
			if(guildScrollY + i * GUILD_HEIGHT < MAX_DRAW_HEIGHT && guildScrollY + i * GUILD_HEIGHT  > MIN_DRAW_HEIGHT){
				//vita2d_draw_texture( guildsBGImage , guildScrollX + 230 , guildScrollY + i * 128);
				//vita2d_draw_rectangle(guildScrollX + 4, 100 + guildScrollY + i * GUILD_HEIGHT, 222 , GUILD_HEIGHT, RGBA8(48, 50, 55, 255));
				//vita2d_pgf_draw_text(pgf, guildScrollX + 256, guildScrollY + i * 128 + 96, RGBA8(255,255,255,255), 3.0f, discordPtr->guilds[i].name.c_str());
				vita2d_font_draw_text(vita2dFont[18] , guildScrollX + 8, 100 + guildScrollY + i * GUILD_HEIGHT + GUILD_HEIGHT, RGBA8(255,255,255,255), GUILD_TITLE_TEXT_SIZE_PIXEL, discordPtr->guilds[i].name.c_str());
			}
		}
		
		// TOP sidepanel to hide guilds underneath
		vita2d_draw_rectangle(0, 0, 230, 100, RGBA8(46, 49, 54, 255));
		vita2d_draw_rectangle(0, 99, 230, 1, RGBA8(5, 5, 6, 255));
		
		// BOTTOM SIDEPANEL
		vita2d_draw_rectangle(0, 479, 230, 1, RGBA8(5, 5, 6, 255));
		vita2d_draw_rectangle(0, 480, 230, 64, RGBA8(40, 43, 48, 255));
		vita2d_draw_texture(sidepanelStateIconImage, 14, 493); // sidepanelStateIconImage = user icon or Vitacord-default-usericon.png
		vita2d_font_draw_text(vita2dFont[18], 70, 514, RGBA8(255, 255, 255, 255), 18, panelUsername.c_str());
		vita2d_font_draw_text(vita2dFont[15], 70, 530, RGBA8(255, 255, 255, 255), 15, panelUserDiscriminator.c_str()); // create a vita2dfont for each font-size or your font will get messed up.
		
		vita2d_draw_texture_scale(dmIconImage , 128 , 30 , 0.5f , 0.5f); // DM ICON 
		
		
		// maybe add something on the big right 
		
		/// STATBAR
		vita2d_draw_rectangle(0, 0, 960, 30, RGBA8(242, 101, 34, 163));
		vita2d_draw_texture(statbarIconImage, 10, 7); // statbarIconImage = Vitacord-statbar-icon.png
		
	}else if(state == 3){
		logSD("call setChannelBoxes");
		setChannelBoxes();
		vita2d_draw_rectangle(0, 0, 960, 544, RGBA8(54, 57, 62, 255)); // Background
		
		
		
		/// SIDEPANEL
		// BG
		vita2d_draw_rectangle(0, 30, 230, 449, RGBA8(46, 49, 54, 255));
		
		// CHANNELS
		logSD("loop draw channel boxes");
		for(int i = 0 ; i < channelBoxes.size() ; i++){
			if(channelScrollY + i * CHANNEL_HEIGHT < MAX_DRAW_HEIGHT && channelScrollY + i * CHANNEL_HEIGHT > MIN_DRAW_HEIGHT){
				logSD("adding channelbox");
				//vita2d_draw_rectangle(channelScrollX + 4, 100 + channelScrollY + i * CHANNEL_HEIGHT, 222 , CHANNEL_HEIGHT, RGBA8(48, 50, 55, 255));
				//vita2d_pgf_draw_text(pgf, channelScrollX + 256, channelScrollY + i * 128 + 64, RGBA8(255,255,255,255), 3.0f, discordPtr->guilds[discordPtr->currentGuild].channels[i].name.c_str());
				logSD("Channelname:");
				logSD(discordPtr->guilds[discordPtr->currentGuild].channels[i].name);
				std::string channelName = discordPtr->guilds[discordPtr->currentGuild].channels[i].name;
				vita2d_font_draw_text(vita2dFont[18] , channelScrollX + 8, 100 + channelScrollY + i * CHANNEL_HEIGHT + CHANNEL_HEIGHT, RGBA8(255,255,255,255), CHANNEL_TITLE_TEXT_SIZE_PIXEL, channelName.c_str());
				//vita2d_pgf_draw_text(pgf, channelScrollX + 256, channelScrollY + i * 128 + 96, RGBA8(255,255,255,255), 1.0f, discordPtr->guilds[discordPtr->currentGuild].channels[i].topic.c_str());
				//logSD("topic:");
				//logSD(discordPtr->guilds[discordPtr->currentGuild].channels[i].topic);
				//std::string channelTopic = discordPtr->guilds[discordPtr->currentGuild].channels[i].topic;
				//vita2d_font_draw_text(vita2dFont[14] , channelScrollX + 180, channelScrollY + i * 128 + 96, RGBA8(255,255,255,255), CHANNEL_TOPIC_TEXT_SIZE_PIXEL, channelTopic.c_str());
			}
		}
		
		// TOP sidepanel to hide guilds underneath
		vita2d_draw_rectangle(0, 0, 230, 100, RGBA8(46, 49, 54, 255));
		vita2d_draw_rectangle(0, 99, 230, 1, RGBA8(5, 5, 6, 255));
		
		// BOTTOM SIDEPANEL
		vita2d_draw_rectangle(0, 479, 230, 1, RGBA8(5, 5, 6, 255));
		vita2d_draw_rectangle(0, 480, 230, 64, RGBA8(40, 43, 48, 255));
		vita2d_draw_texture(sidepanelStateIconImage, 14, 493); // sidepanelStateIconImage = user icon or Vitacord-default-usericon.png
		vita2d_font_draw_text(vita2dFont[18], 70, 514, RGBA8(255, 255, 255, 255), 18, panelUsername.c_str());
		vita2d_font_draw_text(vita2dFont[15], 70, 530, RGBA8(255, 255, 255, 255), 15, panelUserDiscriminator.c_str()); // create a vita2dfont for each font-size or your font will get messed up.
		
		vita2d_draw_texture_scale(dmIconImage , 128 , 30 , 0.5f , 0.5f); // DM ICON 
		
		
		// maybe add something on the big right 
		
		/// STATBAR
		vita2d_draw_rectangle(0, 0, 960, 30, RGBA8(242, 101, 34, 163));
		vita2d_draw_texture(statbarIconImage, 10, 7); // statbarIconImage = Vitacord-statbar-icon.png
		
	}else if(state == 4){
		setMessageBoxes();
		vita2d_draw_rectangle(0, 0, 960, 544, RGBA8(54, 57, 62, 255)); // Background
		
		
		/// SIDEPANEL
		// BG
		vita2d_draw_rectangle(0, 30, 230, 449, RGBA8(46, 49, 54, 255));
		
		
		
		//CHANNELS AND AFTER THAT MESSAGES
		
		for(int i = 0 ; i < channelBoxes.size() ; i++){
			if(channelScrollY + i * CHANNEL_HEIGHT < MAX_DRAW_HEIGHT && channelScrollY + i * CHANNEL_HEIGHT > MIN_DRAW_HEIGHT){
				logSD("adding channelbox");
				//vita2d_draw_rectangle(channelScrollX + 4, 100 + channelScrollY + i * CHANNEL_HEIGHT, 222 , CHANNEL_HEIGHT, RGBA8(48, 50, 55, 255));
				//vita2d_pgf_draw_text(pgf, channelScrollX + 256, channelScrollY + i * 128 + 64, RGBA8(255,255,255,255), 3.0f, discordPtr->guilds[discordPtr->currentGuild].channels[i].name.c_str());
				logSD("Channelname:");
				logSD(discordPtr->guilds[discordPtr->currentGuild].channels[i].name);
				std::string channelName = discordPtr->guilds[discordPtr->currentGuild].channels[i].name;
				vita2d_font_draw_text(vita2dFont[18] , channelScrollX + 8, 100 + channelScrollY + i * CHANNEL_HEIGHT + CHANNEL_HEIGHT, RGBA8(255,255,255,255), CHANNEL_TITLE_TEXT_SIZE_PIXEL, channelName.c_str());
				//vita2d_pgf_draw_text(pgf, channelScrollX + 256, channelScrollY + i * 128 + 96, RGBA8(255,255,255,255), 1.0f, discordPtr->guilds[discordPtr->currentGuild].channels[i].topic.c_str());
				//logSD("topic:");
				//logSD(discordPtr->guilds[discordPtr->currentGuild].channels[i].topic);
				//std::string channelTopic = discordPtr->guilds[discordPtr->currentGuild].channels[i].topic;
				//vita2d_font_draw_text(vita2dFont[14] , channelScrollX + 180, channelScrollY + i * 128 + 96, RGBA8(255,255,255,255), CHANNEL_TOPIC_TEXT_SIZE_PIXEL, channelTopic.c_str());
			}
		}
		// MESSAGES
		   int yPos = 0,height;
		   int messageBoxesAmount = messageBoxes.size();
		   int currentHeights = 0;
		//for(int i =  messageBoxes.size() ; i >= 0  ; i--){
		for(int i =  0 ; i < messageBoxesAmount ; i++){
			yPos = messageScrollY + 40;
			if(yPos < MAX_DRAW_HEIGHT && yPos > MIN_DRAW_HEIGHT){
				height = messageBoxes[i].messageHeight;
				vita2d_draw_rectangle(240, yPos + height, 710, 2, RGBA8(62, 65, 70, 255)); // two small lines to outline the message panel
				vita2d_draw_rectangle(240, yPos + height, 710, 1, RGBA8(51, 53, 55, 255)); // no need for a panel image
				vita2d_font_draw_text(vita2dFont[15], 283, yPos + 26, RGBA8(255, 255, 255, 255), 15, messageBoxes[i].username.c_str());
				vita2d_font_draw_text(vita2dFont[15], 293, yPos + 50, RGBA8(255, 255, 255, 255), 15, messageBoxes[i].content.c_str());
				//vita2d_draw_texture( guildsBGImage , messageScrollX + 128 , messageScrollY + i * 128);
				//vita2d_pgf_draw_text(pgf, messageScrollX + 256, messageScrollY + i * 128 + 96, RGBA8(255,255,255,255), 1.0f, discordPtr->guilds[discordPtr->currentGuild].channels[discordPtr->currentChannel].messages[i].content.c_str());
				//vita2d_font_draw_text(vita2dFont , messageScrollX + 150, messageScrollY + i * 128 + 32, RGBA8(255,255,255,255), MESSAGE_AUTHOR_TEXT_SIZE_PIXEL, discordPtr->guilds[discordPtr->currentGuild].channels[discordPtr->currentChannel].messages[i].author.username.c_str());
				//vita2d_font_draw_text(vita2dFont , messageScrollX + 160, messageScrollY + i * 128 + 96, RGBA8(255,255,255,255), MESSAGE_CONTENT_TEXT_SIZE_PIXEL, discordPtr->guilds[discordPtr->currentGuild].channels[discordPtr->currentChannel].messages[i].content.c_str());
				//vita2d_font_draw_text(vita2dFont[15] , messageScrollX + 150, messageScrollY + i * 128 + 32, RGBA8(255,255,255,255), MESSAGE_AUTHOR_TEXT_SIZE_PIXEL, messageBoxes[i].username.c_str());
				//vita2d_font_draw_text(vita2dFont[30] , messageScrollX + 160, messageScrollY + i * 128 + 96, RGBA8(255,255,255,255), MESSAGE_CONTENT_TEXT_SIZE_PIXEL, messageBoxes[i].content.c_str());
			}
			for(int emo = 0; emo < discordPtr->guilds[discordPtr->currentGuild].channels[discordPtr->currentChannel].messages[i].emojis.size() ; emo++){
				int in = discordPtr->guilds[discordPtr->currentGuild].channels[discordPtr->currentChannel].messages[i].emojis[emo].index ;
				if(emojis[in].icon != NULL){
					if(emojis[in].id == discordPtr->guilds[discordPtr->currentGuild].channels[discordPtr->currentChannel].messages[i].emojis[emo].codepoint){
						
						vita2d_draw_texture(emojis[in].icon , messageScrollX + 160 + MESSAGE_CONTENT_TEXT_SIZE_PIXEL * discordPtr->guilds[discordPtr->currentGuild].channels[discordPtr->currentChannel].messages[i].emojis[emo].x , messageScrollY + i * 128 + 96);
						
					}
				}
			}
			
			yPos += height; // add message height to yPos
		}
		
		// TOP sidepanel to hide guilds underneath
		vita2d_draw_rectangle(0, 0, 230, 100, RGBA8(46, 49, 54, 255));
		vita2d_draw_rectangle(0, 99, 230, 1, RGBA8(5, 5, 6, 255));
		
		// BOTTOM SIDEPANEL
		vita2d_draw_rectangle(0, 479, 230, 1, RGBA8(5, 5, 6, 255));
		vita2d_draw_rectangle(0, 480, 230, 64, RGBA8(40, 43, 48, 255));
		vita2d_draw_texture(sidepanelStateIconImage, 14, 493); // sidepanelStateIconImage = user icon or Vitacord-default-usericon.png
		vita2d_font_draw_text(vita2dFont[18], 70, 514, RGBA8(255, 255, 255, 255), 18, panelUsername.c_str());
		vita2d_font_draw_text(vita2dFont[15], 70, 530, RGBA8(255, 255, 255, 255), 15, panelUserDiscriminator.c_str()); // create a vita2dfont for each font-size or your font will get messed up.
		
		vita2d_draw_texture_scale(dmIconImage , 128 , 30 , 0.5f , 0.5f); // DM ICON 
		
		
		// maybe add something on the big right 
		
		/// STATBAR
		vita2d_draw_rectangle(0, 0, 960, 30, RGBA8(242, 101, 34, 163));
		vita2d_draw_texture(statbarIconImage, 10, 7); // statbarIconImage = Vitacord-statbar-icon.png
		
		// MESSAGEINPUT
		vita2d_draw_texture(messageInputImage, 230, 473);
		
	}else if(state == 6){
		setDirectMessageBoxes();
		vita2d_draw_rectangle(0, 0, 960, 544, RGBA8(114, 137, 217, 255));
		
		for(int i = 0 ; i < directMessageBoxes.size() ; i++){
			if(directMessageScrollY + i * 128 < MAX_DRAW_HEIGHT && directMessageScrollY + i * 128 > MIN_DRAW_HEIGHT){
				vita2d_draw_texture( guildsBGImage , directMessageScrollX + 128 , directMessageScrollY + i * 128);
				//vita2d_pgf_draw_text(pgf, directMessageScrollX + 256, directMessageScrollY + i * 128 + 96, RGBA8(255,255,255,255), 1.0f, discordPtr->guilds[discordPtr->currentGuild].channels[discordPtr->currentChannel].messages[i].content.c_str());
				vita2d_font_draw_text(vita2dFontSmall , directMessageScrollX + 150, directMessageScrollY + i * 128 + 96, RGBA8(255,255,255,255), MESSAGE_AUTHOR_TEXT_SIZE_PIXEL, discordPtr->directMessages[i].recipients[0].username.c_str());
			}
		}
		
		vita2d_draw_texture(dmIconImage , 0 , 0);
		
	}else if(state == 7){
		setDirectMessageMessagesBoxes();
		vita2d_draw_rectangle(0, 0, 960, 544, RGBA8(114, 137, 217, 255));
		for(int i = 0 ; i < directMessageMessagesBoxes.size() ; i++){
			if(directMessageMessagesScrollY + i * 128 < MAX_DRAW_HEIGHT && directMessageMessagesScrollY + i * 128 > MIN_DRAW_HEIGHT){
				vita2d_draw_texture( guildsBGImage , directMessageMessagesScrollX + 128 , directMessageMessagesScrollY + i * 128);
				//vita2d_pgf_draw_text(pgf, directMessageMessagesScrollX + 256, directMessageMessagesScrollY + i * 128 + 96, RGBA8(255,255,255,255), 1.0f, discordPtr->guilds[discordPtr->currentGuild].channels[discordPtr->currentChannel].messages[i].content.c_str());
				vita2d_font_draw_text(vita2dFontSmall , directMessageMessagesScrollX + 150, directMessageMessagesScrollY + i * 128 + 32, RGBA8(255,255,255,255), MESSAGE_AUTHOR_TEXT_SIZE_PIXEL, discordPtr->directMessages[discordPtr->currentDirectMessage].messages[i].author.username.c_str());
				vita2d_font_draw_text(vita2dFontNormal , directMessageMessagesScrollX + 160, directMessageMessagesScrollY + i * 128 + 96, RGBA8(255,255,255,255), MESSAGE_CONTENT_TEXT_SIZE_PIXEL, discordPtr->directMessages[discordPtr->currentDirectMessage].messages[i].content.c_str());
			}
		}
		
		vita2d_draw_texture(dmIconImage , 0 , 0);
		
	}else if(state == 9){
		vita2d_draw_rectangle(0, 0, 960, 544, RGBA8(114, 137, 217, 255));
		int i = 0;
		for( i = 0; i < rectangles.size() ; i++){
			vita2d_draw_rectangle(rectangles[i].x, rectangles[i].y, rectangles[i].w, rectangles[i].h, rectangles[i].color);
		}
	}

	
	vita2d_end_drawing();
	vita2d_swap_buffers();
}

int VitaGUI::scroll(int x , int y , int posx , int posy){
	if(state == 2){
		if(posx < 230 && posx > 0 && posy < 522 && posy > 22){
			guildScrollX = 0;
			guildScrollY += y;
			if(guildScrollY < guildScrollYMin)
				guildScrollY = guildScrollYMin;
			else if(guildScrollY > guildScrollYMax )
				guildScrollY = guildScrollYMax;
			
		}
		return 0;
	}else if(state == 3){
		if(posx < 230 && posx > 0 && posy < 522 && posy > 22){
			channelScrollX = 0;
			channelScrollY += y;
			if(channelScrollY < channelScrollYMin)
				channelScrollY = channelScrollYMin;
			else if(channelScrollY > channelScrollYMax )
				channelScrollY = channelScrollYMax;
		}
		return 0;
	}else if(state==4){
		if(posx < 230 && posx > 0 && posy < 522 && posy > 22){
			channelScrollX = 0;
			channelScrollY += y;
			if(channelScrollY < channelScrollYMin)
				channelScrollY = channelScrollYMin;
			else if(channelScrollY > channelScrollYMax )
				channelScrollY = channelScrollYMax;
		}else if (posx > 230){
			messageScrollX = 0;
			messageScrollY += y;
			if(messageScrollY < messageScrollYMin)
				messageScrollY = messageScrollYMin;
			else if(messageScrollY > messageScrollYMax )
				messageScrollY = messageScrollYMax;
		}
		return 0;
	}else if(state==6){
		directMessageScrollX = 0;
		directMessageScrollY += y;
		if(directMessageScrollY < directMessageScrollYMin)
			directMessageScrollY = directMessageScrollYMin;
		else if(directMessageScrollY > directMessageScrollYMax )
			directMessageScrollY = directMessageScrollYMax;
		return 0;
	}else if(state==7){
		directMessageMessagesScrollX = 0;
		directMessageMessagesScrollY += y;
		if(directMessageMessagesScrollY < directMessageMessagesScrollYMin)
			directMessageMessagesScrollY = directMessageMessagesScrollYMin;
		else if(directMessageMessagesScrollY > directMessageMessagesScrollYMax )
			directMessageMessagesScrollY = directMessageMessagesScrollYMax;
		return 0;
	}
	return -1;
}

int VitaGUI::click(int x , int y){
	if(state == 0){
		for(int i = 0 ; i < loginInputs.size() ; i++){
			if( x > loginInputs[i].x && x < loginInputs[i].x + loginInputs[i].w){
				if( y > loginInputs[i].y && y < loginInputs[i].y + loginInputs[i].h){
					return i;
				}
			}
		}
	}else if(state == 2){
		
		if(x > DMICONX && x < DMICONX2 && y > DMICONY && y < DMICONY2){
			return CLICKED_DM_ICON;
		}
		
		for(int i = 0 ; i < guildBoxes.size() ; i++){
			if( x  > guildBoxes[i].x && x  < guildBoxes[i].x + guildBoxes[i].w){
				if( y > guildBoxes[i].y && y  < guildBoxes[i].y + guildBoxes[i].h){
					return i;
				}
			}
		}
	}else if(state == 3){
		
		if(x > DMICONX && x < DMICONX2 && y > DMICONY && y < DMICONY2){
			return CLICKED_DM_ICON;
		}
		
		for(int i = 0 ; i < channelBoxes.size() ; i++){
			if( x  > channelBoxes[i].x && x  < channelBoxes[i].x + channelBoxes[i].w){
				if( y  > channelBoxes[i].y && y  < channelBoxes[i].y + channelBoxes[i].h){
					return i;
				}
			}
		}
	}else if(state == 4){
		
		
		if(x > DMICONX && x < DMICONX2 && y > DMICONY && y < DMICONY2){
			return CLICKED_DM_ICON;
		}
		
		
		
		
		for(int i = 0 ; i < channelBoxes.size() ; i++){
			if( x  > channelBoxes[i].x && x  < channelBoxes[i].x + channelBoxes[i].w){
				if( y  > channelBoxes[i].y && y  < channelBoxes[i].y + channelBoxes[i].h){
					return i;
				}
			}
		}
	}else if(state == 6){
		
		if(x > DMICONX && x < DMICONX2 && y > DMICONY && y < DMICONY2){
			return CLICKED_DM_ICON;
		}
		
		for(int i = 0 ; i < directMessageBoxes.size() ; i++){
			if( x  > directMessageBoxes[i].x && x  < directMessageBoxes[i].x + directMessageBoxes[i].w){
				if( y  > directMessageBoxes[i].y && y  < directMessageBoxes[i].y + directMessageBoxes[i].h){
					return i;
				}
			}
		}
	}else if(state == 7){
		
		if(x > DMICONX && x < DMICONX2 && y > DMICONY && y < DMICONY2){
			return CLICKED_DM_ICON;
		}
		
		// ? messages
	}
	return -1;
}

void VitaGUI::AddRectangle(float nx , float ny , float nw , float nh , unsigned int ncolor){
	rectangle r;
	r.x = nx;
	r.y = ny;
	r.w = nw;
	r.h = nh;
	r.color = ncolor;
	rectangles.push_back(r);
}
void VitaGUI::RemoveRectangle(int index){
	
	if(index < rectangles.size()){
		rectangles.erase(rectangles.begin()+index);
	}
	
}

int VitaGUI::GetState(){
	return state;
}
void VitaGUI::SetState(int s){
	lastState = state;
	state = s;
	
	if(state == 4){
		setMessageBoxes();
		messageScrollY = messageScrollYMin;
		
		messageScrollY = 0;
		guildScrollY = 0;
		directMessageMessagesScrollY = 0;
		directMessageScrollY = 0;
	}else{
		messageScrollY = 0;
		guildScrollY = 0;
		channelScrollY = 0;
		directMessageMessagesScrollY = 0;
		directMessageScrollY = 0;
	}
	

	
}
void VitaGUI::SetStateToLastState(){
	state = lastState;
}

void VitaGUI::passDiscordPointer(Discord *ptr){
	discordPtr = ptr;
}
void VitaGUI::setGuildBoxes(){
	guildBoxes.clear();
	for(int i = 0; i < discordPtr->guilds.size() ; i++){
		box boxG;
		boxG.x = guildScrollX ;
		boxG.y = 100 + guildScrollY + i * GUILD_HEIGHT;
		boxG.w = 230;
		boxG.h = GUILD_HEIGHT;
		guildBoxes.push_back(boxG);
	}
	guildScrollYMin = -((discordPtr->guilds.size()-1)*GUILD_HEIGHT);
}
void VitaGUI::setChannelBoxes(){
	channelBoxes.clear();
	for(int i = 0; i < discordPtr->guilds[discordPtr->currentGuild].channels.size() ; i++){
		box boxC;
		boxC.x = channelScrollX ;
		boxC.y = 100 + channelScrollY + i * CHANNEL_HEIGHT;
		boxC.w = 230;
		boxC.h = CHANNEL_HEIGHT;
		channelBoxes.push_back(boxC);
	}
	channelScrollYMin = -((discordPtr->guilds[discordPtr->currentGuild].channels.size()-1)*128);
}
void VitaGUI::setMessageBoxes(){
		
	int topMargin = 12;
	int bottomMargin = 8;
	int textHeight = 0;
	int allHeight = 0;
	if(!discordPtr->refreshingMessages && discordPtr->refreshedMessages){
		discordPtr->refreshedMessages = false;
		messageBoxes.clear();
		std::reverse(discordPtr->guilds[discordPtr->currentGuild].channels[discordPtr->currentChannel].messages.begin() , discordPtr->guilds[discordPtr->currentGuild].channels[discordPtr->currentChannel].messages.end());
		for(int i = 0; i < discordPtr->guilds[discordPtr->currentGuild].channels[discordPtr->currentChannel].messages.size() ; i++){
			messagebox boxC;
			boxC.x = messageScrollX + 230;
			boxC.y = messageScrollY + i * 64;
			boxC.w = 730;
			boxC.h = 64;
			boxC.username = discordPtr->guilds[discordPtr->currentGuild].channels[discordPtr->currentChannel].messages[i].author.username;
			boxC.content = "";
			boxC.lineCount = wordWrap( discordPtr->guilds[discordPtr->currentGuild].channels[discordPtr->currentChannel].messages[i].content , 655 , boxC.content);
			textHeight = boxC.lineCount * vita2d_font_text_height(vita2dFont[15], 15, "H");
			boxC.messageHeight = max(64, textHeight + topMargin + bottomMargin);
			allHeight += boxC.messageHeight;
			messageBoxes.push_back(boxC);
		}
		messageScrollYMin =  -( (messageBoxes.size() - 1) * 64); //-( allHeight )
	}
}

int VitaGUI::wordWrap(std::string stringToWrap ,  int availableWidth , std::string &out ){
	
	int wordWidth = 0;
	int lineBreaks = 0;
	
	out="";
	std::istringstream iss{stringToWrap};
	// Read tokens from stream into vector (split at whitespace).
	std::vector<std::string> words{std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{}};
	
	int spaceLeft = availableWidth;
	for(int i = 0 ; i < words.size() ; i++){
		wordWidth = vita2d_font_text_width(vita2dFontNormal, MESSAGE_CONTENT_TEXT_SIZE_PIXEL, words[i].c_str());
		if(wordWidth + 1  > spaceLeft){
			words[i] = '\n' + words[i];
			lineBreaks++;
			spaceLeft = availableWidth - wordWidth;
		}else{
			spaceLeft = spaceLeft - ( wordWidth + 1 );
		}
		out += words[i];
	}
	
	
	return lineBreaks;
	
}

void VitaGUI::setDirectMessageBoxes(){
	directMessageBoxes.clear();
	for(int i = 0; i < discordPtr->directMessages.size() ; i++){
		box boxDM;
		boxDM.x = directMessageScrollX + 128;
		boxDM.y = directMessageScrollY + i * 128;
		boxDM.w = 832;
		boxDM.h = 128;
		directMessageBoxes.push_back(boxDM);
	}
	directMessageScrollYMin = -((discordPtr->directMessages.size()-1)*128 +64) ;
	
}

void VitaGUI::setDirectMessageMessagesBoxes(){
	directMessageMessagesBoxes.clear();
	for(int i = 0; i < discordPtr->directMessages[discordPtr->currentDirectMessage].messages.size() ; i++){
		box boxDMM;
		boxDMM.x = directMessageMessagesScrollX + 128;
		boxDMM.y = directMessageMessagesScrollY + i * 128;
		boxDMM.w = 832;
		boxDMM.h = 128;
		directMessageMessagesBoxes.push_back(boxDMM);
	}
	directMessageMessagesScrollYMax = -((discordPtr->directMessages[discordPtr->currentDirectMessage].messages.size()-1)*128) ;
	
}


void VitaGUI::setUserInfo(){
	
	panelUsername = discordPtr->username;
	panelUserDiscriminator = "#" + discordPtr->discriminator;
}




