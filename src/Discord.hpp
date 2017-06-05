#ifndef DISCORD_HPP
#define DISCORD_HPP

#include <string>
#include <vector>
#include <atomic>

#include "VitaNet.hpp"


class Discord{
	public:
		typedef struct {
			std::string username;
			std::string discriminator;
			std::string id;
			std::string avatar;
			
		}user;
		typedef struct {
			user author;
			std::string content;
			std::string embed;
			std::string attachment;
			std::string mentions;
			std::string timestamp;
			std::string id;
		}message;
		typedef struct {
			std::string name;
			std::string last_pin_timestamp;
			std::string topic;
			std::string last_message_id;
			std::string type;
			std::string id;
			bool is_private;
			
			std::vector<message> messages;
		}channel;
		typedef struct {
			bool owner;
			long permissions;
			std::string icon;
			std::string id;
			std::string name;
			std::vector<channel> channels;
		}guild;
		typedef struct {
			std::string last_message_id;
			long type;
			std::string id;
			std::vector<user> recipients;
			std::vector<message> messages;
		}directMessage;
		
		Discord();
		~Discord();
		void setEmail(std::string mail);
		void setPassword(std::string pass);
		void setToken(std::string tok);
		long login();
		long login(std::string mail , std::string pass);
		long submit2facode(std::string code);
		std::string getToken();
		std::string getTicket();
		std::string getUsername();
		std::string getEmail();
		std::string getPassword();
		void loadData();
		bool loadingData;
		std::vector<guild> guilds;
		std::vector<directMessage> directMessages;
		int guildsAmount = 0;
		static void* loadData_wrapper(void* object)
		{
			reinterpret_cast<Discord*>(object)->thread_loadData(object);
			return 0;
		}
		void JoinGuild(int gIndex);
		uint64_t osGetTimeMS();
		void JoinChannel(int cIndex);
		void JoinDirectMessageChannel(int dIndex);
		int currentGuild = 0;
		int currentChannel = 0;
		int currentDirectMessage = 0;
		bool sendMessage(std::string msg);
		bool sendDirectMessage(std::string msg);
		bool refreshMessages();
		bool refreshDirectMessages();
		bool refreshCurrentDirectMessages();
	
	private:
		VitaNet vitaNet;
		std::string email = "", password = "", code2fa , token , ticket , username , id , avatar , discriminator , phone;
		bool verified, mfa_enabled; // mfa == twofactor its the same
		bool twoFactorAuthEnabled;
		user client;
		bool loggedin;
		bool loadedGuilds ;
		bool loadedChannels;
		bool loadedDMs;
		long fetchUserData();
		void getGuilds();
		void getChannels();
		void getDirectMessageChannels();
		void getChannelMessages(int channelIndex);
		void getCurrentDirectMessages();
		void *thread_loadData(void *arg);
		
		uint64_t lastFetchTimeMS;
		uint64_t fetchTimeMS = 5000; // 4 seconds refreshing
		uint64_t currentTimeMS;
	
};








#endif

