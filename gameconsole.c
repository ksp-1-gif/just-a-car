/*
这个项目主要是做一个简单的汽车控制台小游戏
顺便研发下我的控制台结构
此应用只能在Windows上运行
在其他平台上会输出"This program cannot run on this system."

由于是C代码
所以代码中会含有大量的指针
很有可能会导致内存泄漏
建议在食用的时候严查代码
以防内存泄漏

具体详见consoleGame.h
*/

#include "consoleGame.h"

int consoleWidth = 0, consoleHeight = 0;
int secondWait = 0;
char** consoleBuffer = NULL;

char *car = "█===█\n|   |\n█===█";
char *fence = "=";
char *__exit = "|     |";

#include <time.h>

int main()
{
    srand(time(NULL));
    
    initConsole();
    setFPS(60);
    LoadingConsole();
    
    int fenceExitX = rand() % (consoleWidth - 7);
    int fenceYCnt = 1;
    int carX = consoleWidth / 2;
    int carY = consoleHeight / 2;
    int nopFrame = 50;
    int nopCnt = 0;
    
    while(1)
    {
        if(kbhit())
        {
            char input = getch();
            if(input == 'a' && carX > 0)
            {
                carX -= 1;
            }
            else if(input == 'd' && carX < consoleWidth - 3)
            {
                carX += 1;
            }
            else if(input == 'w' && carY > 0)
            {
                carY -= 1;
            }
            else if(input == 's' && carY < consoleHeight - 5)
            {
                carY += 1;
            }
        }

        if(fenceYCnt > consoleHeight || carY < fenceYCnt - 2)
        {
            Beep(1000, 300);
            fenceYCnt = 1;
            fenceExitX = rand() % (consoleWidth - 7);
        }

        if(fenceYCnt >= carY && fenceYCnt <= carY + 2)
        {
            if(carX < fenceExitX || carX + 4 > fenceExitX + 6)
            {
                writeString("Game Over!", consoleWidth / 2 - 5, consoleHeight / 2);
                nextFrame();
                Beep(1000, 200);
                Beep(1400, 200);
                Beep(1300, 200);
                Beep(900, 200);
                Sleep(1000);
                system("cls");
                break;
            }
        }

        for(int i = 0; i < consoleWidth; i++)
        {
            writeString(fence, i, fenceYCnt);
        }
        writeString(__exit, fenceExitX, fenceYCnt);
        writeString(car, carX, carY);

        nopCnt++;

        if(nopCnt > nopFrame)
        {
            fenceYCnt += 3;
            nopCnt = 0;
        }

        nextFrame();
    }
    freeConsole();
    return 0;
}