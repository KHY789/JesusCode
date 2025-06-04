#pragma comment(lib, "Opengl32.lib")
#include <GLFW/glfw3.h>
#include <math.h>
#include <Windows.h>

#define PI 3.1415926535f

int direction = 0; // -1: 역방향, 0: 정지, 1: 순방향

void drawCircle(float radius, int segments, float r, float g, float b) {
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(r, g, b);
    glVertex2f(0, 0);
    for (int i = 0; i <= segments; i++) {
        float angle = 2.0f * PI * i / segments;
        float x = radius * cosf(angle);
        float y = radius * sinf(angle);
        glVertex2f(x, y);
    }
    glEnd();
}

// 창 크기 비율
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // 뷰포트 설정: 창 전체 크기에 맞게 설정
    glViewport(0, 0, width, height);

    // 투영 행렬 설정: 종횡비 유지
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // 종횡비 계산
    float aspect_ratio = (float)width / (float)height;

    // 창의 종횡비에 맞춰 직교 투영 영역 설정
    if (width > height) {
        // 너비가 높이보다 큰 경우: 좌우 영역 확장
        glOrtho(-aspect_ratio, aspect_ratio, -1.0, 1.0, -1.0, 1.0);
    }
    else {
        // 높이가 너비보다 크거나 같은 경우: 상하 영역 확장
        glOrtho(-1.0, 1.0, -1.0 / aspect_ratio, 1.0 / aspect_ratio, -1.0, 1.0);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main() {
    // GLFW 라이브러리 초기화
    if (!glfwInit()) return -1;
    // 창 생성
    GLFWwindow* window = glfwCreateWindow(800, 600, "Circle", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // 화면 비율 1:1
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    framebuffer_size_callback(window, 800, 600);

    // 애니메이션 파라미터 - 공전 반경
    const float earthOrbitR = 0.6f;   // 지구 공전 반경
    const float moonOrbitR = 0.2f;   // 달 공전 반경

    // 애니메이션 각도 변수 - 공전/자전 각도 계산
    float earthOrbitAng = 0.0f;    // 지구 공전
    float earthSelfAng = 0.0f;     // 지구 자전
    float moonOrbitAng = 0.0f;     // 달 공전
    float moonSelfAng = 0.0f;     // 달 자전

    const float earthOrbitSpeed = 0.01f; // 매 프레임마다 0.005도씩 올림
    const float earthSelfSpeed = 0.05f;
    const float moonOrbitSpeed = 0.05f;
    const float moonSelfSpeed = 0.1f;

    // 메인 렌더링 루프
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

        // 화면 클리어
        glClear(GL_COLOR_BUFFER_BIT);

        //  키 입력 처리
        if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
            direction = 1;
        }
        else if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
            direction = -1;
        }
        else {
            direction = 0;
        }

        // 각도 갱신
        earthOrbitAng += direction * earthOrbitSpeed; // 매 프레임마다 각도 증가
        earthSelfAng += direction * earthSelfSpeed;
        moonOrbitAng += direction * moonOrbitSpeed;
        moonSelfAng += direction * moonSelfSpeed;

        glPushMatrix();
        // 태양 그리기
        drawCircle(0.2, 100, 1.0f, 1.0f, 0.0f);
        glRotatef(earthOrbitAng, 0, 0, 1); // 공전(반시계방향) +
        glTranslatef(earthOrbitR, 0.0f, 0.0f);
        glRotatef(-earthSelfAng, 0, 0, 1); // 자전(시계방향) -

        glPushMatrix();
        // 지구 그리기
        drawCircle(0.1, 100, 0.0f, 0.0f, 1.0f);
        glTranslatef(0.05, 0.0f, 0.0f);//@@@
        drawCircle(0.03, 100, 0.0f, 1.0f, 0.5f);//@@@
        glPopMatrix();

        glRotatef(moonOrbitAng, 0, 0, 1); // 공전(반시계방향)
        glTranslatef(moonOrbitR, 0.0f, 0.0f);
        glRotatef(-moonSelfAng, 0, 0, 1); // 자전(시계방향)
        // 달 그리기
        drawCircle(0.05, 100, 0.5f, 0.5f, 0.5f);
        glTranslatef(0.02, 0.0f, 0.0f);//@@@
        drawCircle(0.02, 100, 0.0f, 0.0f, 0.0f);//@@@
        glPopMatrix();


        // 버퍼 스왑 및 이벤트 처리
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    // 렌더링 루프 종료
    glfwDestroyWindow(window);

    glfwTerminate();
    return 0;
}