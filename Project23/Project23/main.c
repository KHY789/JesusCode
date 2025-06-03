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

void drawRectangle(float width, float height, float r, float g, float b) {
    glBegin(GL_QUADS);
    glColor3f(r, g, b);

    glVertex2f(-width / 2, height / 2);
    glVertex2f(width / 2, height / 2);
    glVertex2f(width / 2, -height / 2);
    glVertex2f(-width / 2, -height / 2);

    glEnd();
}

void drawTriangle(float sideLength, float r, float g, float b) {
    float radius = sideLength / sqrtf(3.0f);
    glBegin(GL_TRIANGLES);
    glColor3f(r, g, b);

    for (int i = 0; i < 3; ++i) {
        float angle = PI / 2 + i * (2.0f * PI / 3.0f);  // 90도부터 시작
        float x = radius * cosf(angle);
        float y = radius * sinf(angle);
        glVertex2f(x, y);
    }

    glEnd();
}

// 오망성(별) 그리기
void drawStar(float radius, int segments, float r, float g, float b) {
    const float inner_r = 0.5f;
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(r, g, b);
    glVertex2f(0, 0);

    for (int i = 0; i <= segments; i++) {
        float angle = ((float)i / segments) * 2.0f * PI + PI / 2.0f;
        float current_r;
        if (i % 2 == 0) {
            current_r = radius;
        }
        else {
            current_r = radius * inner_r;
        }
        glVertex2f(current_r * cos(angle), current_r * sin(angle));
    }
    glEnd();
}

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

    // 메인 렌더링 루프
    while (!glfwWindowShouldClose(window)) {
        // 화면 클리어
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        drawCircle(0.2, 100, 1.0f, 1.0f, 1.0f);

        glPushMatrix();
        glTranslatef(0.6f, -0.6f, 0.0f);
        drawRectangle(0.5, 0.5, 1.0f, 0.0f, 0.0f);
        glPopMatrix();

        // 별 그리기
        glPushMatrix();
        glTranslatef(-0.6f, 0.6f, 0.0f);
        drawStar(0.1, 10, 1.0f, 1.0f, 0.0f);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0.6f, -0.2f, 0.0f);
        drawTriangle(0.5, 0.0f, 0.0f, 1.0f);
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