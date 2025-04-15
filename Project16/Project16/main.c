#include <windows.h>
#include <stdio.h>

HWND consoleWindow; // 콘솔 창 핸들
HDC consoleDC; // 콘솔 장치 컨텍스트 핸들
int charWidth, charHeight; // 콘솔 문자 가로, 세로 크기
int consoleWidth = 155; // 콘솔 가로 크기
int consoleHeight = 40; // 콘솔 세로 크기
float dragSensitivity = 1.0f; // 드래그 민감도
int initialMouseY = -2; // 마우스 Y축 초기 위치 보정값
int offsetY = 2; // 마우스 Y축 오프셋

// 초기화 함수
void initialize() {

    consoleWindow = GetConsoleWindow();
    consoleDC = GetDC(consoleWindow);

    TEXTMETRIC tm;
    GetTextMetrics(consoleDC, &tm);

    charWidth = tm.tmAveCharWidth;
    charHeight = tm.tmHeight;

    system("cls");
}

// 마우스 위치 계산 및 제한 함수
void getMousePosition(int* mouseX, int* mouseY) {

    POINT p;
    GetCursorPos(&p);
    ScreenToClient(consoleWindow, &p);

    *mouseX = (p.x - 10) / charWidth;
    *mouseY = ((p.y - offsetY) / charHeight) + initialMouseY;

    *mouseX = (*mouseX < 0) ? 0 : (*mouseX > consoleWidth - 1) ? consoleWidth - 1 : *mouseX;
    *mouseY = (*mouseY < 0) ? 0 : (*mouseY > consoleHeight - 1) ? consoleHeight - 1 : *mouseY;
}

// 드래그 처리 함수
void handleDrag(int mouseX, int mouseY, char* letter, int* letterX, int* letterY, int* dragStartX, int* dragStartY, int* isDragging) {

    if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
        if (!*isDragging && mouseX == *letterX && mouseY == *letterY) {
            *isDragging = 1;
            // 드래그 시작 위치 저장
            *dragStartX = mouseX;
            *dragStartY = mouseY;
        }

        // 드래그 중 'Q' 위치 업데이트
        if (*isDragging) {
            *letterX += (int)((mouseX - *dragStartX) * dragSensitivity);
            *letterY += (int)((mouseY - *dragStartY) * dragSensitivity);

            // 'Q' 위치 제한 (콘솔 창 경계)
            *letterX = (*letterX < 0) ? 0 : (*letterX > consoleWidth - 1) ? consoleWidth - 1 : *letterX;
            *letterY = (*letterY < 0) ? 0 : (*letterY > consoleHeight - 1) ? consoleHeight - 1 : *letterY;

            // 드래그 시작 위치 업데이트
            *dragStartX = mouseX;
            *dragStartY = mouseY;
        }
    }
    else {
        *isDragging = 0;
    }
}

// 화면 출력 함수
void drawScreen(char letter, int letterX, int letterY, int mouseX, int mouseY) {

    system("cls");
    printf("알파벳 '%c'을 마우스로 드래그하세요.\n", letter);
    printf("현재 알파벳 '%c'의 위치: (%d, %d)\n", letter, letterX, letterY);
    printf("마우스 위치: X=%d, Y=%d\n", mouseX, mouseY);

    // 'Q' 출력 위치 계산
    int displayX = letterX % (consoleWidth + 1);
    int numLines = letterX / (consoleWidth + 1);
    COORD coord = { (SHORT)displayX, (SHORT)(letterY + numLines) };
    // 콘솔 커서 위치 설정
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    printf("%c", letter);

    // 마우스 커서 출력 위치 설정 구조체
    COORD mouseCoord = { (SHORT)mouseX, (SHORT)mouseY };
    // 콘솔 커서 위치 설정
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), mouseCoord);
    printf(">");
}

// 종료 처리 함수
void cleanup() {
    ReleaseDC(consoleWindow, consoleDC);
}

int main() {
    char letter = 'Q'; // 드래그할 문자
    int letterX = 77; // 문자 X 좌표
    int letterY = 20; // 문자 Y 좌표
    int dragStartX, dragStartY; // 드래그 시작 X, Y 좌표
    int isDragging = 0; // 드래그 여부
    int mouseX, mouseY; // 마우스 X, Y 좌표

    initialize();

    while (1) {
        // 마우스 위치 얻기
        getMousePosition(&mouseX, &mouseY);
        // 드래그 처리
        handleDrag(mouseX, mouseY, &letter, &letterX, &letterY, &dragStartX, &dragStartY, &isDragging);
        // 화면 출력
        drawScreen(letter, letterX, letterY, mouseX, mouseY);

        // 종료
        if (GetAsyncKeyState(VkKeyScan('q')) & 0x8000) {

            break;
        }

        Sleep(10);
    }

    cleanup();

    return 0;
}
