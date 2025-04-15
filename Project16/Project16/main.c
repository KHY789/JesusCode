#include <windows.h>
#include <stdio.h>

HWND consoleWindow; // �ܼ� â �ڵ�
HDC consoleDC; // �ܼ� ��ġ ���ؽ�Ʈ �ڵ�
int charWidth, charHeight; // �ܼ� ���� ����, ���� ũ��
int consoleWidth = 155; // �ܼ� ���� ũ��
int consoleHeight = 40; // �ܼ� ���� ũ��
float dragSensitivity = 1.0f; // �巡�� �ΰ���
int initialMouseY = -2; // ���콺 Y�� �ʱ� ��ġ ������
int offsetY = 2; // ���콺 Y�� ������

// �ʱ�ȭ �Լ�
void initialize() {

    consoleWindow = GetConsoleWindow();
    consoleDC = GetDC(consoleWindow);

    TEXTMETRIC tm;
    GetTextMetrics(consoleDC, &tm);

    charWidth = tm.tmAveCharWidth;
    charHeight = tm.tmHeight;

    system("cls");
}

// ���콺 ��ġ ��� �� ���� �Լ�
void getMousePosition(int* mouseX, int* mouseY) {

    POINT p;
    GetCursorPos(&p);
    ScreenToClient(consoleWindow, &p);

    *mouseX = (p.x - 10) / charWidth;
    *mouseY = ((p.y - offsetY) / charHeight) + initialMouseY;

    *mouseX = (*mouseX < 0) ? 0 : (*mouseX > consoleWidth - 1) ? consoleWidth - 1 : *mouseX;
    *mouseY = (*mouseY < 0) ? 0 : (*mouseY > consoleHeight - 1) ? consoleHeight - 1 : *mouseY;
}

// �巡�� ó�� �Լ�
void handleDrag(int mouseX, int mouseY, char* letter, int* letterX, int* letterY, int* dragStartX, int* dragStartY, int* isDragging) {

    if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
        if (!*isDragging && mouseX == *letterX && mouseY == *letterY) {
            *isDragging = 1;
            // �巡�� ���� ��ġ ����
            *dragStartX = mouseX;
            *dragStartY = mouseY;
        }

        // �巡�� �� 'Q' ��ġ ������Ʈ
        if (*isDragging) {
            *letterX += (int)((mouseX - *dragStartX) * dragSensitivity);
            *letterY += (int)((mouseY - *dragStartY) * dragSensitivity);

            // 'Q' ��ġ ���� (�ܼ� â ���)
            *letterX = (*letterX < 0) ? 0 : (*letterX > consoleWidth - 1) ? consoleWidth - 1 : *letterX;
            *letterY = (*letterY < 0) ? 0 : (*letterY > consoleHeight - 1) ? consoleHeight - 1 : *letterY;

            // �巡�� ���� ��ġ ������Ʈ
            *dragStartX = mouseX;
            *dragStartY = mouseY;
        }
    }
    else {
        *isDragging = 0;
    }
}

// ȭ�� ��� �Լ�
void drawScreen(char letter, int letterX, int letterY, int mouseX, int mouseY) {

    system("cls");
    printf("���ĺ� '%c'�� ���콺�� �巡���ϼ���.\n", letter);
    printf("���� ���ĺ� '%c'�� ��ġ: (%d, %d)\n", letter, letterX, letterY);
    printf("���콺 ��ġ: X=%d, Y=%d\n", mouseX, mouseY);

    // 'Q' ��� ��ġ ���
    int displayX = letterX % (consoleWidth + 1);
    int numLines = letterX / (consoleWidth + 1);
    COORD coord = { (SHORT)displayX, (SHORT)(letterY + numLines) };
    // �ܼ� Ŀ�� ��ġ ����
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    printf("%c", letter);

    // ���콺 Ŀ�� ��� ��ġ ���� ����ü
    COORD mouseCoord = { (SHORT)mouseX, (SHORT)mouseY };
    // �ܼ� Ŀ�� ��ġ ����
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), mouseCoord);
    printf(">");
}

// ���� ó�� �Լ�
void cleanup() {
    ReleaseDC(consoleWindow, consoleDC);
}

int main() {
    char letter = 'Q'; // �巡���� ����
    int letterX = 77; // ���� X ��ǥ
    int letterY = 20; // ���� Y ��ǥ
    int dragStartX, dragStartY; // �巡�� ���� X, Y ��ǥ
    int isDragging = 0; // �巡�� ����
    int mouseX, mouseY; // ���콺 X, Y ��ǥ

    initialize();

    while (1) {
        // ���콺 ��ġ ���
        getMousePosition(&mouseX, &mouseY);
        // �巡�� ó��
        handleDrag(mouseX, mouseY, &letter, &letterX, &letterY, &dragStartX, &dragStartY, &isDragging);
        // ȭ�� ���
        drawScreen(letter, letterX, letterY, mouseX, mouseY);

        // ����
        if (GetAsyncKeyState(VkKeyScan('q')) & 0x8000) {

            break;
        }

        Sleep(10);
    }

    cleanup();

    return 0;
}
