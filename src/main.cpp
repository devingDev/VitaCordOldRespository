#define VITASDK

#include <vita2d.h>
#include <psp2/sysmodule.h>
#include <psp2/kernel/processmgr.h>
#include <psp2/display.h>

#include <psp2/net/net.h>
#include <psp2/net/netctl.h>
#include <psp2/net/http.h>

#include <psp2/io/fcntl.h>

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <string>
#include <vector>

#include <curl/curl.h>

#include <debugnet.h>

#include "VitaIME.hpp"
#include "VitaPad.hpp"

#include "debugScreen.h"
#include "json.hpp"

#define ip_server "192.168.1.85"
#define port_server 18194


struct messageauthor{
	std::string username;
	std::string discriminator;
	std::string id;
	std::string avatar;
	
};

struct message{
	std::string timestamp;
	std::string id;
	struct messageauthor author;
	std::string content;
};

struct channel{
	std::string name;
	
	std::string last_pin_timestamp;
	std::string topic;
	std::string last_message_id;
	std::string type;
	std::string id;
	bool is_private;
	
	std::vector<message> messages;
};


struct guild{
	bool owner;
	long permissions;
	std::string icon;
	std::string id;
	std::string name;
	std::vector<channel> channels;
};

std::vector<guild> guilds;

int currentGuild = 0;
int currentChannel = 0;
	int cursorGuild = 0;
	int cursorChannel = 0;

std::string useremail = "" , userpassword = "";

bool loggedIn = false;
bool inChannel = false , inGuild = false , inMain = true , inApp = true;

std::string data; //will hold the url's contents

int guildsAmount = 0;

std::string userToken = "";//"ThisMTI3Ois-AzA5NjgyMTc2.C8rveryUETH3GU08LONGYNSTRINGlOckqoA";
std::string authorizationHeader = "Authorization: Bz832148124";
std::string userMessage = "";

std::string webhookID = "" , webhookToken = "";

std::string postdata = "{ \"name\":\"coderx3\" }";
const char userAgent[] = "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.36";
const char userAgentHeader[] = "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.36";


int scrollX = 0 , scrollY = 0;

uint64_t lastFetchTimeMS , currentTimeMS , fetchDelayMS = 2000;

uint64_t osGetTimeMS(void){
	return (sceKernelGetProcessTimeWide() / 1000);
}

vita2d_pgf *pgf;

VitaPad vitaPad;
VitaIME vitaIME;

void netInit() {
	////psvDebugScreenPrintf("Loading module SCE_SYSMODULE_NET\n");
	sceSysmoduleLoadModule(SCE_SYSMODULE_NET);
	
	////psvDebugScreenPrintf("Running sceNetInit\n");
	SceNetInitParam netInitParam;
	int size = 1*1024*1024;
	netInitParam.memory = malloc(size);
	netInitParam.size = size;
	netInitParam.flags = 0;
	sceNetInit(&netInitParam);

	////psvDebugScreenPrintf("Running sceNetCtlInit\n");
	sceNetCtlInit();
}

void netTerm() {
	////psvDebugScreenPrintf("Running sceNetCtlTerm\n");
	sceNetCtlTerm();

	////psvDebugScreenPrintf("Running sceNetTerm\n");
	sceNetTerm();

	////psvDebugScreenPrintf("Unloading module SCE_SYSMODULE_NET\n");
	sceSysmoduleUnloadModule(SCE_SYSMODULE_NET);
}

void httpInit() {
	////psvDebugScreenPrintf("Loading module SCE_SYSMODULE_HTTP\n");
	sceSysmoduleLoadModule(SCE_SYSMODULE_HTTP);

	////psvDebugScreenPrintf("Running sceHttpInit\n");
	sceHttpInit(1*1024*1024);
}

void httpTerm() {
	////psvDebugScreenPrintf("Running sceHttpTerm\n");
	sceHttpTerm();	

	////psvDebugScreenPrintf("Unloading module SCE_SYSMODULE_HTTP\n");
	sceSysmoduleUnloadModule(SCE_SYSMODULE_HTTP);
}

size_t writeCallback(char* buf, size_t size, size_t nmemb, void* up)
{ //callback must have this declaration
    //buf is a pointer to the data that curl has for us
    //size*nmemb is the size of the buffer

    for (int c = 0; c<size*nmemb; c++)
    {
        data.push_back(buf[c]);
    }
	
	//psvDebugScreenPrintf("\nIncoming START \n");
	//psvDebugScreenPrintf(data.c_str());
	//psvDebugScreenPrintf("\nIncoming END \n");
	debugNetPrintf(DEBUG,"WRITECALLBACK DATA START\n");
	debugNetPrintf(DEBUG,data.c_str());
	debugNetPrintf(DEBUG,"WRITECALLBACK DATA END\n");
    return size*nmemb; //tell curl how many bytes we handled
}


long curlGet(std::string url){
	
	data = "";
	long http_code = 0;
	
	//DBG
	//url = "http://jaynapps.com/psvita/httpdump.php";
	
	CURL *curl;
	CURLcode res;
	curl = curl_easy_init();
	if(curl) {
		
			debugNetPrintf(DEBUG,"Curl Get init success\n");
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		
			debugNetPrintf(DEBUG,url.c_str());
			debugNetPrintf(DEBUG,"\n");
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);
		
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
		curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 10L);
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
		
		curl_easy_setopt(curl, CURLOPT_USERAGENT, userAgent);
		
		struct curl_slist *headerchunk = NULL;
		headerchunk = curl_slist_append(headerchunk, "Accept: */*");
		headerchunk = curl_slist_append(headerchunk, "Content-Type: application/json");
		headerchunk = curl_slist_append(headerchunk, userAgentHeader);
		headerchunk = curl_slist_append(headerchunk, authorizationHeader.c_str());
		headerchunk = curl_slist_append(headerchunk, "Host: discordapp.com");
		
		headerchunk = curl_slist_append(headerchunk, "Content-Length: 0");
		
		res = curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerchunk);
		
		
		
		res = curl_easy_perform(curl);
		curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &http_code);
		if(res != CURLE_OK){
			//psvDebugScreenPrintf("curl_easy_perform CURL FAILED! \n\n");
			//psvDebugScreenPrintf("Error : %s\n\n\n" , curl_easy_strerror(res));
			//fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

			/* always cleanup */ 
			debugNetPrintf(DEBUG,"Curl Get  FAIL\n");
			
		}else{
			
			debugNetPrintf(DEBUG,"Curl Get  success\n");
			//psvDebugScreenPrintf("curl_easy_perform == CURLE_OK => Wroked! \n\n");
			//psvDebugScreenPrintf("Response : %s\n\n\n" , data.c_str());
		}
		
		
	}else{
		
		debugNetPrintf(DEBUG,"Curlget init fail  FAIL\n");
	}
	curl_easy_cleanup(curl);
	
	return http_code;
}

long curlPost(std::string url , std::string postData){
	data = "";
	long http_code = 0;
	
	CURL *curl;
	CURLcode res;
	curl = curl_easy_init();
	if(curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
		curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 10L);
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
		
		struct curl_slist *headerchunk = NULL;
		headerchunk = curl_slist_append(headerchunk, "Accept: */*");
		headerchunk = curl_slist_append(headerchunk, "Content-Type: application/json");
		headerchunk = curl_slist_append(headerchunk, userAgentHeader);
		headerchunk = curl_slist_append(headerchunk, authorizationHeader.c_str());
		headerchunk = curl_slist_append(headerchunk, "Host: discordapp.com");
		
		std::string ContentLengthS = "Content-Length: " + std::to_string(strlen(postdata.c_str()));
		headerchunk = curl_slist_append(headerchunk, ContentLengthS.c_str());
		res = curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerchunk);
		
		curl_easy_setopt(curl, CURLOPT_POST, 1L);
		
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postdata.c_str());
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)strlen(postdata.c_str()));
		
		curl_easy_setopt(curl, CURLOPT_USERAGENT, userAgent);
		
		
		res = curl_easy_perform(curl);
		curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &http_code);
		if(res != CURLE_OK){
			//psvDebugScreenPrintf("curl_easy_perform CURL FAILED! \n\n");
			//psvDebugScreenPrintf("Error : %s\n\n\n" , curl_easy_strerror(res));
			//fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

			debugNetPrintf(DEBUG,"Curl Post  fail\n");
			/* always cleanup */ 
			
		}else{
			
			debugNetPrintf(DEBUG,"Curl Post  success\n");
			//psvDebugScreenPrintf("curl_easy_perform == CURLE_OK => Wroked! \n\n");
			//psvDebugScreenPrintf("Response : %s\n\n\n" , data.c_str());
		}
		
		
	}
	curl_easy_cleanup(curl);
	
	return http_code;
	
}


void curlTest(){
	
	
	
	
	//static const char *postthis="{ \"name\":\"coderx3\" }";
	CURL *curl;
	CURLcode res;
	/* In windows, this will init the winsock stuff */ 
	//curl_global_init(CURL_GLOBAL_ALL);
	
	curl = curl_easy_init();
	if(curl) {
		
		/* First set the URL that is about to receive our POST. This URL can
		   just as well be a https:// URL if that is what should receive the
		   data. */ 
		   
		   
		//psvDebugScreenPrintf("curl_easy_init success \n");
		   
		curl_easy_setopt(curl, CURLOPT_URL, "https://discordapp.com/api/channels/284735881087025152/webhooks");
		
		
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);
		
		
		/* we pass our 'chunk' struct to the callback function */ 
		//curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
		
		
		   
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
		curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 10L);
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
		   
		   
		
		/* Now specify the POST data */ 
		
		
		
		struct curl_slist *headerchunk = NULL;
		headerchunk = curl_slist_append(headerchunk, "Accept: */*");
		headerchunk = curl_slist_append(headerchunk, "Content-Type: application/json");
		headerchunk = curl_slist_append(headerchunk, userAgentHeader);
		headerchunk = curl_slist_append(headerchunk, authorizationHeader.c_str());
		headerchunk = curl_slist_append(headerchunk, "Host: discordapp.com");
		
		std::string ContentLengthS = "Content-Length: " + std::to_string(strlen(postdata.c_str()));
		headerchunk = curl_slist_append(headerchunk, ContentLengthS.c_str());
		res = curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerchunk);
		
		
		
		
		curl_easy_setopt(curl, CURLOPT_POST, 1L);
		
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postdata.c_str());
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)strlen(postdata.c_str()));
		
		curl_easy_setopt(curl, CURLOPT_USERAGENT, userAgent);
		

		/* Perform the request, res will get the return code */ 
		
		//psvDebugScreenPrintf("curl_easy_perform \n");
		res = curl_easy_perform(curl);
		/* Check for errors */ 
		if(res != CURLE_OK){
			//psvDebugScreenPrintf("curl_easy_perform CURL FAILED! \n\n");
			//psvDebugScreenPrintf("Error : %s\n\n\n" , curl_easy_strerror(res));
			//fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

			/* always cleanup */ 
			
		}else{
			
			//psvDebugScreenPrintf("curl_easy_perform == CURLE_OK => Wroked! \n\n");
			//psvDebugScreenPrintf("Response : %s\n\n\n" , data.c_str());
		}
		
		
		
		curl_easy_cleanup(curl);
	}			
	
	
	
	
	
		
	
}

void processJsonWebhook(){
	nlohmann::json j_complete = nlohmann::json::parse(data);
	
	char url[1024];
	
	const char urlS[] = "https://discordapp.com/api/webhooks/%s/%s" ;
	
	
	
	snprintf(url , 1024 , urlS , j_complete["id"].get<std::string>().c_str() , j_complete["token"].get<std::string>().c_str());

	
	std::string postdata = "{ \"username\":\"coderx3\" , \"content\":\"hi\" , \"avatar_url\":\"https://cdn.discordapp.com/avatars/206127888309682176/9ebc942fd23843bc3f7c1ee372fe84b6.png\" }";

		//psvDebugScreenPrintf("Webhook URL : %s \n" , url);
	
	CURL *curl;
	CURLcode res;
	/* In windows, this will init the winsock stuff */ 
	//curl_global_init(CURL_GLOBAL_ALL);
	//psvDebugScreenPrintf("curl_easy_init() \n");
	curl = curl_easy_init();
	if(curl) {
		//psvDebugScreenPrintf("curl easy init worked!\n");
		/* First set the URL that is about to receive our POST. This URL can
		   just as well be a https:// URL if that is what should receive the
		   data. */ 
		   
		   
		//psvDebugScreenPrintf("curl_easy_setopt() URL \n");
		curl_easy_setopt(curl, CURLOPT_URL, url);
		
		
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);
		
		
		/* we pass our 'chunk' struct to the callback function */ 
		//curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
		
		
		   
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
		curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 10L);
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
		   
		   
		
		/* Now specify the POST data */ 
		
		
		//psvDebugScreenPrintf("curl_slist headerchunk \n");
		struct curl_slist *headerchunk = NULL;
		//psvDebugScreenPrintf("curl_slist_append ... \n");
		headerchunk = curl_slist_append(headerchunk, "Accept: */*");
		headerchunk = curl_slist_append(headerchunk, "Content-Type: application/json");
		headerchunk = curl_slist_append(headerchunk, userAgentHeader);
		headerchunk = curl_slist_append(headerchunk, "Authorization: MjA2MTI3ODg4MzA5NjgyMTc2.C8rDVg.UETH3GU08GicgYNjFb8TlOckqoA");
		headerchunk = curl_slist_append(headerchunk, "Host: discordapp.com");
		
		std::string ContentLengthS = "Content-Length: " + std::to_string(strlen(postdata.c_str()));
		headerchunk = curl_slist_append(headerchunk, ContentLengthS.c_str());
		//psvDebugScreenPrintf("curl_easy_setopt() HEDER => headerchunk \n");
		res = curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerchunk);
		
		
		
		//psvDebugScreenPrintf("curl_easy_setopt() POST \n");
		curl_easy_setopt(curl, CURLOPT_POST, 1L);
		//psvDebugScreenPrintf("curl_easy_setopt() POSTFIELDS \n");
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postdata.c_str());
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)strlen(postdata.c_str()));
		
		curl_easy_setopt(curl, CURLOPT_USERAGENT, userAgent);
		

		/* Perform the request, res will get the return code */ 
		//psvDebugScreenPrintf("curl_easy_perform() \n");
		res = curl_easy_perform(curl);
		/* Check for errors */ 
		if(res != CURLE_OK){
			//psvDebugScreenPrintf("curl_easy_perform CURL FAILED! \n\n");
			//psvDebugScreenPrintf("Error : %s\n\n\n" , curl_easy_strerror(res));
			//fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

			/* always cleanup */ 
			
		}else{
			
			//psvDebugScreenPrintf("curl_easy_perform == CURLE_OK => Wroked! \n\n");
			//psvDebugScreenPrintf("Response : %s\n\n\n" , data.c_str());
		}
		
		//psvDebugScreenPrintf("curl_easy_cleanup() ! \n");
		
		curl_easy_cleanup(curl);
	}			
	
}


void loginDiscord(){
	
	postdata = "{ \"email\":\"" + useremail + "\" , \"password\":\"" + userpassword + "\" }";
	
	long httpcode =  curlPost("https://discordapp.com/api/auth/login" , postdata) ;
	
	if(httpcode == 200){
		//logged in!
		loggedIn = true;
		
		debugNetPrintf(DEBUG,"parse json tokenlogin\n");
		try{
			nlohmann::json j_complete = nlohmann::json::parse(data);
			debugNetPrintf(DEBUG,"check login token Json empty?\n");
			if(!j_complete.is_null()){
				if(!j_complete["token"].is_null()){
					
					debugNetPrintf(DEBUG,"Curl Get  success\n");
					userToken = j_complete["token"].get<std::string>();
			
					authorizationHeader = "Authorization: " + userToken;
				}
				
			}
		}catch(const std::exception& e){
			
		}

		
	}else if(httpcode == 400){
		// wrong login info!
		loggedIn = false;
	}
	
}

/*void createWebhookDiscord(){
	
	postdata = "{ \"email\":\"" + useremail + "\" , \"password\":\"" + userpassword + "\" }";
	
	long httpcode =  curlPost("https://discordapp.com/api/auth/login" , postdata) ;
	
	
	
}*/
//guilds/284735881087025152/channels


void getChannels(){
	
	for(int i = 0; i < guildsAmount ; i++){
		
		long httpcode =  curlGet("https://discordapp.com/api/guilds/" + guilds[i].id + "/channels" ) ;
		if(httpcode == 200){
			try{
				nlohmann::json j_complete = nlohmann::json::parse(data);
				if(!j_complete.is_null()){
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
	
}

void getGuilds(){
	
	long httpcode =  curlGet("https://discordapp.com/api/users/@me/guilds" ) ;
	
	if(httpcode == 200){
		try{
			nlohmann::json j_complete = nlohmann::json::parse(data);
			if(!j_complete.is_null()){
				guildsAmount = j_complete.size();
				
				
							debugNetPrintf(DEBUG, std::to_string(guildsAmount).c_str());
				
				for(int i = 0; i < guildsAmount; i++){
					
					guilds.push_back(guild());
					
					if(!j_complete[i].is_null()){
						
							debugNetPrintf(DEBUG,"new guild owner");
						if(!j_complete[i]["owner"].is_null()){
							guilds[i].owner = j_complete[i]["owner"].get<bool>();
						}else{
							guilds[i].owner = false;
						}
						
							debugNetPrintf(DEBUG,"new guild permissions");
						if(!j_complete[i]["permissions"].is_null()){
							guilds[i].permissions = j_complete[i]["permissions"].get<long>();
						}else{
							guilds[i].permissions = 0;
						}
						
							debugNetPrintf(DEBUG,"new guild icon");
						if(!j_complete[i]["icon"].is_null()){
							guilds[i].icon = j_complete[i]["icon"].get<std::string>();
						}else{
							guilds[i].icon = "";
						}
						
							debugNetPrintf(DEBUG,"new guild id");
						if(!j_complete[i]["id"].is_null()){
							guilds[i].id = j_complete[i]["id"].get<std::string>();
						}else{
							guilds[i].id = "";
						}
						
							debugNetPrintf(DEBUG,"new guild name");
						if(!j_complete[i]["name"].is_null()){
							guilds[i].name = j_complete[i]["name"].get<std::string>();
							debugNetPrintf(DEBUG,guilds[i].name.c_str());
						}else{
							guilds[i].name = "";
						}
						
						
						
					}
					
					
				}
			}
		}catch(const std::exception& e){
			
		}
		
	}
	
}


void curlUsersMe(){
	

	
}


void sendMessage(){
	
	postdata = "{ \"content\":\"" + userMessage + "\" }";
	long httpcode = curlPost("https://discordapp.com/api/channels/" + guilds[currentGuild].channels[currentChannel].id + "/messages" , postdata );
	
	if(httpcode == 200){
		
		
	}
	
}

void getMessagesFromChannel(){
	
	
	long httpcode =  curlGet("https://discordapp.com/api/channels/" + guilds[currentGuild].channels[currentChannel].id + "/messages" ) ;
	
	if(httpcode == 200){
		nlohmann::json j_complete = nlohmann::json::parse(data);
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


void printChannelsInGuild(){
	
	//psvDebugScreenPrintf(guilds[currentGuild].name.c_str());
		vita2d_pgf_draw_text(pgf, 16, 16, RGBA8(0,255,0,255), 0.75f, guilds[currentGuild].name.c_str());
	std::string printThis ="";
	for(int i = 0 ; i < guilds[currentGuild].channels.size() ; i++){
		printThis = "";
		if(cursorChannel == i)
			printThis += " > ";
		printThis += guilds[currentGuild].channels[i].name;
		vita2d_pgf_draw_text(pgf, scrollX + 16, scrollY + (32 + 16 * i), RGBA8(0,255,0,255), 0.75f, printThis.c_str());
		//psvDebugScreenPrintf(printThis.c_str());
	}
	
}

void printGuilds(){
	
	//psvDebugScreenPrintf("Guilds \n");
	vita2d_pgf_draw_text(pgf, 16, 16, RGBA8(0,255,0,255), 1.0f, "Guilds : ");
	std::string printThis ="";
	for(int i = 0 ; i < guilds.size() ; i++){
		printThis = "";
		if(cursorGuild == i)
			printThis += " > ";
		printThis += guilds[i].name;
		vita2d_pgf_draw_text(pgf, scrollX + 16, scrollY + (32 + 16 * i), RGBA8(0,255,0,255), 1.0f, printThis.c_str());
		//psvDebugScreenPrintf(printThis.c_str());
	}
}

void printMessages(){
	
	std::string printThis ="";
	vita2d_pgf_draw_text(pgf, 8, 16, RGBA8(0,255,0,255), 1.0f, guilds[currentGuild].channels[currentChannel].name.c_str());
	for(int i =  0 ; i < guilds[currentGuild].channels[currentChannel].messages.size() ; i++){
		
		printThis = "";
		printThis += guilds[currentGuild].channels[currentChannel].messages[i].author.username;
		printThis += " : ";
		printThis += guilds[currentGuild].channels[currentChannel].messages[i].content;
		vita2d_pgf_draw_text(pgf, scrollX + 32, scrollY + (32 + 16 * i), RGBA8(0,255,0,255), 1.0f, printThis.c_str());
		//psvDebugScreenPrintf(printThis.c_str());
	}
	
	
}

void joinFirstTextChannel(){
	
	for(int i = 0 ; i < guildsAmount ;i++){
		
		for(int j = 0 ; j < guilds[i].channels.size() ; j++){
			
			if(guilds[i].channels[j].type == "text"){
				if(guilds[i].channels[j].is_private == false){
				
					currentGuild = i;
					currentChannel = j;
					
					
					i = 999999;
					j = 999999;
					break;
					
				}
			}
			
			
		}
		
	}
	
}

extern "C"
{
    unsigned int sleep(unsigned int seconds)
    {
        sceKernelDelayThread(seconds*1000*1000);
        return 0;
    }

    int usleep(useconds_t usec)
    {
        sceKernelDelayThread(usec);
        return 0;
    }

    void __sinit(struct _reent *);
}

/*__attribute__((constructor(101)))
void pthread_setup(void) 
{
    pthread_init();
    __sinit(_REENT);
}*/

int main(int argc, char *argv[]) {
	
	////psvDebugScreenPrintf("HTTP Sample v.1.0 by barooney\n\n");
	int ret;
	ret=debugNetInit(ip_server,port_server,DEBUG);
	debugNetPrintf(DEBUG,"\n\n\n\n\n\n\nVITACORD - Test debug level %d\n",ret);
	
    vita2d_init();
	vita2d_set_clear_color(RGBA8(0x40, 0x40, 0x40, 0xFF));
	pgf = vita2d_load_default_pgf();
	
	vita2d_start_drawing();
	vita2d_clear_screen();
	vita2d_pgf_draw_text(pgf, 0, 16, RGBA8(0,255,0,255), 0.75f, "VitaCord by Me :P");
	vita2d_end_drawing();
	vita2d_swap_buffers();
	
	//get token from user
	//then set auth
	

	debugNetPrintf(DEBUG,"Net Init\n");
	netInit();
	debugNetPrintf(DEBUG,"Http Init\n");
	httpInit();
	
	
	curl_global_init(CURL_GLOBAL_ALL);
	
	while(!loggedIn){
		useremail = vitaIME.getUserText("Discord Email");
		userpassword = vitaIME.getUserText("Discord Password");
		debugNetPrintf(DEBUG,"Login Discord()\n");
		loginDiscord();
	}
	
	
	debugNetPrintf(DEBUG,data.c_str());
	//psvDebugScreenInit();	
	debugNetPrintf(DEBUG,"\n");
	debugNetPrintf(DEBUG,userToken.c_str());
	debugNetPrintf(DEBUG,"\n");
	debugNetPrintf(DEBUG,authorizationHeader.c_str());
	debugNetPrintf(DEBUG,"\n");
	debugNetPrintf(DEBUG,"GetGuilds()\n");
	getGuilds();
	debugNetPrintf(DEBUG,data.c_str());
	debugNetPrintf(DEBUG,"GetChannels()\n");
	getChannels();
	debugNetPrintf(DEBUG,data.c_str());
	debugNetPrintf(DEBUG,"JoinFirstTextChannel()\n");
	joinFirstTextChannel();
	debugNetPrintf(DEBUG,data.c_str());
	//getMessagesFromChannel();	

	debugNetPrintf(DEBUG,"Main While Loop while(inApp)\n",ret);
	while(inApp){
		//sceKernelDelayThread(1*250*1000); // SLEEP FOR NOW DEBUG REASONS ; ELSE TOO FAST
		sceKernelDelayThread(1*10*1000);

		
		vitaPad.Read();
		
		currentTimeMS = osGetTimeMS();
		if(inChannel){
			vita2d_start_drawing();
			vita2d_clear_screen();
			printMessages();
			vita2d_end_drawing();
			vita2d_swap_buffers();
			

			
			if(vitaPad.circle){
				inGuild = true;
				inChannel = false;
				inMain = false;
				scrollX = scrollY = 0;
				
				sceKernelDelayThread(1*150*1000); // 150 ms
			}else if(vitaPad.cross){
				
				userMessage = vitaIME.getUserText("Message : ");
				sendMessage();
				
				
				scrollX = scrollY = 0;
				
				sceKernelDelayThread(1*150*1000);
				
			}else{
				
				scrollX = 127 - vitaPad.lx;
				scrollY = 127 - vitaPad.ly;
				
			}
			
			if(currentTimeMS - lastFetchTimeMS > fetchDelayMS ){
				getMessagesFromChannel();
				
			}
			
		}else if(inGuild){
			// show channels
			vita2d_start_drawing();
			vita2d_clear_screen();
			printChannelsInGuild();
			vita2d_end_drawing();
			vita2d_swap_buffers();
			
			if(vitaPad.circle){
				inChannel = false;
				inGuild = false;
				inMain = true;
				
				
				scrollX = scrollY = 0;
				
				cursorChannel = 0;
				
				sceKernelDelayThread(1*150*1000); // 150 ms
			}else if(vitaPad.cross){
				inChannel = true;
				inGuild = false;
				inMain = false;
				
				
				scrollX = scrollY = 0;
				
				currentChannel = cursorChannel;
				currentGuild = cursorGuild;
				
				sceKernelDelayThread(1*150*1000); // 150 ms
			}else if(vitaPad.up){
				
				cursorChannel--;
				if(cursorChannel < 0){
					cursorChannel = guilds[currentGuild].channels.size() - 1;
				}
				
				sceKernelDelayThread(1*150*1000); // 150 ms
			}else if(vitaPad.down){
				
				cursorChannel++;
				if(cursorChannel >= guilds[currentGuild].channels.size()){
					cursorChannel = 0;
				}
				
				sceKernelDelayThread(1*150*1000); // 150 ms
			}else{
				
				debugNetPrintf(DEBUG , "VitaPAD CLAX : %d , CLAY : %d \n" , vitaPad.left_analog_x , vitaPad.left_analog_y);
				debugNetPrintf(DEBUG , "VitaPAD LAX : %d , LAY : %d \n" , vitaPad.lx , vitaPad.ly);
				scrollX = 127 - vitaPad.lx;
				scrollY = 127 - vitaPad.ly;
				
			}
		}else if(inMain){
			// show guilds ( servers )
			vita2d_start_drawing();
			vita2d_clear_screen();
			printGuilds();
			vita2d_end_drawing();
			vita2d_swap_buffers();
			if(vitaPad.circle){
				inChannel = false;
				inGuild = false;
				inMain = false;
				inApp = false;
				
				sceKernelDelayThread(1*150*1000); // 150 ms
			}else if(vitaPad.cross){
				inChannel = false;
				inGuild = true;
				inMain = false;
				
				
				scrollX = scrollY = 0;
				
				currentChannel = cursorChannel;
				currentGuild = cursorGuild;
				
				sceKernelDelayThread(1*150*1000); // 150 ms
			}else if(vitaPad.up){
				
				cursorGuild--;
				if(cursorGuild < 0){
					cursorGuild = guildsAmount - 1;
				}
				
				sceKernelDelayThread(1*150*1000); // 150 ms
			}else if(vitaPad.down){
				
				cursorGuild++;
				if(cursorGuild >= guildsAmount){
					cursorGuild = 0;
				}
				
				sceKernelDelayThread(1*150*1000); // 150 ms
			}else{
				
				scrollX = 127 - vitaPad.lx;
				scrollY = 127 - vitaPad.ly;
				
			}
		}
		

		
	}
	
	
	debugNetPrintf(DEBUG,"curl global cleanup\n");
	curl_global_cleanup();

	
	debugNetPrintf(DEBUG,"Http Term\n");
	httpTerm();
	debugNetPrintf(DEBUG,"Net Term\n");
	netTerm();

	debugNetPrintf(DEBUG,"Debugnetfinish()\n");
	debugNetFinish();
	//psvDebugScreenPrintf("This app will close in 10 seconds!\n");
	sceKernelDelayThread(5*1000*1000);

	sceKernelExitProcess(0);
	return 0;
}
