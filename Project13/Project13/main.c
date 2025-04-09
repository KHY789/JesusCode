#include <stdio.h>
#include <windows.h>

// ������ �Ӽ� ����ü ����
typedef struct {
    int x, y;     // ������ ���� ��ǥ
    int w, h;     // ������ ����, ���� ũ��
    char* name;   // ������ �̸�
    char* color;  // ������ ���� �� ���ڻ� (ANSI �ڵ�)
} WinAttr;

// �ܼ� Ŀ�� ��ġ �̵� �Լ�
void gotoxy(int x, int y) {
    COORD Cur;
    Cur.X = x;
    Cur.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

// ������ ��ġ�� ���ڿ��� ����ϴ� �Լ�
void DrawLine(int x, int y, const char* text) {
    gotoxy(x, y);
    printf("%s", text);
}

// ������ �׸��� �Լ�
void DrawWindowUnified(WinAttr Win) {

    //������ ���� ä��� (����)
    for (int i = 1; i < Win.h - 1; i++) {
        gotoxy(Win.x, Win.y + i);
        printf("%s", Win.color);
        for (int j = 0; j < Win.w; j++) {
            printf(" ");
        }
        printf("\033[0m");
    }

    //������ ��� ���μ� �׸���
    gotoxy(Win.x, Win.y);
    printf("%s", Win.color);
    printf(" ");
    for (int i = 0; i < Win.w; i++) {
        printf("-");
    }
    printf(" \033[0m");

    //������ ���μ� �׸��� (����, ������)
    for (int i = 1; i < Win.h - 1; i++) {
        gotoxy(Win.x, Win.y + i);
        printf("%s", Win.color);
        printf("��");
        printf("\033[0m");

        gotoxy(Win.x + Win.w - 1, Win.y + i);
        printf("%s", Win.color);
        printf(" ��");
        printf("\033[0m");

        // ù ��° �����쿡 �ؽ�Ʈ ����
        if (Win.name[strlen(Win.name) - 1] == '1' && i == 1) {
            gotoxy(Win.x + 2, Win.y + i);
            printf("%sHayun1      - �� X\033[0m", Win.color);
        }

        // �� ��° �����쿡 �ؽ�Ʈ ����
        if (Win.name[strlen(Win.name) - 1] == '2' && i == 1) {
            gotoxy(Win.x + 2, Win.y + i);
            printf("%sHayun2      - �� X\033[0m", Win.color);
        }
    }

    //������ �߰� ���μ� �׸���
    gotoxy(Win.x, Win.y + Win.h - 5);
    printf("%s", Win.color);
    printf(" ");
    for (int i = 0; i < Win.w; i++) {
        printf("-");
    }
    printf(" \033[0m");

    //������ �ϴ� ���μ� �׸���
    gotoxy(Win.x, Win.y + Win.h - 1);
    printf("%s", Win.color);
    printf(" ");
    for (int i = 0; i < Win.w; i++) {
        printf("-");
    }
    printf(" \033[0m");
}

int main() {
    // �ܼ� ��ü ���� ���� (�ʷϻ�)
    printf("\033[42m");
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 120; j++) {
            printf(" ");
        }
        printf("\n");
    }
    printf("\033[0m");

    WinAttr win1 = {
        10, 3,
        20, 7,
        "HayunWindow1",
        "\033[47m\033[30m"
    };

    WinAttr win2 = {
        15, 5,
        25, 7,
        "HayunWindow2",
        "\033[43m\033[30m"
    };

    DrawWindowUnified(win1);
    DrawWindowUnified(win2);

    gotoxy(0, 25);

    return 0;
}
