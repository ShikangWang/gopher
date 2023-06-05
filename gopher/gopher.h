#ifndef __GOPHER_H
#define __GOPHER_H

#include <stdio.h>
#include <stdint.h>
#include <time.h>

#define MAX_X	3
#define MAX_Y	3

typedef struct
{
	uint8_t is_alive; //是否存活
	uint16_t ttl; //剩余存活时间
	uint8_t x; //所在位置的x
	uint8_t y; //所在位置的y
}gopher_typedef;

typedef struct
{
	gopher_typedef gophers[MAX_X * MAX_Y];//所有地鼠
	uint16_t goal;//得分
	uint16_t health;//剩余血量值
	uint16_t ttl;//剩余游戏时间
}game_typedef;

gopher_typedef gopher_init(uint8_t x, uint8_t y);
game_typedef game_init(uint16_t health, uint16_t ttl);


#endif

