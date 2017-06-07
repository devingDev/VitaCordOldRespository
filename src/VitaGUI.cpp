#include "VitaGUI.hpp"
#include "log.hpp"
#include <istream>
#include <sstream>
#include <iterator>

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
	
	vita2dFont = vita2d_load_font_file("app0:assets/font/droidsans.ttf");
	
	std::string bgPath = "app0:assets/images/Vitacord-Background-8BIT.png";
	backgroundImage = vita2d_load_PNG_file(bgPath.c_str());
	loginFormImage = vita2d_load_PNG_file("app0:assets/images/Vitacord-LoginForm-8BIT.png");
	loadingImage = vita2d_load_PNG_file("app0:assets/images/Vitacord-Loading-8BIT.png");
	guildsBGImage = vita2d_load_PNG_file("app0:assets/images/Vitacord-GuildsBG-8BIT.png");
	dmIconImage = vita2d_load_PNG_file("app0:assets/images/Vitacord-DMIcon-8BIT.png");
	
	inputbox emailI;
	emailI.x = 420;
	emailI.y = 105;
	emailI.w = 400;
	emailI.h = 55;
	loginInputs.push_back(emailI);
	
	inputbox passwordI;
	passwordI.x = 420;
	passwordI.y = 205;
	passwordI.w = 400;
	passwordI.h = 55;
	loginInputs.push_back(passwordI);
	
	inputbox loginI;
	loginI.x = 420;
	loginI.y = 370;
	loginI.w = 400;
	loginI.h = 70;
	loginInputs.push_back(loginI);
	
	loginTexts.push_back(" ");
	loginTexts.push_back(" ");
	
	emojis.push_back(emoji_icon());
	emojis[0].name = "frenchfries";
	emojis[0].id = 0x1f35f;
	emojis[0].icon = vita2d_load_PNG_file("app0:assets/emoji/emoji_1f35f.png");
	
	emojis.push_back(emoji_icon());
	emojis[1].name = "hamburger";
	emojis[1].id = 0x1f354;
	emojis[1].icon = vita2d_load_PNG_file("app0:assets/emoji/emoji_1f354.png");
	
}
VitaGUI::~VitaGUI(){
	vita2d_fini();
	vita2d_free_texture(backgroundImage);
	vita2d_free_texture(loginFormImage);
	vita2d_free_texture(loadingImage);
	vita2d_free_font(vita2dFont);
	//vita2d_free_pgf(pgf);
}
void VitaGUI::updateBoxes(){
	
	
}

void VitaGUI::Draw(){

	vita2d_start_drawing();
	vita2d_clear_screen();

	
	if(state == 0){
		vita2d_draw_texture( backgroundImage , 0 , 0);
		vita2d_draw_texture( loginFormImage , 0 , 0 );
		//vita2d_pgf_draw_text(pgf, 420, 154, RGBA8(255,255,255,255), 2.0f, loginTexts[0].c_str());
		//vita2d_pgf_draw_text(pgf, 420, 250, RGBA8(255,255,255,255), 2.0f, loginTexts[1].c_str());
		vita2d_font_draw_text(vita2dFont , 420, 154, RGBA8(255,255,255,255), 18, loginTexts[0].c_str());
		vita2d_font_draw_text(vita2dFont , 420, 250, RGBA8(255,255,255,255), 18, loginTexts[1].c_str());
		
	}else if(state == 1){
		vita2d_draw_texture( backgroundImage , 0 , 0);
		//vita2d_draw_texture_rotate(loginFormImage, 128 , 64, loadingImageAngle);
		vita2d_draw_texture_rotate(loadingImage, 416 , 208, loadingImageAngle);
		//vita2d_pgf_draw_text(pgf, 150, 300, RGBA8(255,255,255,255), 2.0f, loadingString.c_str());
		vita2d_font_draw_text(vita2dFont , 150, 300, RGBA8(255,255,255,255), 20, loadingString.c_str());
		loadingImageAngle += 0.08f;
		
	}else if(state == 2){
		setGuildBoxes();
		for(int i = 0 ; i < guildBoxes.size() ; i++){
			if(guildScrollY + i * 128 < MAX_DRAW_HEIGHT && guildScrollY + i * 128 > MIN_DRAW_HEIGHT){
				vita2d_draw_texture( guildsBGImage , guildScrollX + 128 , guildScrollY + i * 128);
				//vita2d_pgf_draw_text(pgf, guildScrollX + 256, guildScrollY + i * 128 + 96, RGBA8(255,255,255,255), 3.0f, discordPtr->guilds[i].name.c_str());
				vita2d_font_draw_text(vita2dFont , guildScrollX + 150, guildScrollY + i * 128 + 96, RGBA8(255,255,255,255), GUILD_TITLE_TEXT_SIZE_PIXEL, discordPtr->guilds[i].name.c_str());
			}
		}
		
		vita2d_draw_texture(dmIconImage , 0 , 0);
		
	}else if(state == 3){
		logSD("call setChannelBoxes");
		setChannelBoxes();
		
		logSD("loop draw channel boxes");
		for(int i = 0 ; i < channelBoxes.size() ; i++){
			if(channelScrollY + i * 128 < MAX_DRAW_HEIGHT && channelScrollY + i * 128 > MIN_DRAW_HEIGHT){
				logSD("adding channelbox");
				vita2d_draw_texture( guildsBGImage , channelScrollX + 128 , channelScrollY + i * 128);
				//vita2d_pgf_draw_text(pgf, channelScrollX + 256, channelScrollY + i * 128 + 64, RGBA8(255,255,255,255), 3.0f, discordPtr->guilds[discordPtr->currentGuild].channels[i].name.c_str());
				logSD("Channelname:");
				logSD(discordPtr->guilds[discordPtr->currentGuild].channels[i].name);
				std::string channelName = discordPtr->guilds[discordPtr->currentGuild].channels[i].name;
				vita2d_font_draw_text(vita2dFont , channelScrollX + 150, channelScrollY + i * 128 + 64, RGBA8(255,255,255,255), CHANNEL_TITLE_TEXT_SIZE_PIXEL, channelName.c_str());
				//vita2d_pgf_draw_text(pgf, channelScrollX + 256, channelScrollY + i * 128 + 96, RGBA8(255,255,255,255), 1.0f, discordPtr->guilds[discordPtr->currentGuild].channels[i].topic.c_str());
				logSD("topic:");
				logSD(discordPtr->guilds[discordPtr->currentGuild].channels[i].topic);
				std::string channelTopic = discordPtr->guilds[discordPtr->currentGuild].channels[i].topic;
				vita2d_font_draw_text(vita2dFont , channelScrollX + 180, channelScrollY + i * 128 + 96, RGBA8(255,255,255,255), CHANNEL_TOPIC_TEXT_SIZE_PIXEL, channelTopic.c_str());
			}
		}
		
		vita2d_draw_texture(dmIconImage , 0 , 0);
		
	}else if(state == 4){
		setMessageBoxes();
		
		for(int i = 0 ; i < messageBoxes.size() ; i++){
			if(messageScrollY + i * 128 < MAX_DRAW_HEIGHT && messageScrollY + i * 128 > MIN_DRAW_HEIGHT){
				vita2d_draw_texture( guildsBGImage , messageScrollX + 128 , messageScrollY + i * 128);
				//vita2d_pgf_draw_text(pgf, messageScrollX + 256, messageScrollY + i * 128 + 96, RGBA8(255,255,255,255), 1.0f, discordPtr->guilds[discordPtr->currentGuild].channels[discordPtr->currentChannel].messages[i].content.c_str());
				//vita2d_font_draw_text(vita2dFont , messageScrollX + 150, messageScrollY + i * 128 + 32, RGBA8(255,255,255,255), MESSAGE_AUTHOR_TEXT_SIZE_PIXEL, discordPtr->guilds[discordPtr->currentGuild].channels[discordPtr->currentChannel].messages[i].author.username.c_str());
				//vita2d_font_draw_text(vita2dFont , messageScrollX + 160, messageScrollY + i * 128 + 96, RGBA8(255,255,255,255), MESSAGE_CONTENT_TEXT_SIZE_PIXEL, discordPtr->guilds[discordPtr->currentGuild].channels[discordPtr->currentChannel].messages[i].content.c_str());
				vita2d_font_draw_text(vita2dFont , messageScrollX + 150, messageScrollY + i * 128 + 32, RGBA8(255,255,255,255), MESSAGE_AUTHOR_TEXT_SIZE_PIXEL, messageBoxes[i].username.c_str());
				vita2d_font_draw_text(vita2dFont , messageScrollX + 160, messageScrollY + i * 128 + 96, RGBA8(255,255,255,255), MESSAGE_CONTENT_TEXT_SIZE_PIXEL, messageBoxes[i].content.c_str());
			}
			for(int emo = 0; emo < discordPtr->guilds[discordPtr->currentGuild].channels[discordPtr->currentChannel].messages[i].emojis.size() ; emo++){
				
				for(int xFail = 0 ; xFail < emojis.size() ; xFail++){
					//criticalLogSD(" draw searching for emoji!");
					if(emojis[xFail].id == discordPtr->guilds[discordPtr->currentGuild].channels[discordPtr->currentChannel].messages[i].emojis[emo].codepoint){
						//criticalLogSD("drwa emoji matches code!");
						if(emojis[xFail].icon != NULL){
							//criticalLogSD("draw emoji not empty!");
							vita2d_draw_texture(emojis[xFail].icon , messageScrollX + 160 + MESSAGE_CONTENT_TEXT_SIZE_PIXEL * discordPtr->guilds[discordPtr->currentGuild].channels[discordPtr->currentChannel].messages[i].emojis[emo].x , messageScrollY + i * 128 + 96);
						}
					}
				}
				
			}
		}
		
		vita2d_draw_texture(dmIconImage , 0 , 0);
		
	}else if(state == 6){
		setDirectMessageBoxes();
		
		for(int i = 0 ; i < directMessageBoxes.size() ; i++){
			if(directMessageScrollY + i * 128 < MAX_DRAW_HEIGHT && directMessageScrollY + i * 128 > MIN_DRAW_HEIGHT){
				vita2d_draw_texture( guildsBGImage , directMessageScrollX + 128 , directMessageScrollY + i * 128);
				//vita2d_pgf_draw_text(pgf, directMessageScrollX + 256, directMessageScrollY + i * 128 + 96, RGBA8(255,255,255,255), 1.0f, discordPtr->guilds[discordPtr->currentGuild].channels[discordPtr->currentChannel].messages[i].content.c_str());
				vita2d_font_draw_text(vita2dFont , directMessageScrollX + 150, directMessageScrollY + i * 128 + 96, RGBA8(255,255,255,255), MESSAGE_AUTHOR_TEXT_SIZE_PIXEL, discordPtr->directMessages[i].recipients[0].username.c_str());
			}
		}
		
		vita2d_draw_texture(dmIconImage , 0 , 0);
		
	}else if(state == 7){
		setDirectMessageMessagesBoxes();
		
		for(int i = 0 ; i < directMessageMessagesBoxes.size() ; i++){
			if(directMessageMessagesScrollY + i * 128 < MAX_DRAW_HEIGHT && directMessageMessagesScrollY + i * 128 > MIN_DRAW_HEIGHT){
				vita2d_draw_texture( guildsBGImage , directMessageMessagesScrollX + 128 , directMessageMessagesScrollY + i * 128);
				//vita2d_pgf_draw_text(pgf, directMessageMessagesScrollX + 256, directMessageMessagesScrollY + i * 128 + 96, RGBA8(255,255,255,255), 1.0f, discordPtr->guilds[discordPtr->currentGuild].channels[discordPtr->currentChannel].messages[i].content.c_str());
				vita2d_font_draw_text(vita2dFont , directMessageMessagesScrollX + 150, directMessageMessagesScrollY + i * 128 + 32, RGBA8(255,255,255,255), MESSAGE_AUTHOR_TEXT_SIZE_PIXEL, discordPtr->directMessages[discordPtr->currentDirectMessage].messages[i].author.username.c_str());
				vita2d_font_draw_text(vita2dFont , directMessageMessagesScrollX + 160, directMessageMessagesScrollY + i * 128 + 96, RGBA8(255,255,255,255), MESSAGE_CONTENT_TEXT_SIZE_PIXEL, discordPtr->directMessages[discordPtr->currentDirectMessage].messages[i].content.c_str());
			}
		}
		
		vita2d_draw_texture(dmIconImage , 0 , 0);
		
	}else if(state == 9){
		int i = 0;
		for( i = 0; i < rectangles.size() ; i++){
			vita2d_draw_rectangle(rectangles[i].x, rectangles[i].y, rectangles[i].w, rectangles[i].h, rectangles[i].color);
		}
	}

	
	vita2d_end_drawing();
	vita2d_swap_buffers();
}

int VitaGUI::scroll(int x , int y){
	if(state == 2){
		guildScrollX = 0;
		guildScrollY += y;
		if(guildScrollY < guildScrollYMin)
			guildScrollY = guildScrollYMin;
		else if(guildScrollY > guildScrollYMax )
			guildScrollY = guildScrollYMax;
		return 0;
	}else if(state == 3){
		channelScrollX = 0;
		channelScrollY += y;
		if(channelScrollY < channelScrollYMin)
			channelScrollY = channelScrollYMin;
		else if(channelScrollY > channelScrollYMax )
			channelScrollY = channelScrollYMax;
		return 0;
	}else if(state==4){
		messageScrollX = 0;
		messageScrollY += y;
		if(messageScrollY < messageScrollYMin)
			messageScrollY = messageScrollYMin;
		else if(messageScrollY > messageScrollYMax )
			messageScrollY = messageScrollYMax;
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
		
		if(x > 0 && x < 128 && y > 0 && y < 128){
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
		
		if(x > 0 && x < 128 && y > 0 && y < 128){
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
		if(x > 0 && x < 128 && y > 0 && y < 128){
			return CLICKED_DM_ICON;
		}
		
		
	}else if(state == 6){
		
		if(x > 0 && x < 128 && y > 0 && y < 128){
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
		
		if(x > 0 && x < 128 && y > 0 && y < 128){
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
		boxG.x = guildScrollX + 128;
		boxG.y = guildScrollY + i * 128;
		boxG.w = 832;
		boxG.h = 128;
		guildBoxes.push_back(boxG);
	}
	guildScrollYMin = -((discordPtr->guilds.size()-1)*128);
}
void VitaGUI::setChannelBoxes(){
	channelBoxes.clear();
	for(int i = 0; i < discordPtr->guilds[discordPtr->currentGuild].channels.size() ; i++){
		box boxC;
		boxC.x = channelScrollX + 128;
		boxC.y = channelScrollY + i * 128;
		boxC.w = 832;
		boxC.h = 128;
		channelBoxes.push_back(boxC);
	}
	channelScrollYMin = -((discordPtr->guilds[discordPtr->currentGuild].channels.size()-1)*128);
}
void VitaGUI::setMessageBoxes(){
	if(!discordPtr->refreshingMessages){
		messageBoxes.clear();
		for(int i = 0; i < discordPtr->guilds[discordPtr->currentGuild].channels[discordPtr->currentChannel].messages.size() ; i++){
			messagebox boxC;
			boxC.x = messageScrollX + 128;
			boxC.y = messageScrollY + i * 128;
			boxC.w = 832;
			boxC.h = 128;
			boxC.username = discordPtr->guilds[discordPtr->currentGuild].channels[discordPtr->currentChannel].messages[i].author.username;
			boxC.content = wordWrap( discordPtr->guilds[discordPtr->currentGuild].channels[discordPtr->currentChannel].messages[i].content , boxC.w);
			messageBoxes.push_back(boxC);
		}
		messageScrollYMin = -((discordPtr->guilds[discordPtr->currentGuild].channels[discordPtr->currentChannel].messages.size()-1)*128 ) ;
	}
}

std::string VitaGUI::wordWrap(std::string stringToWrap , int availableWidth){
	
	int wordWidth = 0;
	
	std::string wrappedText="";
	std::istringstream iss{stringToWrap};
	// Read tokens from stream into vector (split at whitespace).
	std::vector<std::string> words{std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{}};
	
	int spaceLeft = availableWidth;
	for(int i = 0 ; i < words.size() ; i++){
		wordWidth = vita2d_font_text_width(vita2dFont, MESSAGE_CONTENT_TEXT_SIZE_PIXEL, words[i].c_str());
		if(wordWidth + 1  > spaceLeft){
			words[i] = '\n' + words[i];
			spaceLeft = availableWidth - wordWidth;
		}else{
			spaceLeft = spaceLeft - ( wordWidth + 1 );
		}
		wrappedText += words[i];
	}
	
	
	return wrappedText;
	
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




