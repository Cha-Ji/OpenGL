#define GL_SILENCE_DEPRECATION
#include <GLUT/GLUT.h>
#include <math.h>
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
int angle_upper=0;
int angle_low=0;

int dir_upper = 1;
int dir_low = 1;

GLfloat camx = 0.5, camy = 0.5, camz = 4;
GLfloat cam2x = 0, cam2y = 0, cam2z = 0;
GLfloat cam_upx = 0, cam_upy = 1, cam_upz = 0;

void drawBody();
void drawHead();
void drawUpperArm(GLfloat angle);
void drawLowerArm(GLfloat angle);
void drawCuboid(GLfloat sx, GLfloat sy, GLfloat sz);  //직육면체 반복 생략
void drawHand();
void mydisplay();
void reshape(int width, int height);
void Mytimer(int value);
void myKeyboard(unsigned char KeyPressed, int x, int y);

int main(int argc, char* argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("OpenGL Drawing Example");
    glutDisplayFunc(mydisplay);
    glutKeyboardFunc(myKeyboard);
    glutReshapeFunc(reshape);
    glutTimerFunc(20, Mytimer, 1);
    glutMainLoop();
    return 0;
}

void reshape(int width, int height){
    glViewport(50, 50, width - 50, height - 50);
    //glViewport(<#GLint x#>, <#GLint y#>, <#GLsizei width#>, <#GLsizei height#>)
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat ratio = (float)width / height;
    
    gluPerspective(30, ratio, 0.1, 10);
    }
void mydisplay(){

    glClear(GL_COLOR_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(camx, camy, camz,
              cam2x, cam2y, cam2z,
              cam_upx, cam_upy, cam_upz);// 시선 변화 (z축 보기)

    // 몸
    drawBody();
    drawHead();
    // 팔
    glPushMatrix();
    drawUpperArm(angle_upper);
    drawLowerArm(angle_low);
    drawHand();
    glPopMatrix();
    // 왼팔
    glPushMatrix();
    glRotatef(180, 0, 1, 0);
    drawUpperArm(angle_upper);
    drawLowerArm(angle_low);
    drawHand();
    glPopMatrix();
    glFlush();
}
void Mytimer(int value) {
   angle_upper += dir_upper;
   angle_low += 5*dir_low;
   if (angle_upper >= 80)
      dir_upper -= 1;
   else if (angle_upper <= -90)
      dir_upper =  1;

   if (angle_low >= 160)
      dir_low -= 1;
   else if (angle_low <= -90)
      dir_low = 1;

//    GLfloat theta = 0.1;
//    camx = camx * cos(theta) + camz*sin(theta);
//
    
   glutTimerFunc(20, Mytimer, 1);
   glutPostRedisplay();
}

void myKeyboard(unsigned char KeyPressed, int x, int y){
    switch (KeyPressed){
        case 'w':
            camy = -camx*sin(0.1) + camy*cos(0.1);
            break;
        case 'a':
            camz = -camx*sin(0.1) + camz*cos(0.1);
            break;
        case 's':
            camz = camz * cos(0.1) + camx*sin(0.1);
            break;
        case 'd':
            camx = camx * cos(0.1) + camz*sin(0.1);
            break;
    }
    glutPostRedisplay();
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

void drawHead(){
    glPushMatrix();
    glTranslatef(0, 0.7, 0);
    glScalef(1, 1, 1);
    glutWireCube(0.25);
    glPopMatrix();
}

