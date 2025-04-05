#include <stdio.h>
#include <windows.h>

typedef struct {
    int startX;
    int startY;
    int width;
    int height;
    char* name;
    char* bgColor;
    char* horizontal_Line;
    char* vertical_Line;
    char* vertical_Line2;
} WindowAttributes;

void gotoxy(int x, int y) {
    COORD Cur;
    Cur.X = x;
    Cur.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

void DrawLine(int x, int y, const char* text) {
    gotoxy(x, y);
    printf("%s", text);
}

void DrawRectangle(WindowAttributes attr) {
    printf("%s", attr.bgColor);

    DrawLine(attr.startX, attr.startY + 1, attr.horizontal_Line);
    DrawLine(attr.startX, attr.startY + 2, attr.vertical_Line);
    DrawLine(attr.startX, attr.startY + 3, attr.horizontal_Line);

    for (int i = 4; i <= 7; i++) {
        DrawLine(attr.startX, attr.startY + i, attr.vertical_Line2);
    }
    DrawLine(attr.startX, attr.startY + 7, attr.horizontal_Line);

    printf("\033[0m");
}

int main() {
    printf("\033[42m");

    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 120; j++) {
            printf(" ");
        }
        printf("\n");
    }

    printf("\033[0m");

    char* horizontal_Line = " -------------------- \n";
    char* vertical_Line = "びHayun1      - け Xび\n";
    char* vertical_Line2 = "び                  び\n";

    WindowAttributes window1 = {
        10,
        3,
        22,
        9,
        "HayunWindow1",
        "\033[47m\033[30m",
        horizontal_Line,
        vertical_Line,
        vertical_Line2
    };

    WindowAttributes window2 = {
        15,
        5,
        22,
        9,
        "HayunWindow2",
        "\033[43m\033[30m",
        horizontal_Line,
        vertical_Line,
        vertical_Line2
    };

    DrawRectangle(window1);
    DrawRectangle(window2);

    gotoxy(0, 25);

    return 0;
}
