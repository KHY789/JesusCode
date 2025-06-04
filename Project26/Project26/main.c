#pragma comment(lib, "Opengl32.lib")
#include <GLFW/glfw3.h>
#include <math.h>
#include <Windows.h>

#define PI 3.1415926535f

int wink = 0;
int wKeyPrev = 0;

// �ﰢ������ �� �׸���(segments 360 = Circle)
void drawCircle(float radius, int segments, float r, float g, float b) {
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(r, g, b);
    glVertex2f(0, 0);
    for (int i = 0; i < segments; i++) {
        float angle1 = 2.0f * PI * i / segments; // ���� 360�� �Ǵ� 2�� ����,  �� ���� ���� =  2�� * i / segments
        float angle2 = 2.0f * PI * (i + 1) / segments;
        float x1 = radius * cosf(angle1);
        float y1 = radius * sinf(angle1);
        float x2 = radius * cosf(angle2);
        float y2 = radius * sinf(angle2);
        // �߽����� �ܰ� �� ������ �ﰢ�� ����
        glVertex2f(x1, y1);           // ���� ��
        glVertex2f(x2, y2);           // ���� ��
    }
    glEnd();
}

// ������ ������ �� + �� �׸���
void drawFace(float eyeHeight, float eyeOffsetX, float eyeOffsetY, float mouthRadius, float r, float g, float b) {
    glColor3f(r, g, b);
    glLineWidth(8.0f); // �� �β�

    glBegin(GL_LINE_STRIP);
    // ������ ��
    if (wink == 1) {
        // '>'
        glBegin(GL_LINES);
        glVertex2f(eyeOffsetX + eyeHeight / 2, eyeOffsetY + eyeHeight / 2); // '<'�� X��ǥ���� - eyeHeight ���ֱ�( + eyeHeight��)
        glVertex2f(eyeOffsetX, eyeOffsetY);                                 // '<'�� ���ʿ� ��ġ�Ϸ��� ��� X��ǥ�� -���̱�( eyeOffsetX��)

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

    // ���� ��
    glBegin(GL_LINES);
    glVertex2f(-eyeOffsetX, eyeOffsetY - eyeHeight / 2);
    glVertex2f(-eyeOffsetX, eyeOffsetY + eyeHeight / 2);
    glEnd();

    // ���� �� (�ݿ� ��ũ)          ////[�ܹ��� �ݿ�]
    float mouthYOffset = -0.03f;
    //float startX, startY, endX, endY;
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= 100; ++i) {
        float a = (180.0f + 180.0f * i / 100.0f) * (PI / 180.0f);
        glVertex2f(cosf(a) * mouthRadius, sinf(a) * mouthRadius + mouthYOffset); //
        //float x = cosf(a) * mouthRadius;
        //float y = sinf(a) * mouthRadius + mouthYOffset;

        //if (i == 0) {
            //startX = x; startY = y;  // ������ ����
        //}
        //if (i == 100) {
            //endX = x; endY = y;      // ���� ����
        //}

        //glVertex2f(x, y);
    }

    //glVertex2f(startX, startY);
    glEnd();
}

// â ũ�� ����
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // ����Ʈ ����: â ��ü ũ�⿡ �°� ����
    glViewport(0, 0, width, height);

    // ���� ��� ����: ��Ⱦ�� ����
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // ��Ⱦ�� ���
    float aspect_ratio = (float)width / (float)height;

    // â�� ��Ⱦ�� ���� ���� ���� ���� ����
    if (width > height) {
        // �ʺ� ���̺��� ū ���: �¿� ���� Ȯ��
        glOrtho(-aspect_ratio, aspect_ratio, -1.0, 1.0, -1.0, 1.0);
    }
    else {
        // ���̰� �ʺ񺸴� ũ�ų� ���� ���: ���� ���� Ȯ��
        glOrtho(-1.0, 1.0, -1.0 / aspect_ratio, 1.0 / aspect_ratio, -1.0, 1.0);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main() {
    // GLFW ���̺귯�� �ʱ�ȭ
    if (!glfwInit()) return -1;
    // â ����
    GLFWwindow* window = glfwCreateWindow(800, 600, "Circle", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // ȭ�� ���� 1:1
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    framebuffer_size_callback(window, 800, 600);

    // ���� ������ ����
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

        // ȭ�� Ŭ����
        glClear(GL_COLOR_BUFFER_BIT);
        
        SHORT wKeyState = GetAsyncKeyState('W');
        int wKeyNow = (wKeyState & 0x8000) ? 1 : 0;

        if (wKeyNow && !wKeyPrev) {
            wink = 1 - wink;
        }
        wKeyPrev = wKeyNow;


        glPushMatrix();
        // ������ ��
        drawCircle(0.8, 360, 1.0f, 1.0f, 0.0f);
        drawFace(0.3, 0.2, 0.25, 0.5, 0.0f, 0.0f, 0.0f);
        glPopMatrix();

        // ���� ���� �� �̺�Ʈ ó��
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    // ������ ���� ����
    glfwDestroyWindow(window);

    glfwTerminate();
    return 0;
}