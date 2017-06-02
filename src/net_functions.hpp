#ifndef NET_FUNCTIONS_HPP
#define NET_FUNCTIONS_HPP

#include <psp2/sysmodule.h>
#include <psp2/net/net.h>
#include <psp2/net/netctl.h>
#include <psp2/net/http.h>

#include <curl/curl.h>
#include <string>
#include <string.h>



std::string webhookID = "" , webhookToken = "";

std::string postdata = "{ \"name\":\"coderx3\" }";
const char userAgent[] = "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.36";
const char userAgentHeader[] = "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.36";
std::string data = "";
std::string userToken = "";//"ThisMTI3Ois-AzA5NjgyMTc2.C8rveryUETH3GU08LONGYNSTRINGlOckqoA";
std::string authorizationHeader = "Authorization: Bz832148124";
std::string userMessage = "";
int guildsAmount = 0;
std::vector<guild> guilds;

size_t writeCallback(char* buf, size_t size, size_t nmemb, void* up);
void initializeNetworking();
void netInit();
void netTerm();
void httpInit();
void httpTerm();
void terminateNetworking();
long curlDiscordGet(std::string url);
long curlDiscordPost(std::string url , std::string postData);


#endif