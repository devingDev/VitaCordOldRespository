#include "Discord.hpp"
#include "log.hpp"
#include <pthread.h>
#include "json.hpp"

#include <psp2/kernel/processmgr.h>

uint64_t Discord::osGetTimeMS(){
	return (sceKernelGetProcessTimeWide() / 1000);
}

Discord::Discord(){
	loadedGuilds = false;
	loadingData = false;
}

Discord::~Discord(){
		//?
}
bool Discord::sendDirectMessage(std::string msg){
	std::string postData = "{ \"content\":\"" + msg + "\" }";
	std::string sendDMMessageUrl = "https://discordapp.com/api/v6/channels/" 
							+ directMessages[currentDirectMessage].id + "/messages" ;
	VitaNet::http_response senddmmessageresponse = vitaNet.curlDiscordPost(sendDMMessageUrl , postData , token);
	if(senddmmessageresponse.httpcode == 200){
		
		
	}
	
}

bool Discord::sendMessage(std::string msg){
	
	std::string postData = "{ \"content\":\"" + msg + "\" }";
	std::string sendMessageUrl = "https://discordapp.com/api/channels/" + guilds[currentGuild].channels[currentChannel].id + "/messages" ;
	VitaNet::http_response sendmessageresponse = vitaNet.curlDiscordPost(sendMessageUrl , postData , token);
	if(sendmessageresponse.httpcode == 200){
		
		
	}
	return true;
}

bool Discord::refreshMessages(){
	
	currentTimeMS = osGetTimeMS();
	if(currentTimeMS - lastFetchTimeMS > fetchTimeMS){
		getChannelMessages(currentChannel);
		lastFetchTimeMS = osGetTimeMS();
		
	}
	return true;
	
}

void Discord::getChannelMessages(int channelIndex){
	currentChannel = channelIndex;
	std::string channelMessagesUrl = "https://discordapp.com/api/channels/" + guilds[currentGuild].channels[currentChannel].id + "/messages";
	VitaNet::http_response channelmessagesresponse = vitaNet.curlDiscordGet(channelMessagesUrl , token);
	if(channelmessagesresponse.httpcode == 200){
		nlohmann::json j_complete = nlohmann::json::parse(channelmessagesresponse.body);
		int messagesAmount = j_complete.size();
		
		
		if(!j_complete.is_null()){
			guilds[currentGuild].channels[currentChannel].messages.clear();
			
			for( int i = 0 ; i < messagesAmount ; i++){
				guilds[currentGuild].channels[currentChannel].messages.push_back(message());
				
				if(!j_complete[i].is_null()){
					
					if(!j_complete[i]["timestamp"].is_null()){
						guilds[currentGuild].channels[currentChannel].messages[i].timestamp = j_complete[i]["timestamp"].get<std::string>();
					}else{
						guilds[currentGuild].channels[currentChannel].messages[i].timestamp = "";
					}
					
					if(!j_complete[i]["id"].is_null()){
						guilds[currentGuild].channels[currentChannel].messages[i].id = j_complete[i]["id"].get<std::string>();
					}else{
						guilds[currentGuild].channels[currentChannel].messages[i].id = "";
					}
					
					if(!j_complete[i]["content"].is_null()){
						guilds[currentGuild].channels[currentChannel].messages[i].content = j_complete[i]["content"].get<std::string>();
					}else{
						guilds[currentGuild].channels[currentChannel].messages[i].content = "";
					}
					// author :
					if(!j_complete[i]["author"]["username"].is_null()){
						guilds[currentGuild].channels[currentChannel].messages[i].author.username = j_complete[i]["author"]["username"].get<std::string>();
					}else{
						guilds[currentGuild].channels[currentChannel].messages[i].author.username = "";
					}
					
					if(!j_complete[i]["author"]["discriminator"].is_null()){
						guilds[currentGuild].channels[currentChannel].messages[i].author.discriminator = j_complete[i]["author"]["discriminator"].get<std::string>();
					}else{
						guilds[currentGuild].channels[currentChannel].messages[i].author.discriminator = "";
					}
					
					if(!j_complete[i]["author"]["id"].is_null()){
						guilds[currentGuild].channels[currentChannel].messages[i].author.id = j_complete[i]["author"]["id"].get<std::string>();
					}else{
						guilds[currentGuild].channels[currentChannel].messages[i].author.id = "";
					}
					
					if(!j_complete[i]["author"]["avatar"].is_null()){
						guilds[currentGuild].channels[currentChannel].messages[i].author.avatar = j_complete[i]["author"]["avatar"].get<std::string>();
					}else{
						guilds[currentGuild].channels[currentChannel].messages[i].author.avatar = "";
					}

				}
			}
		}
	
		lastFetchTimeMS = osGetTimeMS();
		
	}
	
}
void Discord::JoinGuild(int gIndex){
	currentGuild = gIndex;
}
void Discord::JoinChannel(int cIndex){
	currentChannel = cIndex;
	getChannelMessages(currentChannel);
}
void Discord::setToken(std::string tok){
	token = tok;
}


void * Discord::thread_loadData(void *arg){
	
	Discord *discordPtr = reinterpret_cast<Discord *>(arg);
	logSD("start of thread_loadData");
	discordPtr->loadingData = true;
	while(discordPtr->loadingData){
		if(!discordPtr->loadedGuilds){
			std::string guildsUrl = "https://discordapp.com/api/users/@me/guilds";
			VitaNet::http_response guildsresponse = discordPtr->vitaNet.curlDiscordGet(guildsUrl , token);
			if(guildsresponse.httpcode == 200){
				try{
					nlohmann::json j_complete = nlohmann::json::parse(guildsresponse.body);
					if(!j_complete.is_null()){
						discordPtr->guilds.clear();
						discordPtr->guildsAmount = j_complete.size();
						for(int i = 0; i < guildsAmount; i++){
							
							discordPtr->guilds.push_back(guild());
							
							if(!j_complete[i].is_null()){
								
								
								if(!j_complete[i]["owner"].is_null()){
									discordPtr->guilds[i].owner = j_complete[i]["owner"].get<bool>();
								}else{
									discordPtr->guilds[i].owner = false;
								}
								
								if(!j_complete[i]["permissions"].is_null()){
									discordPtr->guilds[i].permissions = j_complete[i]["permissions"].get<long>();
								}else{
									discordPtr->guilds[i].permissions = 0;
								}
								
								if(!j_complete[i]["icon"].is_null()){
									discordPtr->guilds[i].icon = j_complete[i]["icon"].get<std::string>();
								}else{
									discordPtr->guilds[i].icon = "";
								}
								
								if(!j_complete[i]["id"].is_null()){
									discordPtr->guilds[i].id = j_complete[i]["id"].get<std::string>();
								}else{
									discordPtr->guilds[i].id = "";
								}
								
								if(!j_complete[i]["name"].is_null()){
									discordPtr->guilds[i].name = j_complete[i]["name"].get<std::string>();
									
								}else{
									discordPtr->guilds[i].name = "";
								}
								
								
								
							}
							
							
						}
						discordPtr->loadedGuilds = true;
					}
				}catch(const std::exception& e){
					discordPtr->loadedGuilds = true;
				}
				
			}else{
				discordPtr->loadedGuilds = true;
			}
		}else if(discordPtr->loadedGuilds && !discordPtr->loadedChannels){
			for(int i = 0; i < discordPtr->guildsAmount ; i++){
				std::string channelUrl = "https://discordapp.com/api/guilds/" + discordPtr->guilds[i].id + "/channels";
				VitaNet::http_response channelresponse = discordPtr->vitaNet.curlDiscordGet(channelUrl , token);
				if(channelresponse.httpcode == 200){
					try{
						nlohmann::json j_complete = nlohmann::json::parse(channelresponse.body);
						if(!j_complete.is_null()){
							discordPtr->guilds[i].channels.clear();
							int channelsAmount = j_complete.size();
							for(int c = 0; c < channelsAmount; c++){
								
								discordPtr->guilds[i].channels.push_back(channel());
								
								if(!j_complete[c].is_null()){
									
									if(!j_complete[c]["type"].is_null()){
										discordPtr->guilds[i].channels[c].type = j_complete[c]["type"].get<std::string>();
									}else{
										discordPtr->guilds[i].channels[c].type = "";
									}
									
									if(!j_complete[c]["id"].is_null()){
										discordPtr->guilds[i].channels[c].id = j_complete[c]["id"].get<std::string>();
									}else{
										discordPtr->guilds[i].channels[c].id = "";
									}
									
									if(!j_complete[c]["name"].is_null()){
										discordPtr->guilds[i].channels[c].name = j_complete[c]["name"].get<std::string>();
									}else{
										discordPtr->guilds[i].channels[c].name = "name unavailable";
									}
									
									if(!j_complete[c]["topic"].is_null()){
										discordPtr->guilds[i].channels[c].topic = j_complete[c]["topic"].get<std::string>();
									}else{
										discordPtr->guilds[i].channels[c].topic = "";
									}
								
									if(!j_complete[c]["is_private"].is_null()){
										discordPtr->guilds[i].channels[c].is_private = j_complete[c]["is_private"].get<bool>();
									}else{
										discordPtr->guilds[i].channels[c].is_private = false;
									}
									
									if(!j_complete[c]["last_message_id"].is_null()){
										discordPtr->guilds[i].channels[c].last_message_id = j_complete[c]["last_message_id"].get<std::string>();
									}else{
										discordPtr->guilds[i].channels[c].last_message_id = false;
									}
									
									
									
								}
								
							}
						
						}
					}catch(const std::exception& e){
				
						discordPtr->loadedChannels = true;
					}
				}
				
			}
			discordPtr->loadedChannels = true;
		}else if(discordPtr->loadedGuilds && discordPtr->loadedChannels && !discordPtr->loadedDMs){
			
			std::string directMessagesChannelsUrl = "https://discordapp.com/api/v6/users/@me/channels";
			VitaNet::http_response dmChannelsResponse = discordPtr->vitaNet.curlDiscordGet(directMessagesChannelsUrl , token);
			logSD("dmMessageChannels Response : " + dmChannelsResponse.body);
			if(dmChannelsResponse.httpcode == 200){
				try{
					nlohmann::json j_complete = nlohmann::json::parse(dmChannelsResponse.body);
					if(!j_complete.is_null()){
						discordPtr->directMessages.clear();
						int dmChannels = j_complete.size();
						logSD("Amount of DM channels : " + std::to_string(dmChannels));
						for(int i = 0; i < dmChannels; i++){
							discordPtr->directMessages.push_back(directMessage());
							logSD("dm channel added.");
							
							if(!j_complete[i]["last_message_id"].is_null()){
								discordPtr->directMessages[i].last_message_id = j_complete[i]["last_message_id"].get<std::string>();
								logSD("last message id : ." + discordPtr->directMessages[i].last_message_id);
							}else{
								discordPtr->directMessages[i].last_message_id = "0000000000000000";
								logSD("last message id : ." + discordPtr->directMessages[i].last_message_id);
							}
							if(!j_complete[i]["type"].is_null()){
								discordPtr->directMessages[i].type = j_complete[i]["type"].get<long>();
								logSD("type : ." + std::to_string(discordPtr->directMessages[i].type));
							}else{
								discordPtr->directMessages[i].type = 1;
								logSD("type : ." + std::to_string(discordPtr->directMessages[i].type));
							}
							if(!j_complete[i]["id"].is_null()){
								discordPtr->directMessages[i].id = j_complete[i]["id"].get<std::string>();
								logSD("last id : ." + discordPtr->directMessages[i].id);
							}else{
								discordPtr->directMessages[i].id = "0000000000000000";
								logSD("last id : ." + discordPtr->directMessages[i].id);
							}
							logSD("checking for recipients");
							if(!j_complete[i]["recipients"].is_null()){
								discordPtr->directMessages[i].recipients.clear();
								int recAmount = j_complete[i]["recipients"].size();
								logSD("Amount of recipients : " + std::to_string(recAmount));
								for(int r = 0; r < recAmount  ; r++){
									// author :
									logSD("Adding recipient ");
									discordPtr->directMessages[i].recipients.push_back(user());
									if(!j_complete[i]["recipients"][r]["username"].is_null()){
										discordPtr->directMessages[i].recipients[r].username = j_complete[i]["recipients"][r]["username"].get<std::string>();
										logSD("username : " + discordPtr->directMessages[i].recipients[r].username);
									}else{
										discordPtr->directMessages[i].recipients[r].username = "";
										logSD("username : " + discordPtr->directMessages[i].recipients[r].username);
									}
									
									if(!j_complete[i]["recipients"][r]["discriminator"].is_null()){
										discordPtr->directMessages[i].recipients[r].discriminator = j_complete[i]["recipients"][r]["discriminator"].get<std::string>();
										logSD("discriminator : " + discordPtr->directMessages[i].recipients[r].discriminator);
									}else{
										discordPtr->directMessages[i].recipients[r].discriminator = "";
										logSD("discriminator : " + discordPtr->directMessages[i].recipients[r].discriminator);
									}
									
									if(!j_complete[i]["recipients"][r]["id"].is_null()){
										discordPtr->directMessages[i].recipients[r].id = j_complete[i]["recipients"][r]["id"].get<std::string>();
										logSD("id : " + discordPtr->directMessages[i].recipients[r].id);
									}else{
										discordPtr->directMessages[i].recipients[r].id = "";
										logSD("id : " + discordPtr->directMessages[i].recipients[r].id);
									}
									
									if(!j_complete[i]["recipients"][r]["avatar"].is_null()){
										discordPtr->directMessages[i].recipients[r].avatar = j_complete[i]["recipients"][r]["avatar"].get<std::string>();
										logSD("avatar : " + discordPtr->directMessages[i].recipients[r].avatar);
									}else{
										discordPtr->directMessages[i].recipients[r].avatar = "";
										logSD("avatar : " + discordPtr->directMessages[i].recipients[r].avatar);
									}
									
									
									logSD("end of adding recipient.");
								}
							}
							
							logSD("end of this DM channel.");
							
							
							
						}
						
					}
					
				}catch(const std::exception& e){
					logSD("/EXCEPTION THROWN!!!");
					logSD(":EXCEPTION THROWN!!!");
					logSD(":EXCEPTION THROWN!!!");
					logSD(":EXCEPTION THROWN!!!");
					logSD("\\EXCEPTION THROWN!!!");
				}
				
			}
			discordPtr->loadedDMs = true;
			discordPtr->loadingData = false;
		}
	}
	logSD("end of thread_loadData()");
	pthread_exit(NULL);
}


void Discord::JoinDirectMessageChannel(int dIndex){
	currentDirectMessage = dIndex;
	getCurrentDirectMessages();
	
	
}

void Discord::getDirectMessageChannels(){
	std::string directMessagesChannelsUrl = "https://discordapp.com/api/v6/users/@me/channels";
	VitaNet::http_response dmChannelsResponse = vitaNet.curlDiscordGet(directMessagesChannelsUrl , token);
	
	if(dmChannelsResponse.httpcode == 200){
		try{
			nlohmann::json j_complete = nlohmann::json::parse(dmChannelsResponse.body);
			if(!j_complete.is_null()){
				directMessages.clear();
				int dmChannels = j_complete.size();
				for(int i = 0; i < dmChannels; i++){
					directMessages.push_back(directMessage());
					
					if(!j_complete[i]["last_message_id"].is_null()){
						directMessages[i].last_message_id = j_complete[i]["last_message_id"].get<std::string>();
					}else{
						directMessages[i].last_message_id = "0000000000000000";
					}
					if(!j_complete[i]["type"].is_null()){
						directMessages[i].type = j_complete[i]["type"].get<long>();
					}else{
						directMessages[i].type = 1;
					}
					if(!j_complete[i]["id"].is_null()){
						directMessages[i].id = j_complete[i]["id"].get<std::string>();
					}else{
						directMessages[i].id = "0000000000000000";
					}
					if(!j_complete[i]["recipients"].is_null()){
						directMessages[i].recipients.clear();
						int recAmount = j_complete[i]["recipients"].size();
						for(int r = 0; r < recAmount  ; r++){
							// author :
							directMessages[i].recipients.push_back(user());
							if(!j_complete[i]["recipients"][r]["username"].is_null()){
								directMessages[i].recipients[r].username = j_complete[i]["recipients"][r]["username"].get<std::string>();
							}else{
								directMessages[i].recipients[r].username = "";
							}
							
							if(!j_complete[i]["recipients"][r]["discriminator"].is_null()){
								directMessages[i].recipients[r].discriminator = j_complete[i]["recipients"][r]["discriminator"].get<std::string>();
							}else{
								directMessages[i].recipients[r].discriminator = "";
							}
							
							if(!j_complete[i]["recipients"][r]["id"].is_null()){
								directMessages[i].recipients[r].id = j_complete[i]["recipients"][r]["id"].get<std::string>();
							}else{
								directMessages[i].recipients[r].id = "";
							}
							
							if(!j_complete[i]["recipients"][r]["avatar"].is_null()){
								directMessages[i].recipients[r].avatar = j_complete[i]["recipients"][r]["avatar"].get<std::string>();
							}else{
								directMessages[i].recipients[r].avatar = "";
							}
							
							
						}
					}
					
					
					
					
				}
				
			}
			
		}catch(const std::exception& e){
			logSD("/EXCEPTION THROWN!!!");
			logSD(":EXCEPTION THROWN!!!");
			logSD(":EXCEPTION THROWN!!!");
			logSD(":EXCEPTION THROWN!!!");
			logSD("\\EXCEPTION THROWN!!!");
		}
		
	}
	lastFetchTimeMS = osGetTimeMS();
	
}


bool Discord::refreshDirectMessages(){
	
	currentTimeMS = osGetTimeMS();
	if(currentTimeMS - lastFetchTimeMS > fetchTimeMS){
		lastFetchTimeMS = osGetTimeMS();
		getDirectMessageChannels();
		
	}
}
bool Discord::refreshCurrentDirectMessages(){
	
	currentTimeMS = osGetTimeMS();
	if(currentTimeMS - lastFetchTimeMS > fetchTimeMS){
		lastFetchTimeMS = osGetTimeMS();
		getCurrentDirectMessages();
		
	}
	
}

void Discord::getCurrentDirectMessages(){
	std::string dmChannelUrl = "https://discordapp.com/api/v6/channels/" + directMessages[currentDirectMessage].id + "/messages";
	VitaNet::http_response dmChannelResponse = vitaNet.curlDiscordGet(dmChannelUrl , token);
	
	
	
	if(dmChannelResponse.httpcode == 200){
		try{
			nlohmann::json j_complete = nlohmann::json::parse(dmChannelResponse.body);
			if(!j_complete.is_null()){
				directMessages[currentDirectMessage].messages.clear();
				int msgAmount = j_complete.size();
				for(int i = 0; i < msgAmount; i++){
					
					directMessages[currentDirectMessage].messages.push_back(message());
					
					if(!j_complete[i]["timestamp"].is_null()){
						directMessages[currentDirectMessage].messages[i].timestamp = j_complete[i]["timestamp"].get<std::string>();
					}else{
						directMessages[currentDirectMessage].messages[i].timestamp = "";
					}
					
					if(!j_complete[i]["id"].is_null()){
						directMessages[currentDirectMessage].messages[i].id = j_complete[i]["id"].get<std::string>();
					}else{
						directMessages[currentDirectMessage].messages[i].id = "";
					}
					
					if(!j_complete[i]["content"].is_null()){
						directMessages[currentDirectMessage].messages[i].content = j_complete[i]["content"].get<std::string>();
					}else{
						directMessages[currentDirectMessage].messages[i].content = "";
					}
					// author :
					if(!j_complete[i]["author"]["username"].is_null()){
						directMessages[currentDirectMessage].messages[i].author.username = j_complete[i]["author"]["username"].get<std::string>();
					}else{
						directMessages[currentDirectMessage].messages[i].author.username = "";
					}
					
					if(!j_complete[i]["author"]["discriminator"].is_null()){
						directMessages[currentDirectMessage].messages[i].author.discriminator = j_complete[i]["author"]["discriminator"].get<std::string>();
					}else{
						directMessages[currentDirectMessage].messages[i].author.discriminator = "";
					}
					
					if(!j_complete[i]["author"]["id"].is_null()){
						directMessages[currentDirectMessage].messages[i].author.id = j_complete[i]["author"]["id"].get<std::string>();
					}else{
						directMessages[currentDirectMessage].messages[i].author.id = "";
					}
					
					if(!j_complete[i]["author"]["avatar"].is_null()){
						directMessages[currentDirectMessage].messages[i].author.avatar = j_complete[i]["author"]["avatar"].get<std::string>();
					}else{
						directMessages[currentDirectMessage].messages[i].author.avatar = "";
					}
				}
			}
		}catch(const std::exception& e){
			
		}
	}
	lastFetchTimeMS = osGetTimeMS();
}

void Discord::loadData(){
	logSD("inside loadData()");
	loadingData = true;
	logSD("pthread_t loadDataThread");
	pthread_t loadDataThread;
	logSD("pthread_create( loadDataThread , NULL , wrapper , 0)");
	pthread_create(&loadDataThread, NULL, &Discord::loadData_wrapper, this);
	logSD("end of loadData()");
	
}

long Discord::fetchUserData(){
	
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
	
	return userdataresponse.httpcode;
	
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
	
	if(token.length() > 20){
		if(fetchUserData() == 200){
			loggedin = true;
			return 200;
		}else{
			token = "";
		}
		
	}
	
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

