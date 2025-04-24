#include <stdio.h>

// 5. PassOrFail 함수 정의
int PassOrFail(int score) {
    if (score >= 50)
        return 1;
    else
        return 0;
}

int main() {
    int myScore = 40;  // 본인의 예상점수로 변경하세요

    // 6. PassOrFail 함수 호출 후 결과에 따른 출력
    if (PassOrFail(myScore) == 1) {
        printf("재시험 없습니다!\n");
    }
    else {
        printf("우리는 망했다… 재시험이다…\n");
    }

    return 0;
}
