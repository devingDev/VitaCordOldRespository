#include "net_functions.hpp"


size_t writeCallback(char* buf, size_t size, size_t nmemb, void* up)
{ //callback must have this declaration
    //buf is a pointer to the data that curl has for us
    //size*nmemb is the size of the buffer

    for (int c = 0; c<size*nmemb; c++)
    {
        data.push_back(buf[c]);
    }
	
    return size*nmemb; //tell curl how many bytes we handled
}


void initializeNetworking(){
	netInit();
	httpInit();
	curl_global_init(CURL_GLOBAL_ALL);
}

void terminateNetworking(){
	curl_global_cleanup();
	httpTerm();
	netTerm();
}

void netInit() {
	sceSysmoduleLoadModule(SCE_SYSMODULE_NET);
	SceNetInitParam netInitParam;
	int size = 1*1024*1024;
	netInitParam.memory = malloc(size);
	netInitParam.size = size;
	netInitParam.flags = 0;
	sceNetInit(&netInitParam);
	sceNetCtlInit();
}

void netTerm() {
	sceNetCtlTerm();
	sceNetTerm();
	sceSysmoduleUnloadModule(SCE_SYSMODULE_NET);
}

void httpInit() {
	sceSysmoduleLoadModule(SCE_SYSMODULE_HTTP);
	sceHttpInit(1*1024*1024);
}

void httpTerm() {
	sceHttpTerm();	
	sceSysmoduleUnloadModule(SCE_SYSMODULE_HTTP);
}

long curlDiscordGet(std::string url){
	
	data = "";
	long http_code = 0;
	
	//DBG
	//url = "http://jaynapps.com/psvita/httpdump.php";
	
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
			//fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

			
		}else{
			
		}
		
		
	}else{
		
	}
	curl_easy_cleanup(curl);
	
	return http_code;
}

long curlDiscordPost(std::string url , std::string postData){
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
		
		std::string ContentLengthS = "Content-Length: " + std::to_string(strlen(postData.c_str()));
		headerchunk = curl_slist_append(headerchunk, ContentLengthS.c_str());
		res = curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerchunk);
		
		curl_easy_setopt(curl, CURLOPT_POST, 1L);
		
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)strlen(postData.c_str()));
		
		curl_easy_setopt(curl, CURLOPT_USERAGENT, userAgent);
		
		
		res = curl_easy_perform(curl);
		curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &http_code);
		if(res != CURLE_OK){
			//fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

			/* always cleanup */ 
			
		}else{
			
		}
		
		
	}
	curl_easy_cleanup(curl);
	
	return http_code;
	
}
