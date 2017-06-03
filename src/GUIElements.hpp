#ifndef GUIELEMENTS_HPP
#define GUIELEMENTS_HPP

#include <vita2d.h>
#include <string>

typedef struct{
	float x,y,w,h;
	unsigned int color;
}rectangle;

typedef struct{
	std::string name;
	
}image;


typedef struct{
	int x;
	int y;
	int w;
	int h;
	
}inputbox;


#endif