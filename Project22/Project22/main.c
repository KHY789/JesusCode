#pragma comment(lib, "Opengl32.lib")
#include <GLFW/glfw3.h>
#include <math.h>
#include <time.h>

#define PI 3.1415926535f

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

void drawRectangle(float centerX, float centerY, float width, float height, float angleDeg, float r, float g, float b) {
    float angleRad = angleDeg * PI / 180.0f;

    float halfW = width / 2.0f;
    float halfH = height / 2.0f;

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

        float rotatedX = x * cosf(angleRad) - y * sinf(angleRad);
        float rotatedY = x * sinf(angleRad) + y * cosf(angleRad);

        glVertex2f(centerX + rotatedX, centerY + rotatedY);
    }
    glEnd();
}

void drawHandTriangle(float angleDeg, float length, float width, float r, float g, float b) {
    float angleRad = angleDeg * PI / 180.0f;
    float x = length * cosf(angleRad);
    float y = length * sinf(angleRad);

    float leftX = width * cosf(angleRad + PI / 2);
    float leftY = width * sinf(angleRad + PI / 2);

    float rightX = width * cosf(angleRad - PI / 2);
    float rightY = width * sinf(angleRad - PI / 2);

    glBegin(GL_TRIANGLES);
    glColor3f(r, g, b);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(x, y);
    glVertex2f(leftX, leftY);
    glVertex2f(rightX, rightY);
    glEnd();
}

void drawHexSegment(float centerX, float centerY, float length, float thickness, float angleDeg, float r, float g, float b) {
    float angleRad = angleDeg * PI / 180.0f;
    float halfL = length / 2.0f;
    float halfT = thickness / 2.0f;

    float vertices[6][2] = {
        {-halfL + halfT,  halfT},
        { halfL - halfT,  halfT},
        { halfL,          0.0f},
        { halfL - halfT, -halfT},
        {-halfL + halfT, -halfT},
        {-halfL,          0.0f},
    };

    glBegin(GL_POLYGON);
    glColor3f(r, g, b);
    for (int i = 0; i < 6; ++i) {
        float x = vertices[i][0];
        float y = vertices[i][1];
        // 회전 변환
        float rotatedX = x * cosf(angleRad) - y * sinf(angleRad);
        float rotatedY = x * sinf(angleRad) + y * cosf(angleRad);
        glVertex2f(centerX + rotatedX, centerY + rotatedY);
    }
    glEnd();
}

const int SEGMENTS[10][7] = {
    // A B C D E F G
    {1, 1, 1, 1, 1, 1, 0}, // 0
    {0, 1, 1, 0, 0, 0, 0}, // 1
    {1, 1, 0, 1, 1, 0, 1}, // 2
    {1, 1, 1, 1, 0, 0, 1}, // 3
    {0, 1, 1, 0, 0, 1, 1}, // 4
    {1, 0, 1, 1, 0, 1, 1}, // 5
    {1, 0, 1, 1, 1, 1, 1}, // 6
    {1, 1, 1, 0, 0, 0, 0}, // 7
    {1, 1, 1, 1, 1, 1, 1}, // 8
    {1, 1, 1, 1, 0, 1, 1}, // 9
};

void drawDigit(float x, float y, float size, int digit, float r, float g, float b) {
    float segLength = size;
    float segThick = size * 0.2f;
    float offset = size * 0.55;
    float Gap = offset * 2.0f;
    float bottomGap = offset * 1.5f;

    // 세그먼트 위치 (center 기준 상대좌표)
    float positions[7][3] = {
        {x, y + offset, 0.0f},        // A
        {x + offset, y, 90.0f},       // B
        {x + offset, y - Gap, 90.0f}, // C
        {x, y - 2 * bottomGap, 0.0f},    // D
        {x - offset, y - Gap, 90.0f}, // E
        {x - offset, y, 90.0f},       // F
        {x, y - offset, 0.0f},        // G
    };

    for (int i = 0; i < 7; ++i) {
        if (SEGMENTS[digit][i]) {
            drawHexSegment(positions[i][0], positions[i][1], segLength, segThick, positions[i][2], r, g, b);
        }
    }
}

void drawColon(float x, float y, float radius) {
    drawCircle(x, y + radius * 1.5f, radius, 20, 1.0f, 1.0f, 1.0f);
    drawCircle(x, y - radius * 1.5f, radius, 20, 1.0f, 1.0f, 1.0f);
}

int main() {
    if (!glfwInit()) return -1;

    GLFWwindow* window = glfwCreateWindow(1000, 1000, "GLFW: Ellipse Clock", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    const int segments = 100;
    const float radiusX = 0.9f;
    const float radiusY = 0.9f;

    double startTime = glfwGetTime();

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        double elapsedTime = glfwGetTime() - startTime;
        int totalSeconds = (int)elapsedTime;

        float minuteAngle = 6.0f * ((totalSeconds / 60) % 60);      // 분침 각도
        float hourAngle = 30.0f * ((totalSeconds / 3600) % 12);     // 시침 각도

        // 시계 배경 타원
        glBegin(GL_TRIANGLE_FAN);
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(0.0f, 0.0f);
        for (int i = 0; i <= segments; ++i) {
            float angle = 2.0f * PI * i / segments;
            glVertex2f(radiusX * cosf(angle), radiusY * sinf(angle));
        }
        glEnd();

        // 테두리
        glLineWidth(6.0f);
        glBegin(GL_LINE_LOOP);
        glColor3f(1.0f, 1.0f, 0.5f);
        for (int i = 0; i <= segments; i++) {
            float angle = 2.0f * PI * i / segments;
            float x = radiusX * cosf(angle);
            float y = radiusY * sinf(angle);
            glVertex2f(x, y);
        }
        glEnd();

        // 흰색 안쪽 원
        float whiteRadius = 0.85f;
        drawCircle(0.0f, 0.0f, whiteRadius, segments, 1.0f, 1.0f, 1.0f);

        // 문자판 사각형 (12개 위치)
        float baseRadius = 0.78f;
        float baseWidth = 0.1f;
        float baseHeight = 0.02f;

        for (int i = 0; i < 12; ++i) {
            float angle = 2.0f * PI * i / 12.0f;
            float rotationDeg = angle * 180.0f / PI;

            float x, y;
            float width = baseWidth;
            float height = baseHeight;
            float r = 0.0f, g = 0.0f, b = 0.0f;

            if (i == 0 || i == 6) {
                width = 0.13f;
                height = 0.03f;
                x = (baseRadius - 0.01f) * cosf(angle);
                y = (baseRadius - 0.01f) * sinf(angle);
            }
            else if (i == 3 || i == 9) {
                width = 0.12f;
                height = 0.03f;
                x = (baseRadius - 0.01f) * cosf(angle);
                y = (baseRadius - 0.01f) * sinf(angle);
            }
            else {
                x = baseRadius * cosf(angle);
                y = baseRadius * sinf(angle);
            }

            drawRectangle(x, y, width, height, rotationDeg, r, g, b);
        }

        // 48개 눈금
        float tickRadius = 0.78f;
        float tickWidth = 0.05f;
        float tickHeight = 0.008f;

        for (int i = 0; i < 60; ++i) {
            if (i % 5 == 0) continue;
            float angle = 2.0f * PI * i / 60.0f;
            float rotationDeg = angle * 180.0f / PI;
            float x = tickRadius * cosf(angle);
            float y = tickRadius * sinf(angle);
            drawRectangle(x, y, tickWidth, tickHeight, rotationDeg, 0.0f, 0.0f, 0.0f);
        }

        // 시침
        drawHandTriangle(180.0f - hourAngle, 0.65f, 0.04f, 0.0f, 0.0f, 0.0f);
        // 분침
        drawHandTriangle(90.0f - minuteAngle, 0.75f, 0.02f, 0.0f, 0.0f, 1.0f);
        // 중심 원 디자인
        drawCircle(-0.01f, -0.01f, 0.04f, segments, 0.0f, 0.0f, 0.0f);
        drawCircle(-0.01f, -0.01f, 0.035f, segments, 1.0f, 1.0f, 0.5f);
        drawCircle(-0.01f, -0.01f, 0.03f, segments, 0.0f, 0.0f, 0.0f);


        // 공통 중심 좌표
        float centerX = -0.25f;
        float centerY = 0.25f;

        // 노란 원
        float white2Radius = 0.2f;
        drawCircle(centerX, centerY, white2Radius, segments, 1.0f, 1.0f, 0.5f);

        // 흰 원 테두리
        glLineWidth(5.0f);
        glColor3f(0.0f, 0.0f, 0.0f);
        glBegin(GL_LINE_LOOP);
        for (int i = 0; i <= segments; ++i) {
            float angle = 2.0f * PI * i / segments;
            float x = white2Radius * cosf(angle);
            float y = white2Radius * sinf(angle);
            glVertex2f(x + centerX, y + centerY);
        }
        glEnd();

        // 내부 원(초) 12개 문자판
        float tick2Radius = white2Radius * 0.85f;
        float tick2Width = 0.03f;
        float tick2Height = 0.01f;
        for (int i = 0; i < 12; ++i) {
            float angle = 2.0f * PI * i / 12.0f;
            float rotationDeg = angle * 180.0f / PI;
            float x = centerX + tick2Radius * cosf(angle);
            float y = centerY + tick2Radius * sinf(angle);
            drawRectangle(x, y, tick2Width, tick2Height, rotationDeg, 0.0f, 0.0f, 0.0f);
        }

        // 초침 (1초에 6도 = 60초에 한 바퀴)
        float secondAngle = 360.0f - fmodf((float)elapsedTime * 6.0f, 360.0f) + 90.0f;  // 시계방향 회전
        float secHandLength = white2Radius * 0.9f;
        float secHandWidth = 0.01f;
        float secHandHeight = secHandLength;
        drawRectangle(centerX + (secHandLength / 2.0f) * cosf(secondAngle * PI / 180.0f),
            centerY + (secHandLength / 2.0f) * sinf(secondAngle * PI / 180.0f),
            secHandLength, secHandWidth, secondAngle, 1.0f, 0.0f, 0.0f);

        // 검정 중심 원
        float blackCenterRadius = 0.01f;
        drawCircle(centerX, centerY, blackCenterRadius, segments, 0.0f, 0.0f, 0.0f);

        int minutes = (int)(elapsedTime / 60) % 60;
        int hours = (int)(elapsedTime / 3600) % 24;

        // 디지털시계
        int actualDigits[4] = {
            hours / 10,
            hours % 10,
            minutes / 10,
            minutes % 10
        };

        float baseX = -0.415f;
        float baseY = -0.25f;
        float size = 0.15f;
        float gap = 0.25f;

        for (int i = 0; i < 4; ++i) {
            float xOffset = i * gap + (i >= 2 ? gap * 0.3f : 0.0f);

            // 항상 회색 8 먼저 그림
            drawDigit(baseX + xOffset, baseY, size, 8, 0.5f, 0.5f, 0.5f);

            // 실제 시간에 해당하는 숫자만 빨간색으로 덧그림
            drawDigit(baseX + xOffset, baseY, size, actualDigits[i], 1.0f, 0.0f, 0.0f);
        }

        // 콜론 (항상 표시)
        float colonWidth = 0.05f;
        float colonHeight = 0.05f;
        float colonX = baseX + gap * 2 - 0.085f;
        float colonY = baseY - 0.08f;

        drawRectangle(colonX, colonY + 0.08f, colonWidth, colonHeight, 0.0f, 0.5f, 0.5f, 0.5f); // 위 점
        drawRectangle(colonX, colonY - 0.08f, colonWidth, colonHeight, 0.0f, 0.5f, 0.5f, 0.5f); // 아래 점

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    return 0;
}



