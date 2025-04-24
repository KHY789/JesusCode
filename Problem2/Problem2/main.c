#include <stdio.h>
#include <Windows.h>

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

#define LEFT_MARGIN 2
#define RIGHT_MARGIN 2
#define TOP_MARGIN 1
#define BOTTOM_MARGIN 1

// Ŀ���� (row, col) ��ġ�� �̵��ϴ� �Լ�
void move_cursor(int row, int col) {
    // ANSI escape code: \033[row;colH
    printf("\033[%d;%dH", row + 1, col + 1);
}

int main() {
    // �ܼ� ȭ�� ��ü�� ����� Ŀ�� �����
    system("cls");
    printf("\033[?25l"); // Ŀ�� �����

    // ȭ�� ��ü�� ���� ���� �������� �ʱ�ȭ (���û���)
    for (int r = 0; r < SCREEN_HEIGHT; r++) {
        move_cursor(r, 0);
        for (int c = 0; c < SCREEN_WIDTH; c++) {
            putchar(' ');
        }
    }

    // �Ķ��� ������� ĥ�� ���� ũ�� ���
    int start_row = TOP_MARGIN;
    int end_row = SCREEN_HEIGHT - BOTTOM_MARGIN - 1;
    int start_col = LEFT_MARGIN;
    int end_col = SCREEN_WIDTH - RIGHT_MARGIN - 1;

    // ������ �Ķ� ������� ĥ�ϱ�
    for (int r = start_row; r <= end_row; r++) {
        move_cursor(r, start_col);
        for (int c = start_col; c <= end_col; c++) {
            // \033[44m : �Ķ� ���
            // ���� ���� ���
            printf("\033[44m \033[0m");
        }
    }

    // �۾� ���� �� Ŀ�� ���̵��� ����
    printf("\033[?25h");
    move_cursor(SCREEN_HEIGHT, 0); // Ŀ���� ������ �ٷ� �̵�

    return 0;
}
