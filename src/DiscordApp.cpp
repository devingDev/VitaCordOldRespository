#include "DiscordApp.hpp"
#include "log.hpp"

void DiscordApp::Start(){
	
	logSD("____App started!_____");
	
	for(;;){
		vitaGUI.Draw();
		vitaPad.Read();
		vitaTouch.readTouch();
		clicked = vitaGUI.click(vitaTouch.lastTouchPoint.x , vitaTouch.lastTouchPoint.y);
		vitaState = vitaGUI.GetState();
		if(vitaState == 0){
			switch(clicked){
				case 0:
					discord.setEmail(vitaIME.getUserText("Discord Email"));
					vitaGUI.loginTexts[clicked] = discord.getEmail();
					sceKernelDelayThread(SLEEP_CLICK_NORMAL);
					break;
				case 1:
					discord.setPassword(vitaIME.getUserText("Discord Password"));
					vitaGUI.loginTexts[clicked] = discord.getPassword();
					sceKernelDelayThread(SLEEP_CLICK_NORMAL);
					break;
					
				case 2:
					int loginR = discord.login();
					if(loginR  == 200){
						logSD("Login Success");
						vitaGUI.loadingString = "Wait a second " + discord.getUsername();
						discord.loadData();
						logSD("Loaded data");
						vitaGUI.SetState(1);
					}else if(loginR == 200000){
						if( discord.submit2facode(vitaIME.getUserText("Enter your 2Factor Auth Code!")) == 200){
							logSD("Login (2FA) Success");
							vitaGUI.loadingString = "Wait a second " + discord.getUsername();
							discord.loadData();
							logSD("Loaded data");
							vitaGUI.SetState(1);
							logSD("Set state");
						}
					}
					
					sceKernelDelayThread(SLEEP_CLICK_EXTENDED);
					break;
				
			}
		}else if(vitaState == 1){
			if(discord.loadingData){
				
			}else{
				vitaGUI.SetState(2);
			}
		}else if(vitaState == 2){
			
		}
		
		
	}
	
}