#include <GLUT/GLUT.h>

GLfloat Delta = 0.0;

void mydisplay(){
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.5, 0.8);
    glVertex3f(-1.0 + Delta, -0.5, 0.0);
    glVertex3f(0.0 + Delta, -0.5, 0.0);
    glVertex3f(0.0 + Delta, 0.5, 0.0);
    glVertex3f(-1.0 + Delta, 0.5, 0.0);
    glEnd();
    glutSwapBuffers();
}

void myTimer(int value){
    Delta = Delta +  0.001;
    glutPostRedisplay();
    glutTimerFunc(20, myTimer, value);
}

int main(int argc, char* argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(300, 300);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("OpenGL Drawing Example");
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, 1.0, -1.0);
    glutDisplayFunc(mydisplay);
    glutTimerFunc(20, myTimer, 1);
    glutMainLoop();
    return 0;
}

