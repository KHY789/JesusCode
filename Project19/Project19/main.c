#pragma comment(lib, "Opengl32.lib") // Windows���� OpenGL ���̺귯�� ���
#include <GLFW/glfw3.h>// GLFW ���̺귯��

/* NuGet ��Ű�� �Ŵ������� GLFW ��ġ�� ���*/

#include <math.h> // sinf, cosf ���
#define PI 3.1415926535f // ������(PI) ��� ���


int main() {
    if (!glfwInit()) return -1;

    // 500x500 ũ���� â ����, ���� ����
    GLFWwindow* window = glfwCreateWindow(500, 500, "GLFW: Circle", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
        // â ���� ���� �� GLFW ���� �� ���α׷� ����
    }

    // ������ â�� OpenGL ���ؽ�Ʈ�� ���� �����忡 ���ε� ('window' â�� �׸� �׸���)
    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window)) {
        // ���� �÷� ���� ����� (������)
        glClear(GL_COLOR_BUFFER_BIT);

        // �� �׸���
        float radius = 0.4f; // ���� ������
        int segments = 100;

        // GL_TRIANGLE_FAN���� �׸��� (ù ������ �߽����� �ﰢ������ ����)
        glBegin(GL_TRIANGLE_FAN);
        glColor3f(1.0f, 0.0f, 0.0f); // �߽� �� (������)
        glVertex2f(0.0f, 0.0f); // �߽� ��ǥ (ȭ�� �߾�)

        // �� �ѷ��� ���� segments ����ŭ ������ ��� �� �߰�
        for (int i = 0; i <= segments; i++) {
            float angle = 2.0f * PI * i / segments;
            float x = radius * cosf(angle);
            float y = radius * sinf(angle);

            glColor3f(0.0f, 0.0f, 1.0f); // �ܰ� ���� (�Ķ���)
            glVertex2f(x, y); // �� �ѷ� ���� ��ǥ
        }
        glEnd();

        glfwSwapBuffers(window); // �� ���� --> ����Ʈ ���� (ȭ�鿡 ǥ��)
        glfwPollEvents(); // �̺�Ʈ ó��
    }

    // ���� ���� ����
    glfwDestroyWindow(window);
    // GLFW ���̺귯�� ����
    glfwTerminate();

    return 0;
}
