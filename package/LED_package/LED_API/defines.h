#pragma once

typedef unsigned long		DWORD;
typedef unsigned short		WORD;
typedef unsigned char		BYTE;
typedef unsigned int		UNINT32;
typedef struct sockaddr_in	SOCKADDR_IN;
typedef sockaddr			SOCKADDR;
typedef int					SOCKET;

#define u16					unsigned int

#define MAX_LEDS			4

struct config_led_type {
	char name[30];
	char ip[30];
	int  floor_id;
	int  arrow;
};