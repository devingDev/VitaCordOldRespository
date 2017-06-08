#include "VitaGUI.hpp"
#include "log.hpp"
#include <istream>
#include <sstream>
#include <iterator>
#include <psp2/io/dirent.h>
#include <debugnet.h>


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
	
	debugNetPrintf(DEBUG, "Draw()\n");
	
	if(state == 2){
		
		debugNetPrintf(DEBUG, "Call SetGuildBoxes()\n");
		setGuildBoxes();
	} else if(state == 3){
		debugNetPrintf(DEBUG, "Call SetChannelBoxes()\n");
		setChannelBoxes();
	}else if(state == 4){
		debugNetPrintf(DEBUG, "Call SetChannel+MessageBoxes()\n");
		setChannelBoxes();
		setMessageBoxes();
	}else if(state == 6){
		
		debugNetPrintf(DEBUG, "Call SetDMBoxes()\n");
		setDirectMessageBoxes();
	}else if(state == 7){
		
		debugNetPrintf(DEBUG, "Call SetDM+MsgBoxes()\n");
		setDirectMessageBoxes();
		setDirectMessageMessagesBoxes();
	}
		
		debugNetPrintf(DEBUG, "All boxes set!\n");
	
	
	vita2d_start_drawing();
	vita2d_clear_screen();
	
	debugNetPrintf(DEBUG, "Check states\n");
	
	if(state == 0){
		
		DrawLoginScreen();
		
	}else if(state == 1){
		vita2d_draw_rectangle(0, 0, 960, 544, RGBA8(114, 137, 217, 255));
		//vita2d_draw_texture_rotate(loginFormImage, 128 , 64, loadingImageAngle);
		vita2d_draw_texture_rotate(loadingImage, 416 , 208, loadingImageAngle);
		//vita2d_pgf_draw_text(pgf, 150, 300, RGBA8(255,255,255,255), 2.0f, loadingString.c_str());
		vita2d_font_draw_text(vita2dFont[20] , 150, 300, RGBA8(255,255,255,255), 20, loadingString.c_str());
		loadingImageAngle += 0.08f;
		
	}else if(state == 2){
		
		vita2d_draw_rectangle(0, 0, 960, 544, RGBA8(54, 57, 62, 255)); // Background

		
		
		
		/// SIDEPANEL
		// BG
		vita2d_draw_rectangle(0, 30, 230, 449, RGBA8(46, 49, 54, 255));
		
		// GUILDS
		DrawGuildsOnSidebar();
		
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
		
		vita2d_draw_rectangle(0, 0, 960, 544, RGBA8(54, 57, 62, 255)); // Background
		
		
		
		/// SIDEPANEL
		// BG
		vita2d_draw_rectangle(0, 30, 230, 449, RGBA8(46, 49, 54, 255));
		
		// CHANNELS
		logSD("loop draw channel boxes");
		DrawChannelsOnSidebar();
		
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
		vita2d_draw_rectangle(0, 0, 960, 544, RGBA8(54, 57, 62, 255)); // Background
		
		
		/// SIDEPANEL
		// BG
		vita2d_draw_rectangle(0, 30, 230, 449, RGBA8(46, 49, 54, 255));
		
		
		
		//CHANNELS AND AFTER THAT MESSAGES
		
		DrawChannelsOnSidebar();
		
		// MESSAGES
		DrawMessages();
		
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

		vita2d_draw_rectangle(0, 0, 960, 544, RGBA8(54, 57, 62, 255)); // Background
		
		
		/// SIDEPANEL
		// BG
		vita2d_draw_rectangle(0, 30, 230, 449, RGBA8(46, 49, 54, 255));
		
		DrawDirectMessageUsersOnSidebar();
		
		
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
		
	}else if(state == 7){
		vita2d_draw_rectangle(0, 0, 960, 544, RGBA8(54, 57, 62, 255)); // Background
			
			
		/// SIDEPANEL
		// BG
		vita2d_draw_rectangle(0, 30, 230, 449, RGBA8(46, 49, 54, 255));
		
		DrawDirectMessageUsersOnSidebar();
		
		DrawDirectMessageMessages();
		
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
		
	}else if(state == 9){
		vita2d_draw_rectangle(0, 0, 960, 544, RGBA8(114, 137, 217, 255));
		int i = 0;
		for( i = 0; i < rectangles.size() ; i++){
			vita2d_draw_rectangle(rectangles[i].x, rectangles[i].y, rectangles[i].w, rectangles[i].h, rectangles[i].color);
		}
	}

	
	debugNetPrintf(DEBUG, "End of check states\n");
	
	vita2d_end_drawing();
	vita2d_swap_buffers();
}

int VitaGUI::scroll(int x , int y , int posx , int posy){
	debugNetPrintf(DEBUG, "Scroll GUI\n");
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
		if(posx < 230 && posx > 0 && posy < 522 && posy > 22){
			directMessageScrollX = 0;
			directMessageScrollY += y;
			
			if(directMessageScrollY < directMessageScrollYMin)
				directMessageScrollY = directMessageScrollYMin;
			else if(directMessageScrollY > directMessageScrollYMax )
				directMessageScrollY = directMessageScrollYMax;
		}

		return 0;
	}else if(state==7){
		
		if(posx < 230 && posx > 0 && posy < 522 && posy > 22){
			directMessageScrollX = 0;
			directMessageScrollY += y;
			
			if(directMessageScrollY < directMessageScrollYMin)
				directMessageScrollY = directMessageScrollYMin;
			else if(directMessageScrollY > directMessageScrollYMax )
				directMessageScrollY = directMessageScrollYMax;
		}
		if(posx> 230){
			directMessageMessagesScrollX = 0;
			directMessageMessagesScrollY += y;
			
			
			if(directMessageMessagesScrollY < directMessageMessagesScrollYMin)
				directMessageMessagesScrollY = directMessageMessagesScrollYMin;
			else if(directMessageMessagesScrollY > directMessageMessagesScrollYMax )
				directMessageMessagesScrollY = directMessageMessagesScrollYMax;
		}
		
		return 0;
	}
	return -1;
}




int VitaGUI::click(int x , int y){
	debugNetPrintf(DEBUG, "Click GUI\n");
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
		
		for(int i = 0 ; i < directMessageBoxes.size() ; i++){
			if( x  > directMessageBoxes[i].x && x  < directMessageBoxes[i].x + directMessageBoxes[i].w){
				if( y  > directMessageBoxes[i].y && y  < directMessageBoxes[i].y + directMessageBoxes[i].h){
					return i;
				}
			}
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
	debugNetPrintf(DEBUG, "SetState : %d\n" , state);
	
	if(state == 4){
		setMessageBoxes();
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
	guildScrollYMin = -((discordPtr->guilds.size()-1)*GUILD_HEIGHT - 300);
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
	channelScrollYMin = -((discordPtr->guilds[discordPtr->currentGuild].channels.size()-1)*128 - 300);
}
bool VitaGUI::setMessageBoxes(){
		
	int topMargin = 45;
	int bottomMargin = 18;
	int textHeight = 0;
	int allHeight = 0;
	if(!discordPtr->refreshingMessages && discordPtr->refreshedMessages){
		discordPtr->refreshedMessages = false;
		messageBoxes.clear();
		for(int i = 0; i < discordPtr->guilds[discordPtr->currentGuild].channels[discordPtr->currentChannel].messages.size() ; i++){
			messagebox boxC;
			boxC.x = messageScrollX + 230;
			boxC.y = messageScrollY + i * 64;
			boxC.username = discordPtr->guilds[discordPtr->currentGuild].channels[discordPtr->currentChannel].messages[i].author.username;
			boxC.content = "";
			boxC.lineCount = wordWrap( discordPtr->guilds[discordPtr->currentGuild].channels[discordPtr->currentChannel].messages[i].content , 655 , boxC.content);
			textHeight = boxC.lineCount * vita2d_font_text_height(vita2dFont[15], 15, boxC.content.c_str());
			boxC.messageHeight = max(64, textHeight + topMargin + bottomMargin);
			allHeight += boxC.messageHeight;
			
			
			boxC.w = 730;
			boxC.h = boxC.messageHeight;
			
			
			messageBoxes.push_back(boxC);
		}
		messageScrollYMin =  -( allHeight - 352 ); //-( allHeight )
		return true;
	}
	return false;
}

int VitaGUI::wordWrap(std::string str, int width, std::string &out) {
   
    int curWidth = width;
    int lineCount = 1;
    while (curWidth < str.length()) {
        std::string::size_type spacePos = str.rfind(' ', curWidth);
        if (spacePos == std::string::npos)
            spacePos = str.find(' ', curWidth);
        if (spacePos != std::string::npos) {
            str[spacePos] = '\n';
            lineCount++;
            curWidth = spacePos + width + 1;
            }
        }
    out = str.substr(0, str.size());
    return lineCount;


//(std::string stringToWrap ,  int availableWidth , std::string &out ){
	
	//int wordWidth = 0;
	//int lineBreaks = 0;
	//
	//out="";
	//std::istringstream iss{stringToWrap};
	//// Read tokens from stream into vector (split at whitespace).
	//std::vector<std::string> words{std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{}};
	//
	//int spaceLeft = availableWidth;
	//for(int i = 0 ; i < words.size() ; i++){
	//	wordWidth = vita2d_font_text_width(vita2dFontNormal, MESSAGE_CONTENT_TEXT_SIZE_PIXEL, words[i].c_str());
	//	if(wordWidth + 1  > spaceLeft){
	//		words[i] = '\n' + words[i];
	//		lineBreaks++;
	//		spaceLeft = availableWidth - wordWidth;
	//	}else{
	//		spaceLeft = spaceLeft - ( wordWidth + 1 );
	//	}
	//	out += words[i];
	//}
	//
	//
	//return lineBreaks;
	
}


void VitaGUI::setDirectMessageBoxes(){
	directMessageBoxes.clear();
	for(int i = 0; i < discordPtr->directMessages.size() ; i++){
		box boxDM;
		boxDM.x = directMessageScrollX ;
		boxDM.y = 100 + directMessageScrollY + i * GUILD_HEIGHT;
		boxDM.w = 230;
		boxDM.h = GUILD_HEIGHT;
		directMessageBoxes.push_back(boxDM);
	}
	directMessageScrollYMin = -((discordPtr->directMessages.size()-1)*GUILD_HEIGHT -300) ;
	
}

void VitaGUI::setDirectMessageMessagesBoxes(){
	
	//discordPtr->directMessages[discordPtr->currentDirectMessage].messages[i].content
	
	
	
	int topMargin = 45;
	int bottomMargin = 18;
	int textHeight = 0;
	int allHeight = 0;
	// TODO CHECK FOR REFRESHED AND REFRESHING DMSGS + PTHREAD THE refreshDm() in Discord.cpp
	//if(!discordPtr->refreshingMessages && discordPtr->refreshedMessages){
		//discordPtr->refreshedMessages = false;
		directMessageMessagesBoxes.clear();
		for(int i = 0; i < discordPtr->directMessages[discordPtr->currentDirectMessage].messages.size() ; i++){
			messagebox boxC;
			boxC.x = directMessageMessagesScrollX + 230;
			boxC.y = directMessageMessagesScrollY + i * 64;
			boxC.username = discordPtr->directMessages[discordPtr->currentDirectMessage].messages[i].author.username;
			boxC.content = "";
			boxC.lineCount = wordWrap( discordPtr->directMessages[discordPtr->currentDirectMessage].messages[i].content , 655 , boxC.content);
			textHeight = boxC.lineCount * vita2d_font_text_height(vita2dFont[15], 15, boxC.content.c_str());
			boxC.messageHeight = max(64, textHeight + topMargin + bottomMargin);
			allHeight += boxC.messageHeight;
			
			
			
			boxC.w = 730;
			boxC.h = boxC.messageHeight;
			
			
			directMessageMessagesBoxes.push_back(boxC);
		}
		directMessageMessagesScrollYMin =  -( allHeight - 352 ); //-( allHeight )

	//}
	

	
}


void VitaGUI::setUserInfo(){
	
	panelUsername = discordPtr->username;
	panelUserDiscriminator = "#" + discordPtr->discriminator;
}


void VitaGUI::showLoginCue(){
	debugNetPrintf(DEBUG, "Show login cue\n");
	vita2d_start_drawing();
	vita2d_clear_screen();
	
	DrawLoginScreen();
	
	vita2d_draw_rectangle(455 , 335, 330 , 58 , RGBA8(0xFF , 0xFF , 0xFF , 0x24));
	
	vita2d_end_drawing();
	vita2d_swap_buffers();
	debugNetPrintf(DEBUG, "Finish show login cue\n");
}

void VitaGUI::unshowLoginCue(){
	debugNetPrintf(DEBUG, "unshwo login cue\n");
	vita2d_start_drawing();
	vita2d_clear_screen();
	
	DrawLoginScreen();
	
	vita2d_end_drawing();
	vita2d_swap_buffers();
	
	debugNetPrintf(DEBUG, "finish unshow login cue\n");
}

void VitaGUI::DrawLoginScreen(){
	
	
		vita2d_draw_rectangle(0, 0, 960, 544, RGBA8(114, 137, 217, 255));
		vita2d_draw_texture( loginFormImage , 161, 53 );
		//vita2d_pgf_draw_text(pgf, 420, 154, RGBA8(255,255,255,255), 2.0f, loginTexts[0].c_str());
		//vita2d_pgf_draw_text(pgf, 420, 250, RGBA8(255,255,255,255), 2.0f, loginTexts[1].c_str());
		vita2d_font_draw_text(vita2dFont[18] , 438, 181, RGBA8(255,255,255,255), 18, loginTexts[0].c_str());
		vita2d_font_draw_text(vita2dFont[18] , 438, 261, RGBA8(255,255,255,255), 18, loginTexts[1].c_str());
		vita2d_font_draw_text(vita2dFont[18] , 815, 261, RGBA8(255,0,0,255), 18, loginTexts[2].c_str());
	
}

void VitaGUI::DrawGuildsOnSidebar(){
	int height = 0;
	debugNetPrintf(DEBUG, "Start of DrawGuilds \n" );
	for(int i = 0 ; i < guildBoxes.size() ; i++){
		height = guildScrollY + i * GUILD_HEIGHT;
		debugNetPrintf(DEBUG, "Checking guild text height : %d \n" , height);
		if(height < MAX_DRAW_HEIGHT && height  > MIN_DRAW_HEIGHT){
			//vita2d_draw_texture( guildsBGImage , guildScrollX + 230 , guildScrollY + i * 128);
			//vita2d_draw_rectangle(guildScrollX + 4, 100 + guildScrollY + i * GUILD_HEIGHT, 222 , GUILD_HEIGHT, RGBA8(48, 50, 55, 255));
			//vita2d_pgf_draw_text(pgf, guildScrollX + 256, guildScrollY + i * 128 + 96, RGBA8(255,255,255,255), 3.0f, discordPtr->guilds[i].name.c_str());
			debugNetPrintf(DEBUG, "Draw Guild Sidebar text\n");
			vita2d_font_draw_text(vita2dFont[18] , guildScrollX + 8, 100 + guildScrollY + i * GUILD_HEIGHT + 40, RGBA8(255,255,255,255), GUILD_TITLE_TEXT_SIZE_PIXEL, discordPtr->guilds[i].name.c_str());
			debugNetPrintf(DEBUG, "Drew Guild Sidebar text \n" );
		}
	}
	debugNetPrintf(DEBUG, "End of DrawGuilds \n" );
	
}

void VitaGUI::DrawChannelsOnSidebar(){
	for(int i = 0 ; i < channelBoxes.size() ; i++){
		if(channelScrollY + i * CHANNEL_HEIGHT < MAX_DRAW_HEIGHT && channelScrollY + i * CHANNEL_HEIGHT > MIN_DRAW_HEIGHT){
			logSD("adding channelbox");
			if(discordPtr->currentChannel == i && discordPtr->inChannel){
				vita2d_draw_rectangle(channelScrollX + 4, 100 + channelScrollY + i * CHANNEL_HEIGHT, 222 , CHANNEL_HEIGHT, RGBA8(40, 43, 48, 255));
			}
			//vita2d_pgf_draw_text(pgf, channelScrollX + 256, channelScrollY + i * 128 + 64, RGBA8(255,255,255,255), 3.0f, discordPtr->guilds[discordPtr->currentGuild].channels[i].name.c_str());
			logSD("Channelname:");
			logSD(discordPtr->guilds[discordPtr->currentGuild].channels[i].name);
			std::string channelName = discordPtr->guilds[discordPtr->currentGuild].channels[i].name;
			vita2d_font_draw_text(vita2dFont[18] , channelScrollX + 8, 100 + channelScrollY + i * CHANNEL_HEIGHT + 40, RGBA8(255,255,255,255), CHANNEL_TITLE_TEXT_SIZE_PIXEL, channelName.c_str());
			//vita2d_pgf_draw_text(pgf, channelScrollX + 256, channelScrollY + i * 128 + 96, RGBA8(255,255,255,255), 1.0f, discordPtr->guilds[discordPtr->currentGuild].channels[i].topic.c_str());
			//logSD("topic:");
			//logSD(discordPtr->guilds[discordPtr->currentGuild].channels[i].topic);
			//std::string channelTopic = discordPtr->guilds[discordPtr->currentGuild].channels[i].topic;
			//vita2d_font_draw_text(vita2dFont[14] , channelScrollX + 180, channelScrollY + i * 128 + 96, RGBA8(255,255,255,255), CHANNEL_TOPIC_TEXT_SIZE_PIXEL, channelTopic.c_str());
		}
	}
	
}

void VitaGUI::DrawMessages(){
	
	int yPos = 0,height;
	int messageBoxesAmount = messageBoxes.size();
	int currentHeights = 0;
	//for(int i =  messageBoxes.size() ; i >= 0  ; i--){
	yPos = messageScrollY + 40;
	for(int i =  0 ; i < messageBoxesAmount ; i++){
		
			debugNetPrintf(DEBUG, "MESSAGE STEP 1\n");
			height = messageBoxes[i].messageHeight;
		
		debugNetPrintf(DEBUG, "calculating %d of %d\n", i, messageBoxesAmount);
		if(yPos < MAX_DRAW_HEIGHT && yPos > MIN_DRAW_HEIGHT){
			debugNetPrintf(DEBUG, "MESSAGE STEP 2\n");
			vita2d_draw_rectangle(240, yPos + height, 710, 2, RGBA8(62, 65, 70, 255)); // two small lines to outline the message panel
			debugNetPrintf(DEBUG, "MESSAGE STEP 3\n");
			vita2d_draw_rectangle(240, yPos + height, 710, 1, RGBA8(51, 53, 55, 255)); // no need for a panel image
			debugNetPrintf(DEBUG, "MESSAGE STEP 4\n");
				vita2d_font_draw_text(vita2dFont[15], 283, yPos + 26, RGBA8(255, 255, 255, 255), 15, messageBoxes[i].username.c_str());
			debugNetPrintf(DEBUG, "MESSAGE STEP 5\n");
				vita2d_font_draw_text(vita2dFont[15], 293, yPos + 50, RGBA8(255, 255, 255, 255), 15, messageBoxes[i].content.c_str());
			debugNetPrintf(DEBUG, "MESSAGE STEP 6\n");
			//vita2d_draw_texture( guildsBGImage , messageScrollX + 128 , messageScrollY + i * 128);
			//vita2d_pgf_draw_text(pgf, messageScrollX + 256, messageScrollY + i * 128 + 96, RGBA8(255,255,255,255), 1.0f, discordPtr->guilds[discordPtr->currentGuild].channels[discordPtr->currentChannel].messages[i].content.c_str());
			//vita2d_font_draw_text(vita2dFont , messageScrollX + 150, messageScrollY + i * 128 + 32, RGBA8(255,255,255,255), MESSAGE_AUTHOR_TEXT_SIZE_PIXEL, discordPtr->guilds[discordPtr->currentGuild].channels[discordPtr->currentChannel].messages[i].author.username.c_str());
			//vita2d_font_draw_text(vita2dFont , messageScrollX + 160, messageScrollY + i * 128 + 96, RGBA8(255,255,255,255), MESSAGE_CONTENT_TEXT_SIZE_PIXEL, discordPtr->guilds[discordPtr->currentGuild].channels[discordPtr->currentChannel].messages[i].content.c_str());
			//vita2d_font_draw_text(vita2dFont[15] , messageScrollX + 150, messageScrollY + i * 128 + 32, RGBA8(255,255,255,255), MESSAGE_AUTHOR_TEXT_SIZE_PIXEL, messageBoxes[i].username.c_str());
			//vita2d_font_draw_text(vita2dFont[30] , messageScrollX + 160, messageScrollY + i * 128 + 96, RGBA8(255,255,255,255), MESSAGE_CONTENT_TEXT_SIZE_PIXEL, messageBoxes[i].content.c_str());
		}
		
		//for(int emo = 0; emo < discordPtr->guilds[discordPtr->currentGuild].channels[discordPtr->currentChannel].messages[i].emojis.size() ; emo++){
		//	int in = discordPtr->guilds[discordPtr->currentGuild].channels[discordPtr->currentChannel].messages[i].emojis[emo].index ;
		//	if(emojis[in].icon != NULL){
		//		if(emojis[in].id == discordPtr->guilds[discordPtr->currentGuild].channels[discordPtr->currentChannel].messages[i].emojis[emo].codepoint){
		//			
		//			vita2d_draw_texture(emojis[in].icon , messageScrollX + 160 + MESSAGE_CONTENT_TEXT_SIZE_PIXEL * discordPtr->guilds[discordPtr->currentGuild].channels[discordPtr->currentChannel].messages[i].emojis[emo].x , messageScrollY + i * 128 + 96);
		//			
		//		}
		//	}
		//}
		
		yPos += height; // add message height to yPos
		debugNetPrintf(DEBUG, "Cycle complete.\n");
	}
		
}


void VitaGUI::DrawDirectMessageUsersOnSidebar(){
	
	
	debugNetPrintf(DEBUG, "DrawDirectMessageUsers\n");
	
	for(int i = 0 ; i < directMessageBoxes.size() ; i++){
		if(directMessageScrollY + i * CHANNEL_HEIGHT < MAX_DRAW_HEIGHT && directMessageScrollY + i * CHANNEL_HEIGHT > MIN_DRAW_HEIGHT){
			
			if(discordPtr->currentDirectMessage == i && discordPtr->inDirectMessageChannel){
				vita2d_draw_rectangle(directMessageScrollX + 4, 100 + directMessageScrollY + i * CHANNEL_HEIGHT, 222 , CHANNEL_HEIGHT, RGBA8(40, 43, 48, 255));
			}
			
			//vita2d_draw_texture( guildsBGImage , directMessageScrollX + 128 , directMessageScrollY + i * 128);
			//vita2d_pgf_draw_text(pgf, directMessageScrollX + 256, directMessageScrollY + i * 128 + 96, RGBA8(255,255,255,255), 1.0f, discordPtr->guilds[discordPtr->currentGuild].channels[discordPtr->currentChannel].messages[i].content.c_str());

			std::string userName = discordPtr->directMessages[i].recipients[0].username;
			vita2d_font_draw_text(vita2dFont[18] , directMessageScrollX + 8, 100 + directMessageScrollY + i * CHANNEL_HEIGHT + 40, RGBA8(255,255,255,255), CHANNEL_TITLE_TEXT_SIZE_PIXEL, userName.c_str());
			
		}
	}

	
}

void VitaGUI::DrawDirectMessageMessages(){

	
	int yPos = 0,height;
	int messageBoxesAmount = directMessageMessagesBoxes.size();
	int currentHeights = 0;
	//for(int i =  messageBoxes.size() ; i >= 0  ; i--){
	yPos = directMessageMessagesScrollY + 40;
	for(int i =  0 ; i < messageBoxesAmount ; i++){
		
			debugNetPrintf(DEBUG, "MESSAGE STEP 1\n");
			height = directMessageMessagesBoxes[i].messageHeight;
		
		debugNetPrintf(DEBUG, "calculating %d of %d\n", i, messageBoxesAmount);
		if(yPos < MAX_DRAW_HEIGHT && yPos > MIN_DRAW_HEIGHT){
			debugNetPrintf(DEBUG, "MESSAGE STEP 2\n");
			vita2d_draw_rectangle(240, yPos + height, 710, 2, RGBA8(62, 65, 70, 255)); // two small lines to outline the message panel
			debugNetPrintf(DEBUG, "MESSAGE STEP 3\n");
			vita2d_draw_rectangle(240, yPos + height, 710, 1, RGBA8(51, 53, 55, 255)); // no need for a panel image
			debugNetPrintf(DEBUG, "MESSAGE STEP 4\n");
				vita2d_font_draw_text(vita2dFont[15], 283, yPos + 26, RGBA8(255, 255, 255, 255), 15, directMessageMessagesBoxes[i].username.c_str());
			debugNetPrintf(DEBUG, "MESSAGE STEP 5\n");
				vita2d_font_draw_text(vita2dFont[15], 293, yPos + 50, RGBA8(255, 255, 255, 255), 15, directMessageMessagesBoxes[i].content.c_str());
			debugNetPrintf(DEBUG, "MESSAGE STEP 6\n");
		}

		
		yPos += height; // add message height to yPos
		debugNetPrintf(DEBUG, "Cycle complete.\n");
	}
	
}




