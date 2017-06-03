#include "Discord.hpp"
#include "log.hpp"
#include <pthread.h>
#include "json.hpp"

Discord::Discord(){
	loadedGuilds = false;
	loadingData = false;
}

Discord::~Discord(){
		//?
}


void * Discord::thread_loadData(void *arg){
	
	logSD("start of thread_loadData()");
	loadingData = true;
	while(loadingData){
		if(!loadedGuilds){
			std::string guildsUrl = "https://discordapp.com/api/users/@me/guilds";
			VitaNet::http_response guildsresponse = vitaNet.curlDiscordGet(guildsUrl , token);
			logSD("guildsresponse : " + guildsresponse.body);
			if(guildsresponse.httpcode == 200){
				try{
					nlohmann::json j_complete = nlohmann::json::parse(guildsresponse.body);
					if(!j_complete.is_null()){
						guilds.clear();
						guildsAmount = j_complete.size();
						for(int i = 0; i < guildsAmount; i++){
							
							guilds.push_back(guild());
							
							if(!j_complete[i].is_null()){
								
								
								if(!j_complete[i]["owner"].is_null()){
									guilds[i].owner = j_complete[i]["owner"].get<bool>();
								}else{
									guilds[i].owner = false;
								}
								
								if(!j_complete[i]["permissions"].is_null()){
									guilds[i].permissions = j_complete[i]["permissions"].get<long>();
								}else{
									guilds[i].permissions = 0;
								}
								
								if(!j_complete[i]["icon"].is_null()){
									guilds[i].icon = j_complete[i]["icon"].get<std::string>();
								}else{
									guilds[i].icon = "";
								}
								
								if(!j_complete[i]["id"].is_null()){
									guilds[i].id = j_complete[i]["id"].get<std::string>();
								}else{
									guilds[i].id = "";
								}
								
								if(!j_complete[i]["name"].is_null()){
									guilds[i].name = j_complete[i]["name"].get<std::string>();
									
								}else{
									guilds[i].name = "";
								}
								
								
								
							}
							
							
						}
						loadedGuilds = true;
					}
				}catch(const std::exception& e){
					
				}
				
			}else{
				loadingData = false;
			}
		}else{
			for(int i = 0; i < guildsAmount ; i++){
				std::string channelUrl = "https://discordapp.com/api/guilds/" + guilds[i].id + "/channels";
				VitaNet::http_response channelresponse = vitaNet.curlDiscordGet(channelUrl , token);
				logSD("channelresponse : " + channelresponse.body);
				if(channelresponse.httpcode == 200){
					try{
						nlohmann::json j_complete = nlohmann::json::parse(channelresponse.body);
						if(!j_complete.is_null()){
							guilds[i].channels.clear();
							int channelsAmount = j_complete.size();
							for(int c = 0; c < channelsAmount; c++){
								
								guilds[i].channels.push_back(channel());
								
								if(!j_complete[c].is_null()){
									
									if(!j_complete[c]["type"].is_null()){
										guilds[i].channels[c].type = j_complete[c]["type"].get<std::string>();
									}else{
										guilds[i].channels[c].type = "";
									}
									
									if(!j_complete[c]["id"].is_null()){
										guilds[i].channels[c].id = j_complete[c]["id"].get<std::string>();
									}else{
										guilds[i].channels[c].id = "";
									}
									
									if(!j_complete[c]["name"].is_null()){
										guilds[i].channels[c].name = j_complete[c]["name"].get<std::string>();
									}else{
										guilds[i].channels[c].name = "name unavailable";
									}
									
									if(!j_complete[c]["topic"].is_null()){
										guilds[i].channels[c].topic = j_complete[c]["topic"].get<std::string>();
									}else{
										guilds[i].channels[c].topic = "";
									}
								
									if(!j_complete[c]["is_private"].is_null()){
										guilds[i].channels[c].is_private = j_complete[c]["is_private"].get<bool>();
									}else{
										guilds[i].channels[c].is_private = false;
									}
									
									if(!j_complete[c]["last_message_id"].is_null()){
										guilds[i].channels[c].last_message_id = j_complete[c]["last_message_id"].get<std::string>();
									}else{
										guilds[i].channels[c].last_message_id = false;
									}
									
									
									
								}
								
							}
						
						}
					}catch(const std::exception& e){
				
					}
				}
				
			}
			
			loadingData = false;
		}
	}
	logSD("end of thread_loadData()");
}

void Discord::loadData(){
	logSD("inside loadData()");
	loadingData = true;
	logSD("pthread_t loadDataThread");
	pthread_t loadDataThread;
	logSD("pthread_create( loadDataThread , NULL , wrapper , 0)");
	pthread_create(&loadDataThread, NULL, &Discord::loadData_wrapper, 0);
	logSD("end of loadData()");
	
}

void Discord::fetchUserData(){
	
	logSD("Fetching userdata");
	std::string userDataUrl = "https://discordapp.com/api/users/@me";
	VitaNet::http_response userdataresponse = vitaNet.curlDiscordGet(userDataUrl , token);
	logSD("userdata response : " + userdataresponse.body);
	if(userdataresponse.httpcode == 200){
		// check if Two-Factor-Authentication is activated and needs further user action
		nlohmann::json j_complete = nlohmann::json::parse(userdataresponse.body);
		if(!j_complete.is_null()){
			if(!j_complete["username"].is_null()){
				username = j_complete["username"].get<std::string>();
			}
			if(!j_complete["verified"].is_null()){
				verified = j_complete["verified"].get<bool>();
			}
			if(!j_complete["mfa_enabled"].is_null()){
				mfa_enabled = j_complete["mfa_enabled"].get<bool>();
			}
			if(!j_complete["id"].is_null()){
				id = j_complete["id"].get<std::string>();
			}
			if(!j_complete["phone"].is_null()){
				phone = j_complete["phone"].get<std::string>();
			}
			if(!j_complete["avatar"].is_null()){
				avatar = j_complete["avatar"].get<std::string>();
			}
			if(!j_complete["discriminator"].is_null()){
				discriminator = j_complete["discriminator"].get<std::string>();
			}
		}
		
		
	}
	
}

void Discord::getGuilds(){
	std::string guildUrl = "https://discordapp.com/api/users/@me/guilds";
}
void Discord::getChannels(){
	
}
std::string Discord::getUsername(){
	return username;
}
std::string Discord::getEmail(){
	return email;
}
std::string Discord::getPassword(){
	return password;
}
void Discord::setEmail(std::string mail){
	email = mail;
}
void Discord::setPassword(std::string pass){
	password = pass;
}
long Discord::login(){
	return login(email , password);
}
long Discord::login(std::string mail , std::string pass){
	logSD("Login attempt");
	email = mail;
	password = pass;
	//std::string loginUrl = "http://jaynapps.com/psvita/httpdump.php";  // DBG
	std::string loginUrl = "https://discordapp.com/api/auth/login";
	std::string postData = "{ \"email\":\"" + email + "\" , \"password\":\"" + password + "\" }";
	logSD(loginUrl + " postData : " + postData);
	VitaNet::http_response loginresponse = vitaNet.curlDiscordPost(loginUrl , postData , token);
	logSD("Login response:");
	logSD(loginresponse.body);
	if(loginresponse.httpcode == 200){
		// check if Two-Factor-Authentication is activated and needs further user action
		nlohmann::json j_complete = nlohmann::json::parse(loginresponse.body);
		try{
			if(!j_complete.is_null()){
				if(!j_complete["mfa"].is_null()){
					if(!j_complete["ticket"].is_null()){
						// Two factor auth is enabled ! grab ticket
						twoFactorAuthEnabled = true;
						ticket = j_complete["ticket"].get<std::string>();
						logSD("Need 2FA Code");
						loginresponse.httpcode = 200000; // NEED MFA
					}
				}else if(!j_complete["token"].is_null()){
					// Logged in !
					token = j_complete["token"].get<std::string>();
					loggedin = true;
					fetchUserData();
				}
				
			}
		}catch(const std::exception& e){
			
		}
		
		
	}else{
		// login failed >_>
		
	}
	return loginresponse.httpcode;
	
}
long Discord::submit2facode(std::string code){
	logSD("Submit 2FA Attempt");
	code2fa = code;

	std::string postData = "{ \"code\":\"" + code2fa + "\" , \"ticket\":\"" + ticket + "\" }";
	VitaNet::http_response submit2facoderesponse = vitaNet.curlDiscordPost( "https://discordapp.com/api/v6/auth/mfa/totp" , postData , token);
	logSD("Submit 2FA Response:");
	logSD(submit2facoderesponse.body);
	if(submit2facoderesponse.httpcode == 200){
		
		nlohmann::json j_complete2 = nlohmann::json::parse(submit2facoderesponse.body);
		if(!j_complete2.is_null()){
			if(!j_complete2["token"].is_null()){
				token = j_complete2["token"].get<std::string>();
				loggedin = true;
				fetchUserData();
			}
		}
		
	}
	logSD("Return 2FA httpcode:");
	return submit2facoderesponse.httpcode;
	
}
std::string Discord::getToken(){
	return token;
}
std::string Discord::getTicket(){
	return ticket;
}