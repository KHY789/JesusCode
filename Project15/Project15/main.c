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
// ���� �÷��̾� ��ġ ����
int prevPlayerX, prevPlayerY;

void gotoxy(int x, int y) {
    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// �Ķ��� ���
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
    // �ʱ� ��ġ ����
    playerX = 60;
    playerY = 12;
    prevPlayerX = playerX;
    prevPlayerY = playerY;

    system("cls");

    // �ʱ� ��� �׸���
    draw_green_background();

    while (1) {
        // ���� ��ġ �Ķ������� ĥ�ϱ�
        gotoxy(prevPlayerX, prevPlayerY);
        printf("\033[44m \033[0m");

        // W Ű�� ���ȴ��� Ȯ�� (key down)
        if (GetAsyncKeyState(VK_W) & 0x8000) {
            if (playerY > 0) {
                playerY--;
            }
        }

        // S Ű�� ���ȴ��� Ȯ�� (key down)
        if (GetAsyncKeyState(VK_S) & 0x8000) {
            if (playerY < 24) {
                playerY++;
            }
        }

        // A Ű�� ���ȴ��� Ȯ�� (key down)
        if (GetAsyncKeyState(VK_A) & 0x8000) {
            if (playerX > 0) {
                playerX--;
            }
        }

        // D Ű�� ���ȴ��� Ȯ�� (key down)
        if (GetAsyncKeyState(VK_D) & 0x8000) {
            if (playerX < 119) {
                playerX++;
            }
        }

        if (GetAsyncKeyState(VK_Q) & 0x8000) {
        // ȭ�� �߾ӿ� "���� ����" ���
        gotoxy(54, 12);
        printf("\033[44m\033[37m �� ��   �� �� \033[0m\n");
            break;
        }

        // Q (ĳ����) ���� �����ϱ�
        gotoxy(playerX, playerY);
        printf("\033[44m\033[38;5;196mQ\033[0m");

        // ���� ��ġ�� ���� ��ġ�� ����
        prevPlayerX = playerX;
        prevPlayerY = playerY;

        Sleep(50);
    }

    gotoxy(0, 25);

    return 0;
}

