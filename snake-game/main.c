#include <windows.h>
#include "game.h"

int main()
{
    setup();
    while (!game_over)
    {
        draw();
        for (int i = 0; i < 10; i++)
        {
            input();   // 每 10 毫秒就侦测一次按键，大幅提升灵敏度
            Sleep(10); // 短暂休息
        }
        logic();
    }
    return 0;
}
