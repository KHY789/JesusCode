#pragma comment(lib, "Opengl32.lib") // Windows에서 OpenGL 라이브러리 사용
#include <GLFW/glfw3.h>// GLFW 라이브러리

/* NuGet 패키지 매니져에서 GLFW 설치후 사용*/

#include <math.h> // sinf, cosf 사용
#define PI 3.1415926535f // 원주율(PI) 상수 사용


int main() {
    if (!glfwInit()) return -1;

    // 500x500 크기의 창 생성, 제목 설정
    GLFWwindow* window = glfwCreateWindow(500, 500, "GLFW: Circle", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
        // 창 생성 실패 시 GLFW 종료 후 프로그램 종료
    }

    // 생성된 창의 OpenGL 컨텍스트를 현재 스레드에 바인딩 ('window' 창에 그림 그리기)
    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window)) {
        // 현재 컬러 버퍼 지우기 (검은색)
        glClear(GL_COLOR_BUFFER_BIT);

        // 원 그리기
        float radius = 0.4f; // 원의 반지름
        int segments = 100;

        // GL_TRIANGLE_FAN으로 그리기 (첫 정점을 중심으로 삼각형들을 연결)
        glBegin(GL_TRIANGLE_FAN);
        glColor3f(1.0f, 0.0f, 0.0f); // 중심 색 (빨간색)
        glVertex2f(0.0f, 0.0f); // 중심 좌표 (화면 중앙)

        // 원 둘레에 따라 segments 수만큼 점들을 계산 후 추가
        for (int i = 0; i <= segments; i++) {
            float angle = 2.0f * PI * i / segments;
            float x = radius * cosf(angle);
            float y = radius * sinf(angle);

            glColor3f(0.0f, 0.0f, 1.0f); // 외곽 색상 (파란색)
            glVertex2f(x, y); // 원 둘레 점의 좌표
        }
        glEnd();

        glfwSwapBuffers(window); // 백 버퍼 --> 프론트 버퍼 (화면에 표시)
        glfwPollEvents(); // 이벤트 처리
    }

    // 메인 루프 종료
    glfwDestroyWindow(window);
    // GLFW 라이브러리 종료
    glfwTerminate();

    return 0;
}
