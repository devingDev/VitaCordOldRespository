#include "VitaGUI.hpp"
#include "log.hpp"

void VitaGUI::NextFont(){
	
	
	currentFont ++;
	if(currentFont > 4){
		currentFont = 0;
	}else if(currentFont < 0){
		currentFont = 0;
	}
	
	switch(currentFont){
		case 0:
			vita2dFont = vita2dFontSymbola;
			break;
		case 1:
			vita2dFont = vita2dFontSymbolaHint;
			break;
		case 2:
			vita2dFont = vita2dFontSeguiemEmoji;
			break;
		case 3:
			vita2dFont = vita2dFontLastResort;
			break;	
		case 4:
			vita2dFont = vita2dFontOpenSansEmoji;
			break;	
		default:
			vita2dFont = vita2dFontOpenSansEmoji;
			break;
	}
}

VitaGUI::VitaGUI(){
	vita2d_init();
	vita2d_set_clear_color(RGBA8(0x40, 0x40, 0x40, 0xFF));
	//pgf = vita2d_load_default_pgf();
	
	//pgf = vita2d_load_custom_pgf("app0:assets/font/seguiemj.pgf");
	vita2dFontSymbola = vita2d_load_font_file("app0:assets/font/symbola.ttf");
	vita2dFontSymbolaHint = vita2d_load_font_file("app0:assets/font/symbolahint.ttf");
	vita2dFontSeguiemEmoji = vita2d_load_font_file("app0:assets/font/seguiemj.ttf");
	vita2dFontLastResort = vita2d_load_font_file("app0:assets/font/lastresort.ttf");
	vita2dFontOpenSansEmoji = vita2d_load_font_file("app0:assets/font/opensansemoji.ttf");
	
	vita2dFont = vita2dFontSymbola;
	
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
		vita2d_font_draw_text(vita2dFont , 420, 154, RGBA8(255,255,255,255), 20, loginTexts[0].c_str());
		vita2d_font_draw_text(vita2dFont , 420, 250, RGBA8(255,255,255,255), 20, loginTexts[1].c_str());
		
	}else if(state == 1){
		vita2d_draw_texture( backgroundImage , 0 , 0);
		//vita2d_draw_texture_rotate(loginFormImage, 128 , 64, loadingImageAngle);
		vita2d_draw_texture_rotate(loadingImage, 416 , 208, loadingImageAngle);
		//vita2d_pgf_draw_text(pgf, 150, 300, RGBA8(255,255,255,255), 2.0f, loadingString.c_str());
		vita2d_font_draw_text(vita2dFont , 150, 300, RGBA8(255,255,255,255), 20, loadingString.c_str());
		loadingImageAngle ++;
		
	}else if(state == 2){
		setGuildBoxes();
		for(int i = 0 ; i < guildBoxes.size() ; i++){
			vita2d_draw_texture( guildsBGImage , guildScrollX + 128 , guildScrollY + i * 128);
			//vita2d_pgf_draw_text(pgf, guildScrollX + 256, guildScrollY + i * 128 + 96, RGBA8(255,255,255,255), 3.0f, discordPtr->guilds[i].name.c_str());
		vita2d_font_draw_text(vita2dFont , guildScrollX + 256, guildScrollY + i * 128 + 96, RGBA8(255,255,255,255), 30, discordPtr->guilds[i].name.c_str());
		}
		
		vita2d_draw_texture(dmIconImage , 0 , 0);
		
	}else if(state == 3){
		setChannelBoxes();
		
		for(int i = 0 ; i < channelBoxes.size() ; i++){
			vita2d_draw_texture( guildsBGImage , channelScrollX + 128 , channelScrollY + i * 128);
			//vita2d_pgf_draw_text(pgf, channelScrollX + 256, channelScrollY + i * 128 + 64, RGBA8(255,255,255,255), 3.0f, discordPtr->guilds[discordPtr->currentGuild].channels[i].name.c_str());
			vita2d_font_draw_text(vita2dFont , channelScrollX + 256, channelScrollY + i * 128 + 64, RGBA8(255,255,255,255), 30, discordPtr->guilds[discordPtr->currentGuild].channels[i].name.c_str());
			//vita2d_pgf_draw_text(pgf, channelScrollX + 256, channelScrollY + i * 128 + 96, RGBA8(255,255,255,255), 1.0f, discordPtr->guilds[discordPtr->currentGuild].channels[i].topic.c_str());
			vita2d_font_draw_text(vita2dFont , channelScrollX + 256, channelScrollY + i * 128 + 96, RGBA8(255,255,255,255), 10, discordPtr->guilds[discordPtr->currentGuild].channels[i].topic.c_str());
		}
		
		vita2d_draw_texture(dmIconImage , 0 , 0);
		
	}else if(state == 4){
		setMessageBoxes();
		
		for(int i = 0 ; i < messageBoxes.size() ; i++){
			vita2d_draw_texture( guildsBGImage , messageScrollX + 128 , messageScrollY + i * 128);
			//vita2d_pgf_draw_text(pgf, messageScrollX + 256, messageScrollY + i * 128 + 96, RGBA8(255,255,255,255), 1.0f, discordPtr->guilds[discordPtr->currentGuild].channels[discordPtr->currentChannel].messages[i].content.c_str());
			vita2d_font_draw_text(vita2dFont , messageScrollX + 256, messageScrollY + i * 128 + 32, RGBA8(255,255,255,255), 10, discordPtr->guilds[discordPtr->currentGuild].channels[discordPtr->currentChannel].messages[i].content.c_str());
			vita2d_font_draw_text(vita2dFont , messageScrollX + 256, messageScrollY + i * 128 + 96, RGBA8(255,255,255,255), 20, discordPtr->guilds[discordPtr->currentGuild].channels[discordPtr->currentChannel].messages[i].content.c_str());
		}
		
		vita2d_draw_texture(dmIconImage , 0 , 0);
		
	}else if(state == 6){
		setDirectMessageBoxes();
		
		for(int i = 0 ; i < directMessageBoxes.size() ; i++){
			vita2d_draw_texture( guildsBGImage , directMessageScrollX + 128 , directMessageScrollY + i * 128);
			//vita2d_pgf_draw_text(pgf, directMessageScrollX + 256, directMessageScrollY + i * 128 + 96, RGBA8(255,255,255,255), 1.0f, discordPtr->guilds[discordPtr->currentGuild].channels[discordPtr->currentChannel].messages[i].content.c_str());
			vita2d_font_draw_text(vita2dFont , directMessageScrollX + 256, directMessageScrollY + i * 128 + 96, RGBA8(255,255,255,255), 20, discordPtr->directMessages[i].recipients[0].username.c_str());
		}
		
		vita2d_draw_texture(dmIconImage , 0 , 0);
		
	}else if(state == 7){
		setDirectMessageMessagesBoxes();
		
		for(int i = 0 ; i < directMessageMessagesBoxes.size() ; i++){
			vita2d_draw_texture( guildsBGImage , directMessageMessagesScrollX + 128 , directMessageMessagesScrollY + i * 128);
			//vita2d_pgf_draw_text(pgf, directMessageMessagesScrollX + 256, directMessageMessagesScrollY + i * 128 + 96, RGBA8(255,255,255,255), 1.0f, discordPtr->guilds[discordPtr->currentGuild].channels[discordPtr->currentChannel].messages[i].content.c_str());
			vita2d_font_draw_text(vita2dFont , directMessageMessagesScrollX + 256, directMessageMessagesScrollY + i * 128 + 32, RGBA8(255,255,255,255), 10, discordPtr->directMessages[discordPtr->currentDirectMessage].recipients[0].username.c_str());
			vita2d_font_draw_text(vita2dFont , directMessageMessagesScrollX + 256, directMessageMessagesScrollY + i * 128 + 96, RGBA8(255,255,255,255), 20, discordPtr->directMessages[discordPtr->currentDirectMessage].messages[i].content.c_str());
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
	}else if(state==6){
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
	guildScrollYMin = -((discordPtr->guilds.size()-1)*128 +64);
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
	channelScrollYMin = -((discordPtr->guilds[discordPtr->currentGuild].channels.size()-1)*128 +64);
}
void VitaGUI::setMessageBoxes(){
	messageBoxes.clear();
	for(int i = 0; i < discordPtr->guilds[discordPtr->currentGuild].channels[discordPtr->currentChannel].messages.size() ; i++){
		box boxC;
		boxC.x = messageScrollX + 128;
		boxC.y = messageScrollY + i * 128;
		boxC.w = 832;
		boxC.h = 128;
		messageBoxes.push_back(boxC);
	}
	messageScrollYMin = -((discordPtr->guilds[discordPtr->currentGuild].channels[discordPtr->currentChannel].messages.size()-1)*128 +64) ;
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
	directMessageMessagesScrollYMax = -((discordPtr->directMessages[discordPtr->currentDirectMessage].messages.size()-1)*128 +64) ;
	
}




