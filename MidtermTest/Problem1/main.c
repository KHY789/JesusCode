#include <stdio.h>

// 5. PassOrFail �Լ� ����
int PassOrFail(int score) {
    if (score >= 50)
        return 1;
    else
        return 0;
}

int main() {
    int myScore = 40;  // ������ ���������� �����ϼ���

    // 6. PassOrFail �Լ� ȣ�� �� ����� ���� ���
    if (PassOrFail(myScore) == 1) {
        printf("����� �����ϴ�!\n");
    }
    else {
        printf("�츮�� ���ߴ١� ������̴١�\n");
    }

    return 0;
}
