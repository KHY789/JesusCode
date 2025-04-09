#include <stdio.h>
#include <windows.h>

// 윈도우 속성 구조체 정의
typedef struct {
    int x, y;     // 윈도우 시작 좌표
    int w, h;     // 윈도우 가로, 세로 크기
    char* name;   // 윈도우 이름
    char* color;  // 윈도우 배경색 및 글자색 (ANSI 코드)
} WinAttr;

// 콘솔 커서 위치 이동 함수
void gotoxy(int x, int y) {
    COORD Cur;
    Cur.X = x;
    Cur.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

// 지정된 위치에 문자열을 출력하는 함수
void DrawLine(int x, int y, const char* text) {
    gotoxy(x, y);
    printf("%s", text);
}

// 윈도우 그리기 함수
void DrawWindowUnified(WinAttr Win) {

    //윈도우 내부 채우기 (공백)
    for (int i = 1; i < Win.h - 1; i++) {
        gotoxy(Win.x, Win.y + i);
        printf("%s", Win.color);
        for (int j = 0; j < Win.w; j++) {
            printf(" ");
        }
        printf("\033[0m");
    }

    //윈도우 상단 가로선 그리기
    gotoxy(Win.x, Win.y);
    printf("%s", Win.color);
    printf(" ");
    for (int i = 0; i < Win.w; i++) {
        printf("-");
    }
    printf(" \033[0m");

    //윈도우 세로선 그리기 (왼쪽, 오른쪽)
    for (int i = 1; i < Win.h - 1; i++) {
        gotoxy(Win.x, Win.y + i);
        printf("%s", Win.color);
        printf("ㅣ");
        printf("\033[0m");

        gotoxy(Win.x + Win.w - 1, Win.y + i);
        printf("%s", Win.color);
        printf(" ㅣ");
        printf("\033[0m");

        // 첫 번째 윈도우에 텍스트 삽입
        if (Win.name[strlen(Win.name) - 1] == '1' && i == 1) {
            gotoxy(Win.x + 2, Win.y + i);
            printf("%sHayun1      - ㅁ X\033[0m", Win.color);
        }

        // 두 번째 윈도우에 텍스트 삽입
        if (Win.name[strlen(Win.name) - 1] == '2' && i == 1) {
            gotoxy(Win.x + 2, Win.y + i);
            printf("%sHayun2      - ㅁ X\033[0m", Win.color);
        }
    }

    //윈도우 중간 가로선 그리기
    gotoxy(Win.x, Win.y + Win.h - 5);
    printf("%s", Win.color);
    printf(" ");
    for (int i = 0; i < Win.w; i++) {
        printf("-");
    }
    printf(" \033[0m");

    //윈도우 하단 가로선 그리기
    gotoxy(Win.x, Win.y + Win.h - 1);
    printf("%s", Win.color);
    printf(" ");
    for (int i = 0; i < Win.w; i++) {
        printf("-");
    }
    printf(" \033[0m");
}

int main() {
    // 콘솔 전체 배경색 설정 (초록색)
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
