#ifndef DISCORD_HPP
#define DISCORD_HPP

#include <string>
#include <vector>
#include "VitaNet.hpp"

#include "json.hpp"

class Discord{
	public:
		Discord();
		~Discord();
		short login(std::string mail , std::string pass);
		short submit2facode(std::string code);
		std::string getToken();
		std::string getTicket();
		
		typedef struct {
			std::string nickname;
			std::string discriminator;
			std::string userid;
			std::string icon;
			
		}user;
		typedef struct {
			user author;
			std::string content;
			std::string embed;
			std::string attachment;
			std::string mentions;
			std::string timestamp;
			std::string messageid;
		}message;
		typedef struct {
			std::string name;
			std::string last_pin_timestamp;
			std::string topic;
			std::string last_message_id;
			std::string type;
			std::string channelid;
			bool is_private;
			
			std::vector<message> messages;
		}channel;
		typedef struct {
			bool owner;
			long permissions;
			std::string icon;
			std::string guildid;
			std::string name;
			std::vector<channel> channels;
		}guild;
	
	private:
		VitaNet vitaNet;
		std::string email, password , code2fa , token , ticket , nickname , userid , icon , discriminator;
		bool twoFactorAuthEnabled;
		user client;
		bool loggedin;
		
	
	
	
};








#endif