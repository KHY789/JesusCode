#pragma comment(lib, "Opengl32.lib")
#include <GLFW/glfw3.h>
#include <math.h>

#define PI 3.1415926535f

// 원 그리기 함수
void drawCircle(float cx, float cy, float radius, int segments, float r, float g, float b) {
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(r, g, b);
    glVertex2f(cx, cy);
    for (int i = 0; i <= segments; i++) {
        float angle = 2.0f * PI * i / segments;
        float x = radius * cosf(angle);
        float y = radius * sinf(angle);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

// 사각형 그리기 함수
void drawRectangle(float centerX, float centerY, float width, float height, float angleDeg, float r, float g, float b) {
    float angleRad = angleDeg * PI / 180.0f;

    float halfW = width / 2.0f;
    float halfH = height / 2.0f;

    // 네 꼭짓점 좌표 (중심 기준)
    float corners[4][2] = {
        {-halfW, -halfH},
        { halfW, -halfH},
        { halfW,  halfH},
        {-halfW,  halfH}
    };

    glBegin(GL_QUADS);
    glColor3f(r, g, b);
    for (int i = 0; i < 4; ++i) {
        float x = corners[i][0];
        float y = corners[i][1];

        // 회전 변환
        float rotatedX = x * cosf(angleRad) - y * sinf(angleRad);
        float rotatedY = x * sinf(angleRad) + y * cosf(angleRad);

        glVertex2f(centerX + rotatedX, centerY + rotatedY);
    }
    glEnd();
}


int main() {
    if (!glfwInit()) return -1;

    GLFWwindow* window = glfwCreateWindow(1000, 1000, "GLFW: Ellipse with Circles", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        int segments = 100;
        float radiusX = 0.7f;
        float radiusY = 0.65f;

        // 큰 파란 타원
        glBegin(GL_TRIANGLE_FAN);
        glColor3f(0.22f, 0.4f, 0.74f);
        glVertex2f(0.0f, 0.0f);
        for (int i = 0; i <= segments; i++) {
            float angle = 2.0f * PI * i / segments;
            float x = radiusX * cosf(angle);
            float y = radiusY * sinf(angle);
            glVertex2f(x, y);
        }
        glEnd();

        // 테두리
        glLineWidth(4.0f);
        glBegin(GL_LINE_LOOP);
        glColor3f(0.0f, 0.0f, 0.0f);
        for (int i = 0; i <= segments; i++) {
            float angle = 2.0f * PI * i / segments;
            float x = radiusX * cosf(angle);
            float y = radiusY * sinf(angle);
            glVertex2f(x, y);
        }
        glEnd();

        float whiteRadius = 0.15f;

        // 원3 - 오른쪽 위
        drawCircle(-0.14f, -0.19f, whiteRadius, segments, 1.0f, 1.0f, 1.0f);

        // 원4 - 오른쪽 위
        drawCircle(0.14f, -0.19f, whiteRadius, segments, 1.0f, 1.0f, 1.0f);

        // 중심 타원 (검은색)
        float ellipseCenterX = 0.0f;
        float ellipseCenterY = -0.05f;
        float ellipseRadiusX = 0.11f;
        float ellipseRadiusY = 0.09f;

        glBegin(GL_TRIANGLE_FAN);
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(ellipseCenterX, ellipseCenterY);
        for (int i = 0; i <= segments; i++) {
            float angle = 2.0f * PI * i / segments;
            float x = ellipseRadiusX * cosf(angle);
            float y = ellipseRadiusY * sinf(angle);
            glVertex2f(ellipseCenterX + x, ellipseCenterY + y);
        }
        glEnd();

        float smallRadius = 0.05f;

        // 원1 - 왼쪽 위
        drawCircle(-0.57f, 0.15f, smallRadius, segments, 0.0f, 0.0f, 0.0f);

        // 원2 - 오른쪽 위
        drawCircle(0.57f, 0.15f, smallRadius, segments, 0.0f, 0.0f, 0.0f);

        // 네모1
        float rect1X = -0.35f;  // 네모 중심 x
        float rect1Y = -0.18f;  // 네모 중심 y
        float rect1Width = 0.3f;
        float rect1Height = 0.01f;
        drawRectangle(rect1X, rect1Y, rect1Width, rect1Height, 0.0f, 0.0f, 0.0f, 0.0f);

        // 네모2
        float rect2X = -0.35f;
        float rect2Y = -0.08f;
        float rect2Width = 0.3f;
        float rect2Height = 0.01f;
        float rect2Angle = -15.0f; // 도 단위
        drawRectangle(rect2X, rect2Y, rect2Width, rect2Height, rect2Angle, 0.0f, 0.0f, 0.0f);

        // 네모3
        float rect3X = -0.35f;
        float rect3Y = -0.28f;
        float rect3Width = 0.3f;
        float rect3Height = 0.01f;
        float rect3Angle = 15.0f;
        drawRectangle(rect3X, rect3Y, rect3Width, rect3Height, rect3Angle, 0.0f, 0.0f, 0.0f);

        // 네모4
        float rect4X = +0.35f;  // 네모 중심 x
        float rect4Y = -0.18f;  // 네모 중심 y
        float rect4Width = 0.3f;
        float rect4Height = 0.01f;
        drawRectangle(rect4X, rect4Y, rect4Width, rect4Height, 0.0f, 0.0f, 0.0f, 0.0f);

        // 네모5
        float rect5X = +0.35f;
        float rect5Y = -0.08f;
        float rect5Width = 0.3f;
        float rect5Height = 0.01f;
        float rect5Angle = 15.0f; // 도 단위
        drawRectangle(rect5X, rect5Y, rect5Width, rect5Height, rect5Angle, 0.0f, 0.0f, 0.0f);

        // 네모6
        float rect6X = +0.35f;
        float rect6Y = -0.28f;
        float rect6Width = 0.3f;
        float rect6Height = 0.01f;
        float rect6Angle = -15.0f;
        drawRectangle(rect6X, rect6Y, rect6Width, rect6Height, rect6Angle, 0.0f, 0.0f, 0.0f);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
