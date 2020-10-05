#include <GLUT/GLUT.h>

#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 500
int angle_upper=0;
int angle_low=0;
int dir_upper = 1;
int dir_low = 1;

void drawAxis();
void drawXAxis();
void drawBody();
void drawHead();
void drawUpperArm(GLfloat angle);
void drawLowerArm(GLfloat angle);
void drawCuboid(GLfloat sx, GLfloat sy, GLfloat sz);  //직육면체 반복 생략
void drawHand();
void drawFinger1();
void drawFinger2(GLfloat angle);
void mydisplay();
void reshape(int width, int height);
void Mytimer(int value);

int main(int argc, char* argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("OpenGL Drawing Example");
    glutDisplayFunc(mydisplay);
    glutReshapeFunc(reshape);
    glutTimerFunc(20, Mytimer, 1);
    glutMainLoop();
    return 0;
}
void reshape(int width, int height){
    glViewport(0, 0, width, height);
    GLfloat f_w = (GLfloat)width / (GLfloat)WINDOW_WIDTH;
    GLfloat f_h = (GLfloat)height / (GLfloat)WINDOW_HEIGHT;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-1.0 * f_w, 1.0 * f_w, -1.0 * f_h, 1.0 * f_h, -2, 2);
    gluLookAt(0.5, 0.5, 1, 0, 0, 0, 0, 1, 0);// 시선 변화 (z축 보기)
}
void mydisplay(){
    glClear(GL_COLOR_BUFFER_BIT);
    drawAxis();
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // 몸
    drawBody();
    drawHead();
    // 팔
    glPushMatrix();
        drawUpperArm(angle_upper);
        drawLowerArm(angle_low);
        drawHand();
        glPushMatrix();
            drawFinger1();
        glPopMatrix();
        glPushMatrix();
            drawFinger2(30);
    glPopMatrix();
    
    // 왼팔
    glPushMatrix();
        glRotatef(180, 0, 1, 0);
        drawUpperArm(angle_upper);
        drawLowerArm(angle_low);
        drawHand();
        glPushMatrix();
            drawFinger1();
        glPopMatrix();
        glPushMatrix();
            drawFinger2(30);
    glPopMatrix();
    
    glFlush();
}

void drawXAxis(){
    glBegin(GL_LINES);
        glVertex3f(0,0,0);
        glVertex3f(0.2,0,0);
        glVertex3f(0.2,0,0);
        glVertex3f(0.14,0.06,0);
        glVertex3f(0.2,0,0);
        glVertex3f(0.14,-0.06,0);
    glEnd();
    
    
}
void drawAxis(){
    glColor3f(1,1,1);
    // 축 초기화
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glPushMatrix();     //calling convention
        // 축 회전 : 돌린 축은 원상복귀를 해야한다.
        drawXAxis();
        glRotatef(90, 0, 0, 1);

        drawXAxis();
        glRotatef(-90, 0, 0, 1);
        // 각도 원상복구
    glPopMatrix();  // calling convention
    glPushMatrix();
        glRotatef(-90, 0, 1, 0);
        drawXAxis();
    glPopMatrix();
    glFlush();
}

void drawBody(){
    glPushMatrix();
    glScalef(2, 4, 1);
    glutWireCube(0.25);
    glPopMatrix();
    
}

void drawUpperArm(GLfloat angle){
    
        glTranslatef(0.25, 0.3, 0);
        glRotatef(angle, 0, 0, 1);
        glTranslatef(0.25, 0, 0);
    
    //회전한 상태를 유지 : lowerArm 을 그리기 위해
    drawCuboid(0.5,0.2,0.2);
}

void drawLowerArm(GLfloat angle){
    glTranslatef(0.25, 0, 0);
    glRotatef(angle, 0, 0, 1);
    glTranslatef(0.25, 0, 0);
    drawCuboid(0.5, 0.2, 0.2);
}

void drawCuboid(GLfloat sx, GLfloat sy, GLfloat sz){
    glPushMatrix();
        glScalef(sx, sy, sz);
        glutWireCube(1);
    glPopMatrix();
}

void drawHand(){
    glTranslatef(0.35, 0, 0);
    glutWireSphere(0.1, 15, 15);
}
void drawFinger1(){
    glTranslatef(0.15, 0, 0);
    drawCuboid(0.1, 0.05, 0.05);
}
void drawFinger2(GLfloat angle) {

   glRotatef(angle, 0, 0, 1);
   glTranslatef(0.15, 0, 0);
   drawCuboid(0.1, 0.05, 0.05);
}

void Mytimer(int value) {
   angle_upper += 5;
   angle_low += 5*dir_low;

    if(angle_upper == 300)
        angle_upper -= 20;

    if(angle_low >= 200 && angle_low < 400)
        dir_low = 0;
   else if (angle_low <= -90)
      dir_low = 1;

   glutTimerFunc(20, Mytimer, 1);
   glutPostRedisplay();
}

void drawHead(){
    glPushMatrix();
    glTranslatef(0, 0.7, 0);
    glScalef(1, 1, 1);
    glutWireCube(0.25);
    glPopMatrix();
    
}
