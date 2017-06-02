#ifndef DISCORDAPP_HPP
#define DISCORDAPP_HPP

#include "VitaTouch.hpp"
#include "VitaPad.hpp"
#include "VitaIME.hpp"
#include "Discord.hpp"


class DiscordApp{
	
	public:
		void Start();
		
	private:
		Discord discord;
		VitaIME vitaIME;
		VitaPad vitaPad;
		VitaTouch vitaTouch;
	
};



#endif