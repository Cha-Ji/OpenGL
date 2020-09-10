#include <GLUT/GLUT.h>

# define WINDOW_WIDTH 600
# define WINDOW_HEIGHT 500
void mydisplay(){
    glClear(GL_COLOR_BUFFER_BIT);   // 컬러버퍼에 초기화 색을 가함
    glColor3f(0.5, 0.5, 0.5);       // 회색
    glBegin(GL_POLYGON);            // 사각형
        glVertex3f(-0.5, -0.5, 0.0);    //좌하단
        glVertex3f(0.5, -0.5, 0.0);     //우하단
        glVertex3f(0.5, 0.5, 0.0);      //우상단
        glVertex3f(-0.5, 0.5, 0.0);     //좌상단
    glEnd();
    glFlush();
}

void myReshape(int newWidth, int newHeight){
    glViewport(0, 0, newWidth, newHeight);
    GLfloat widthFactor = (GLfloat)newWidth / (GLfloat)300;
    GLfloat heightFactor = (GLfloat)newHeight / (GLfloat)300;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0 * widthFactor, 1.0 * widthFactor, -1.0 * heightFactor, 1.0 * heightFactor, -1.0, 1.0);
    
    
}
int main(int argc, char* argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(0, 0);   // 윈도우가 생성되는 포지션
    glutCreateWindow("OpenGL Example Drawing");
    glClearColor(1.0, 1.0, 1.0, 1.0);   //초기화 색은 백색
    glutDisplayFunc(mydisplay);
    glutReshapeFunc(myReshape);
    glutMainLoop();
    return 0;
}
