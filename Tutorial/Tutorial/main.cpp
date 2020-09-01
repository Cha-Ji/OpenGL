#include <GLUT/GLUT.h> //MacOS : Xcode에서 실행해 표현이 다릅니다.

void mydisplay(){
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);
    glVertex3f(0.0, 0.9, 0.0);     // 머리
    glVertex3f(-0.9, 0.5, 0.0);    // 왼팔
    glVertex3f(-0.3, -0.5, 0.0);   // 왼쪽 허리
    glVertex3f(-0.5, -1, 0.0);     // 왼발
    glVertex3f(0.0, -0.5, 0.0);
    glVertex3f(0.5, -1, 0.0);      // 오른발
    glVertex3f(0.3, -0.5, 0.0);    // 오른 허리
    glVertex3f(0.9, 0.5, 0.0);     // 오른팔
    
    glEnd();
    glFlush();
}

int main(int argc, char* argv[]){
    glutInit(&argc, argv);
    glutCreateWindow("Test");
    glutDisplayFunc(mydisplay);
    glutMainLoop();
    return 0;
}
