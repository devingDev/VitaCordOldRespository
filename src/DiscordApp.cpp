#include "DiscordApp.hpp"
#include "log.hpp"
#include <psp2/io/fcntl.h>


void DiscordApp::loadUserDataFromFile(){
	logSD("sceioopen");
	int fh = sceIoOpen("ux0:data/vitacord-userdata.txt", SCE_O_RDONLY , 0777);
	logSD("getfilesize");
	int filesize = sceIoLseek(fh, 0, SCE_SEEK_END);
	logSD("filesize is : " + std::to_string(filesize));
	logSD("sceioseekfront");
	sceIoLseek(fh, 0, SCE_SEEK_SET);
	logSD("char* buffer = malloc(filesize)");
	char* buffer = malloc(filesize);
	logSD("sceioread");
	int readbytes = sceIoRead(fh, buffer, filesize); 
	logSD("readbytes is : " + std::to_string(readbytes));
	logSD("sceioclose");
	sceIoClose(fh);
	
	if(filesize < 4 || readbytes < 4){
		logSD("file too small no settings loaded");
		return;
	}
	logSD("declare strings");
	
	std::string parserString = std::string( buffer , readbytes);
	std::string email = ""  , password = "";
	bool getmail= true , getpass = false;
	int i = 0;
	logSD("declare strings");
	for(int i = 0 ; i < parserString.length() ; i++){
		
		if(parserString[i] == '\n'){
			if(getmail){
				logSD("newline . switching to getpass");
				getmail = false;
				getpass = true;
			}else if(getpass){
				logSD("newline . end of parsing");
				getpass = false;
				i = 9999;
				break;
			}
		}else if(parserString[i] == '\r'){
			
		}else if(parserString[i] == '\0'){
			logSD("NIL character");
		}else{
			if(getmail){
				logSD("add to mail : " + parserString[i]);
				email += parserString[i];
			}else if(getpass){
				logSD("add to pass : " + parserString[i]);
				password += parserString[i];
			}
		}
		
	}
	logSD("set mail");
	discord.setEmail(email);
	logSD("set pass");
	discord.setPassword(password);
	
	vitaGUI.loginTexts[0] = discord.getEmail();
	vitaGUI.loginTexts[1] = discord.getPassword();
}

void DiscordApp::saveUserDataToFile(std::string mail , std::string pass){
	std::string userdata = mail + "\n" + pass + "\n";
	int fh = sceIoOpen("ux0:data/vitacord-userdata.txt", SCE_O_WRONLY | SCE_O_CREAT, 0777);
	sceIoWrite(fh, userdata.c_str(), strlen(userdata.c_str()));
}


void DiscordApp::Start(){
	
	logSD("____App started!_____");
	
	loadUserDataFromFile();
	
	for(;;){
		vitaGUI.Draw();
		vitaPad.Read();
		vitaTouch.readTouch();
		clicked = vitaGUI.click(vitaTouch.lastTouchPoint.x , vitaTouch.lastTouchPoint.y);
		vitaState = vitaGUI.GetState();
		if(vitaState == 0){
			switch(clicked){
				case 0:
					discord.setEmail(vitaIME.getUserText("Discord Email" , discord.getEmail().c_str() ));
					vitaGUI.loginTexts[clicked] = discord.getEmail();
					sceKernelDelayThread(SLEEP_CLICK_NORMAL);
					break;
				case 1:
					discord.setPassword(vitaIME.getUserText("Discord Password" , discord.getPassword().c_str()));
					vitaGUI.loginTexts[clicked] = discord.getPassword();
					sceKernelDelayThread(SLEEP_CLICK_NORMAL);
					break;
					
				case 2:
					int loginR = discord.login();
					if(loginR  == 200){
						logSD("Login Success");
						vitaGUI.loadingString = "Wait a second " + discord.getUsername();
						saveUserDataToFile(discord.getEmail() , discord.getPassword());
						discord.loadData();
						logSD("Loaded data");
						vitaGUI.SetState(1);
					}else if(loginR == 200000){
						if( discord.submit2facode(vitaIME.getUserText("Enter your 2Factor Auth Code!")) == 200){
							logSD("Login (2FA) Success");
							vitaGUI.loadingString = "Wait a second " + discord.getUsername();
							saveUserDataToFile(discord.getEmail() , discord.getPassword());
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
			
			logSD("vitaState == 1");
			if(discord.loadingData){

				logSD("discord.loadingData == true");
			}else{
				logSD("discord.loadingData == false");
				vitaGUI.SetState(2);
				logSD("vitaGui state = 2");
			}
			logSD("vitastate 1 end");
		}else if(vitaState == 2){
			
		}
		
		
	}
	
}