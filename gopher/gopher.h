#ifndef __GOPHER_H
#define __GOPHER_H

#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <Windows.h>

#define MAX_X	3
#define MAX_Y	3

#define GOPHER_DEATH_TIME	10
#define HEALTH_PER_GOPHER	5

#define WINDOWS_TEST


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
	uint8_t status;//1表示正常运行，0表示停止运行
}game_typedef;

void gopher_init(gopher_typedef *new_gopher, uint8_t x, uint8_t y, uint16_t ttl);
void game_init(game_typedef *new_game, uint16_t health, uint16_t ttl);
uint8_t hit_gopher(game_typedef *game, uint8_t x, uint8_t y);
uint8_t game_run(game_typedef *game);
uint16_t get_gopher_state(game_typedef *game);
uint8_t gopher_exist(game_typedef *game, uint8_t x, uint8_t y);

#endif

