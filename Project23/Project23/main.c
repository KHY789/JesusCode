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
        float angle = PI / 2 + i * (2.0f * PI / 3.0f);  // 90������ ����
        float x = radius * cosf(angle);
        float y = radius * sinf(angle);
        glVertex2f(x, y);
    }

    glEnd();
}

// ������(��) �׸���
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

    // ���� ������ ����
    while (!glfwWindowShouldClose(window)) {
        // ȭ�� Ŭ����
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        drawCircle(0.2, 100, 1.0f, 1.0f, 1.0f);

        glPushMatrix();
        glTranslatef(0.6f, -0.6f, 0.0f);
        drawRectangle(0.5, 0.5, 1.0f, 0.0f, 0.0f);
        glPopMatrix();

        // �� �׸���
        glPushMatrix();
        glTranslatef(-0.6f, 0.6f, 0.0f);
        drawStar(0.1, 10, 1.0f, 1.0f, 0.0f);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0.6f, -0.2f, 0.0f);
        drawTriangle(0.5, 0.0f, 0.0f, 1.0f);
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