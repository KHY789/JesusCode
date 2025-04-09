#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

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
    