#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

#ifndef VK_W
#define VK_W 0x57
#endif
#ifndef VK_S
#define VK_S 0x53
#endif
#ifndef VK_A
#define VK_A 0x41
#endif
#ifndef VK_D
#define VK_D 0x44
#endif
#ifndef VK_Q
#define VK_Q 0x51
#endif

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

        // W 키가 눌렸는지 확인 (key down)
        if (GetAsyncKeyState(VK_W) & 0x8000) {
            if (playerY > 0) {
                playerY--;
            }
        }

        // S 키가 눌렸는지 확인 (key down)
        if (GetAsyncKeyState(VK_S) & 0x8000) {
            if (playerY < 24) {
                playerY++;
            }
        }

        // A 키가 눌렸는지 확인 (key down)
        if (GetAsyncKeyState(VK_A) & 0x8000) {
            if (playerX > 0) {
                playerX--;
            }
        }

        // D 키가 눌렸는지 확인 (key down)
        if (GetAsyncKeyState(VK_D) & 0x8000) {
            if (playerX < 119) {
                playerX++;
            }
        }

        if (GetAsyncKeyState(VK_Q) & 0x8000) {
        // 화면 중앙에 "게임 종료" 출력
        gotoxy(54, 12);
        printf("\033[44m\033[37m 게 임   종 료 \033[0m\n");
            break;
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

