#pragma comment(lib, "Opengl32.lib")
#include <GLFW/glfw3.h>
#include <math.h>
#include <Windows.h>

#define PI 3.1415926535f

int wink = 0;
int wKeyPrev = 0;

// 삼각형으로 원 그리기(segments 360 = Circle)
void drawCircle(float radius, int segments, float r, float g, float b) {
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(r, g, b);
    glVertex2f(0, 0);
    for (int i = 0; i < segments; i++) {
        float angle1 = 2.0f * PI * i / segments; // 원은 360도 또는 2π 라디안,  각 점의 각도 =  2π * i / segments
        float angle2 = 2.0f * PI * (i + 1) / segments;
        float x1 = radius * cosf(angle1);
        float y1 = radius * sinf(angle1);
        float x2 = radius * cosf(angle2);
        float y2 = radius * sinf(angle2);
        // 중심점과 외곽 두 점으로 삼각형 구성
        glVertex2f(x1, y1);           // 현재 점
        glVertex2f(x2, y2);           // 다음 점
    }
    glEnd();
}

// 선으로 스마일 눈 + 입 그리기
void drawFace(float eyeHeight, float eyeOffsetX, float eyeOffsetY, float mouthRadius, float r, float g, float b) {
    glColor3f(r, g, b);
    glLineWidth(8.0f); // 선 두께

    glBegin(GL_LINE_STRIP);
    // 오른쪽 눈
    if (wink == 1) {
        // '>'
        glBegin(GL_LINES);
        glVertex2f(eyeOffsetX + eyeHeight / 2, eyeOffsetY + eyeHeight / 2); // '<'는 X좌표에서 - eyeHeight 해주기( + eyeHeight를)
        glVertex2f(eyeOffsetX, eyeOffsetY);                                 // '<'가 왼쪽에 위치하려면 모든 X좌표에 -붙이기( eyeOffsetX를)

        glVertex2f(eyeOffsetX, eyeOffsetY);
        glVertex2f(eyeOffsetX + eyeHeight / 2, eyeOffsetY - eyeHeight / 2);

        glEnd();
    }
    else {
        // 'I'
        glBegin(GL_LINES);
        glVertex2f(eyeOffsetX, eyeOffsetY - eyeHeight / 2);
        glVertex2f(eyeOffsetX, eyeOffsetY + eyeHeight / 2);
        glEnd();
    }

    // 왼쪽 눈
    glBegin(GL_LINES);
    glVertex2f(-eyeOffsetX, eyeOffsetY - eyeHeight / 2);
    glVertex2f(-eyeOffsetX, eyeOffsetY + eyeHeight / 2);
    glEnd();

    // 웃는 입 (반원 아크)          ////[단무지 반원]
    float mouthYOffset = -0.03f;
    //float startX, startY, endX, endY;
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= 100; ++i) {
        float a = (180.0f + 180.0f * i / 100.0f) * (PI / 180.0f);
        glVertex2f(cosf(a) * mouthRadius, sinf(a) * mouthRadius + mouthYOffset); //
        //float x = cosf(a) * mouthRadius;
        //float y = sinf(a) * mouthRadius + mouthYOffset;

        //if (i == 0) {
            //startX = x; startY = y;  // 시작점 저장
        //}
        //if (i == 100) {
            //endX = x; endY = y;      // 끝점 저장
        //}

        //glVertex2f(x, y);
    }

    //glVertex2f(startX, startY);
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

    // 메인 렌더링 루프
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

        // 화면 클리어
        glClear(GL_COLOR_BUFFER_BIT);
        
        SHORT wKeyState = GetAsyncKeyState('W');
        int wKeyNow = (wKeyState & 0x8000) ? 1 : 0;

        if (wKeyNow && !wKeyPrev) {
            wink = 1 - wink;
        }
        wKeyPrev = wKeyNow;


        glPushMatrix();
        // 스마일 얼굴
        drawCircle(0.8, 360, 1.0f, 1.0f, 0.0f);
        drawFace(0.3, 0.2, 0.25, 0.5, 0.0f, 0.0f, 0.0f);
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