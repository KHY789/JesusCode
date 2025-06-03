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

// �� �׸���
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
        else{
            current_r = radius * inner_r;
        }
        glVertex2f(current_r * cos(angle), current_r * sin(angle));
    }
    glEnd();
}

// �����ϸ� ��(�� + ��) �׸���
void drawFace(float eyeR, float eyeOffsetX, float eyeOffsetY, float mouthRadius) {
    // ���� ��
    glPushMatrix();
    glTranslatef(-eyeOffsetX, eyeOffsetY, 0.0f);
    drawCircle(eyeR, 16, 0.0f, 0.0f, 0.0f);
    glPopMatrix();

    // ������ ��
    glPushMatrix();
    glTranslatef(eyeOffsetX, eyeOffsetY, 0.0f);
    drawCircle(eyeR, 16, 0.0f, 0.0f, 0.0f);
    glPopMatrix();

    glLineWidth(5.0f); // �� �β�
    glBegin(GL_LINE_STRIP);
    // ���� �� (�ݿ� ��ũ)
    float mouthYOffset = -0.03f;
    for (int i = 0; i <= 100; ++i) {
        float a = (180.0f + 180.0f * i / 100.0f) * (PI / 180.0f);
        glVertex2f(cosf(a) * mouthRadius, sinf(a) * mouthRadius + mouthYOffset);
    }
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
    GLFWwindow* window = glfwCreateWindow(1000, 935, "Circle", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // ȭ�� ���� 1:1
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    framebuffer_size_callback(window, 1000, 935);

    // �ִϸ��̼� �Ķ����
    const float smileOrbitR = 0.5f;   // �����ϸ� ���� �ݰ�
    const float starOrbitR = 0.35f;     // ������ ���� �ݰ�

    // ���� ������ ����
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

        // ȭ�� Ŭ����
        glClear(GL_COLOR_BUFFER_BIT);

        // ����/���� ���� ���
        float t = (float)glfwGetTime();
        float smileOrbitAng = t * 60.0f;    // �����ϸ� ���� �ӵ�
        float smileSelfAng = t * 100.0f;     // �����ϸ� ���� �ӵ�
        float starOrbitAng = t * 200.0f;     // �� ���� �ӵ�

        drawRectangle(0.02, 0.02, 1.0f, 0.0f, 0.0f);

        glPushMatrix();
        glRotatef(-smileOrbitAng, 0, 0, 1);
        glTranslatef(smileOrbitR, 0.0f, 0.0f); // ����
        glRotatef(smileSelfAng, 0, 0, 1); // ����
        // ������ �� �׸���
        drawCircle(0.2, 100, 1.0f, 1.0f, 0.0f);

        glPushMatrix();
        glRotatef(smileOrbitAng, 0, 0, 1);
        // ������ ��, �� �׸���
        drawFace(0.02, 0.07, 0.05, 0.06);

        glPopMatrix();

        // �� �׸���
        glPushMatrix();
        glRotatef(-starOrbitAng, 0, 0, 1);
        glTranslatef(starOrbitR, 0.0f, 0.0f); // ����
        drawStar(0.1, 10, 1.0f, 1.0f, 1.0f);

        glPopMatrix();
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