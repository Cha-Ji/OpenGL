#include <GLUT/GLUT.h>
#include <iostream>

#define _WINDOW_HEIGHT   300
#define _WINDOW_WIDTH   300

GLfloat r = 1.0, g = 1.0, b = 1.0;
GLint cur_x = -1, cur_y = -1;
int mode_visual = 1;
int mode = 0;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    if (mode_visual == 1) {
        if (mode == 0)
            glutWireSphere(0.3, 15, 15);
        else if (mode == 1)
            glutWireTeapot(0.3);
    }
    glFlush();
}

void mouseBtn(int btn, int states, int x, int y) {
    if (btn == GLUT_LEFT_BUTTON && states == GLUT_UP) {
        mode = (mode + 1) % 2;
        glutPostRedisplay();
    }
}

void mouseDrag(int x, int y) {
    GLint dx, dy;
    if (cur_x >= 0 || cur_y >= 0) {
        dx = abs(x - cur_x);
        dy = abs(y - cur_y);

        g = (g - 0.1) < 0 ? 0 : g - 0.1;
        b = (b - 0.1) < 0 ? 0 : b - 0.1;
        glColor3f(r, g, b);

        glutPostRedisplay();
    }

    cur_x = x;
    cur_y = y;
}

void winEntry(int state) {
    if (state == GLUT_LEFT)
        mode_visual = 0;
    else
        mode_visual = 1;
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutCreateWindow("title");
    glutInitWindowSize(_WINDOW_WIDTH, _WINDOW_HEIGHT);
    glutDisplayFunc(display);
    glutMouseFunc(mouseBtn);
    glutMotionFunc(mouseDrag);
    glutEntryFunc(winEntry);

    glutMainLoop();
    return 0;
}
