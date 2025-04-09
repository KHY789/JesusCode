#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

int playerX, playerY;
// 이전 플레이어 위치 저장
int prevPlayerX, prevPlayerY;

void gotoxy(int x, int y) {
    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// 파란색 배경
void draw_green_background() {
    printf("\033[44m");

    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 120; j++) {
            printf(" ");
        }
        printf("\n");
    }

    printf("\033[0m");
}

int main() {
    // 초기 위치 설정
    playerX = 60;
    playerY = 12;
    prevPlayerX = playerX;
    prevPlayerY = playerY;

    system("cls");

    // 초기 배경 그리기
    draw_green_background();

    while (1) {
        // 이전 위치 파란색으로 칠하기
        gotoxy(prevPlayerX, prevPlayerY);
        printf("\033[44m \033[0m");

        if (_kbhit()) {
            char ch = _getch();

            if (ch == 'w' && playerY > 0) {
                playerY--;
            }
            else if (ch == 's' && playerY < 24) {
                playerY++;
            }
            else if (ch == 'a' && playerX > 0) {
                playerX--;
            }
            else if (ch == 'd' && playerX < 119) {
                playerX++;
            }
            else if (ch == 'q') {
                break;
            }
        }

        // Q (캐릭터) 색깔 지정하기
        gotoxy(playerX, playerY);
        printf("\033[44m\033[38;5;196mQ\033[0m");

        // 현재 위치를 이전 위치로 저장
        prevPlayerX = playerX;
        prevPlayerY = playerY;

        Sleep(50);
    }

    gotoxy(0, 25);

    return 0;
}
    