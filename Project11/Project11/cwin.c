#include <windows.h>
#include <stdio.h>

void gotoxy(int x, int y)
{
    COORD Cur;
    Cur.X = x;
    Cur.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

void DrawLine(int x, int y, const char* text) {
    gotoxy(x, y);
    printf("%s", text);
}

int main() {
    char* horizontal_Line = " ----------------------------------------\n";
    char* vertical_Line = "び                                - け Xび\n";
    char* vertical_Line2 = "び                                      び\n";

    DrawLine(0, 1, horizontal_Line);
    DrawLine(0, 2, vertical_Line);
    DrawLine(0, 3, horizontal_Line);

    for (int i = 4; i <= 7; i++) {
        DrawLine(0, i, vertical_Line2);
    }

    DrawLine(0, 8, horizontal_Line);

    return 0;
}