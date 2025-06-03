#pragma comment(lib, "Opengl32.lib")
#include <GLFW/glfw3.h>
#include <math.h>
#include <Windows.h>

#define PI 3.1415926535f


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

// 스마일맨 얼굴(눈 + 입) 그리기
void drawFace(float eyeR, float eyeOffsetX, float eyeOffsetY, float mouthRadius) {
    // 왼쪽 눈
    glPushMatrix();
    glTranslatef(-eyeOffsetX, eyeOffsetY, 0.0f);
    drawCircle(eyeR, 16, 0.0f, 0.0f, 0.0f);
    glPopMatrix();

    // 오른쪽 눈
    glPushMatrix();
    glTranslatef(eyeOffsetX, eyeOffsetY, 0.0f);
    drawCircle(eyeR, 16, 0.0f, 0.0f, 0.0f);
    glPopMatrix();

    glLineWidth(5.0f); // 선 두께
    glBegin(GL_LINE_STRIP);
    // 웃는 입 (반원 아크)
    float mouthYOffset = -0.03f;
    for (int i = 0; i <= 100; ++i) {
        float a = (180.0f + 180.0f * i / 100.0f) * (PI / 180.0f);
        glVertex2f(cosf(a) * mouthRadius, sinf(a) * mouthRadius + mouthYOffset);
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
    GLFWwindow* window = glfwCreateWindow(1000, 935, "Circle", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // 화면 비율 1:1
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    framebuffer_size_callback(window, 1000, 935);

    // 애니메이션 파라미터
    const float smileOrbitR = 0.7f;   // 스마일맨 공전 반경

    // 메인 렌더링 루프
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

        // 화면 클리어
        glClear(GL_COLOR_BUFFER_BIT);

        // 공전/자전 각도 계산
        float t = (float)glfwGetTime();
        float smileOrbitAng = t * 60.0f;    // 스마일맨 공전 속도


        glPushMatrix();
        glRotatef(-smileOrbitAng, 0, 0, 1);
        glTranslatef(-smileOrbitR, 0.0f, 0.0f); // 공전
        // 스마일 얼굴 그리기
        drawCircle(0.2, 100, 1.0f, 1.0f, 0.0f);

        glPushMatrix();
        glRotatef(smileOrbitAng, 0, 0, 1);
        // 스마일 눈, 입 그리기
        drawFace(0.02, 0.07, 0.05, 0.06);

        glPopMatrix();
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