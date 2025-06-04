#pragma comment(lib, "Opengl32.lib")
#include <GLFW/glfw3.h>
#include <math.h>
#include <Windows.h>

#define PI 3.1415926535f

int direction = 0; // -1: ������, 0: ����, 1: ������

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

    // �ִϸ��̼� �Ķ���� - ���� �ݰ�
    const float earthOrbitR = 0.6f;   // ���� ���� �ݰ�
    const float moonOrbitR = 0.2f;   // �� ���� �ݰ�

    // �ִϸ��̼� ���� ���� - ����/���� ���� ���
    float earthOrbitAng = 0.0f;    // ���� ����
    float earthSelfAng = 0.0f;     // ���� ����
    float moonOrbitAng = 0.0f;     // �� ����
    float moonSelfAng = 0.0f;     // �� ����

    const float earthOrbitSpeed = 0.01f; // �� �����Ӹ��� 0.005���� �ø�
    const float earthSelfSpeed = 0.05f;
    const float moonOrbitSpeed = 0.05f;
    const float moonSelfSpeed = 0.1f;

    // ���� ������ ����
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

        // ȭ�� Ŭ����
        glClear(GL_COLOR_BUFFER_BIT);

        //  Ű �Է� ó��
        if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
            direction = 1;
        }
        else if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
            direction = -1;
        }
        else {
            direction = 0;
        }

        // ���� ����
        earthOrbitAng += direction * earthOrbitSpeed; // �� �����Ӹ��� ���� ����
        earthSelfAng += direction * earthSelfSpeed;
        moonOrbitAng += direction * moonOrbitSpeed;
        moonSelfAng += direction * moonSelfSpeed;

        glPushMatrix();
        // �¾� �׸���
        drawCircle(0.2, 100, 1.0f, 1.0f, 0.0f);
        glRotatef(earthOrbitAng, 0, 0, 1); // ����(�ݽð����) +
        glTranslatef(earthOrbitR, 0.0f, 0.0f);
        glRotatef(-earthSelfAng, 0, 0, 1); // ����(�ð����) -

        glPushMatrix();
        // ���� �׸���
        drawCircle(0.1, 100, 0.0f, 0.0f, 1.0f);
        glTranslatef(0.05, 0.0f, 0.0f);//@@@
        drawCircle(0.03, 100, 0.0f, 1.0f, 0.5f);//@@@
        glPopMatrix();

        glRotatef(moonOrbitAng, 0, 0, 1); // ����(�ݽð����)
        glTranslatef(moonOrbitR, 0.0f, 0.0f);
        glRotatef(-moonSelfAng, 0, 0, 1); // ����(�ð����)
        // �� �׸���
        drawCircle(0.05, 100, 0.5f, 0.5f, 0.5f);
        glTranslatef(0.02, 0.0f, 0.0f);//@@@
        drawCircle(0.02, 100, 0.0f, 0.0f, 0.0f);//@@@
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