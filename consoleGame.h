#include <conio.h>
#include <stdlib.h>

void initConsole();
void setFPS(int fps);
void LoadingConsole();
void writeString(char *str, int x, int y);
void nextFrame();
void freeConsole();

extern int secondWait;
extern int consoleWidth, consoleHeight;
extern char** consoleBuffer;

#if __WIN32__

#include <windows.h>

void initConsole()
{
    system("chcp 65001");
    system("cls");
}

void setFPS(int fps)
{
    secondWait = 1000 / fps;
}

void LoadingConsole()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        consoleHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
        consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    }
    else {
        // 如果获取失败，使用默认值
        consoleWidth = 80;
        consoleHeight = 25;
    }
    if(consoleBuffer == NULL)
    {
        consoleBuffer = consoleBuffer = (char**)malloc(consoleHeight * sizeof(char*));
        for(int i = 0; i < consoleHeight; i++)
        {
            consoleBuffer[i] = (char*)malloc((consoleWidth + 1) * sizeof(char));
            for(int j = 0; j < consoleWidth; j++)
            {
                consoleBuffer[i][j] = ' ';
            }
            consoleBuffer[i][consoleWidth] = '\0';
        }
    }

    system("cls");
}

void writeString(char *str, int startX, int startY)
{
    int charPtr = 0;
    int charX = startX;
    int charY = startY;

    while(str[charPtr] != '\0')
    {
        if(str[charPtr] == '\n')
        {
            charX = startX;
            charY++;
        }
        else
        {
            if(charY < consoleHeight && charX < consoleWidth) {
                consoleBuffer[charY][charX] = str[charPtr];
            }
            charX++;
        }
        charPtr++;
    }
}

void nextFrame()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = {0, 0};
    DWORD charsWritten;

    for(int i = 0; i < consoleHeight; i++)
    {
        coord.Y = i;
        WriteConsoleOutputCharacterA(hConsole, consoleBuffer[i], consoleWidth, coord, &charsWritten);
    }

    Sleep(secondWait);
    
    for(int i = 0; i < consoleHeight; i++)
    {
        for(int j = 0; j < consoleWidth; j++)
        {
            consoleBuffer[i][j] = ' ';
        }
        consoleBuffer[i][consoleWidth] = '\0';
    }
}

void freeConsole()
{
    if(consoleBuffer != NULL)
    {
        for(int i = 0; i < consoleHeight; i++)
        {
            free(consoleBuffer[i]);
        }
    }
    free(consoleBuffer);
    consoleBuffer = NULL;
}

#endif