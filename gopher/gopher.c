#include "gopher.h"

uint8_t goal_per_gopher[3] = {5,10,20};
uint16_t gopher_ttl[3] = {2000,1000,500};
uint8_t difficulty = 0;

int main()
{
    game_typedef game;

    srand(time);
    game_init(&game, 100, 60*20);
    
    game.status = 1;
    while (1)
    {
        if (game.status == 1)
        {
            game.status = game_run(&game);
            Sleep(1);
        }
    }
}


void gopher_init(gopher_typedef *new_gopher, uint8_t x, uint8_t y, uint16_t ttl)
{
    new_gopher->is_alive = 1;
    new_gopher->x = x;
    new_gopher->y = y;
    new_gopher->ttl = ttl;
}

void game_init(game_typedef* new_game, uint16_t health, uint16_t ttl)
{
    new_game->goal = 0;
    new_game->health = health;
    new_game->ttl = ttl;
    new_game->status = 0;
}

/*
@brief 击打地鼠
@param game : 游戏结构体; x,y : 击打位置
@return -1 : 击打位置越界; 0 : 未击中; 1 : 击中
*/
uint8_t hit_gopher(game_typedef* game, uint8_t x, uint8_t y)
{
    if (x < 0 || y < 0 || x > MAX_X - 1 || y > MAX_Y - 1)
    {
        return -1;
    }
    else
    {
        if (game->gophers[x + y * MAX_Y].is_alive == 1)
        {
            game->gophers[x + y * MAX_Y].is_alive = 0;
            game->gophers[x + y * MAX_Y].ttl = GOPHER_DEATH_TIME;
            return 1;
        }
        else
            return 0;
    }
}

/*
@brief 游戏运行主体
@param game : 游戏结构体
@return 0 : 游戏结束; 1 : 游戏正常运行
*/
uint16_t count = 0;
uint8_t game_run(game_typedef *game)
{
    uint8_t x = 3, y = 3;
    count++;
    
    if (count == 1000)//地鼠随机生成
    {
        count = 0;
        x = rand() % 3;
        y = rand() % 3;
        gopher_init(&game->gophers[x + MAX_X * y], x, y, gopher_ttl[difficulty]);
    }
    game->ttl -= 1;
    for (int i = 0; i < MAX_X * MAX_Y; i++)
    {
        game->gophers[i].ttl = game->gophers[i].ttl > 0 ? game->gophers[i].ttl - 1 : 0; //地鼠存活时间减少
        if (game->gophers[i].ttl == 0 && game->gophers[i].is_alive == 1) //地鼠一直未被击中
        {
            game->health = game->health > HEALTH_PER_GOPHER ? game->health - HEALTH_PER_GOPHER : 0;
            if (game->health == 0)//生命值清空，游戏结束
                return 0;
        }
    }

    if (1)//判断玩家按下了按键
    {
        //x = rx_recv[0];//求出按键值
        //y = rx_recv[1];
        if (hit_gopher(game, x, y))
        {
            game->goal += goal_per_gopher[difficulty];
        }

    }

    if (game->ttl == 0)//时间到，游戏结束
    {
        return 0;
    }

    return 1;
}