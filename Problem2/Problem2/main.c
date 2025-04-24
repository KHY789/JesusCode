#include <stdio.h>
#include <Windows.h>

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

#define LEFT_MARGIN 2
#define RIGHT_MARGIN 2
#define TOP_MARGIN 1
#define BOTTOM_MARGIN 1

// 커서를 (row, col) 위치로 이동하는 함수
void move_cursor(int row, int col) {
    // ANSI escape code: \033[row;colH
    printf("\033[%d;%dH", row + 1, col + 1);
}

int main() {
    // 콘솔 화면 전체를 지우고 커서 숨기기
    system("cls");
    printf("\033[?25l"); // 커서 숨기기

    // 화면 전체를 배경색 없이 공백으로 초기화 (선택사항)
    for (int r = 0; r < SCREEN_HEIGHT; r++) {
        move_cursor(r, 0);
        for (int c = 0; c < SCREEN_WIDTH; c++) {
            putchar(' ');
        }
    }

    // 파란색 배경으로 칠할 영역 크기 계산
    int start_row = TOP_MARGIN;
    int end_row = SCREEN_HEIGHT - BOTTOM_MARGIN - 1;
    int start_col = LEFT_MARGIN;
    int end_col = SCREEN_WIDTH - RIGHT_MARGIN - 1;

    // 영역을 파란 배경으로 칠하기
    for (int r = start_row; r <= end_row; r++) {
        move_cursor(r, start_col);
        for (int c = start_col; c <= end_col; c++) {
            // \033[44m : 파란 배경
            // 공백 문자 출력
            printf("\033[44m \033[0m");
        }
    }

    // 작업 끝난 후 커서 보이도록 설정
    printf("\033[?25h");
    move_cursor(SCREEN_HEIGHT, 0); // 커서를 마지막 줄로 이동

    return 0;
}
