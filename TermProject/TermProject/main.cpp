#define GL_SILENCE_DEPRECATION
#include <GLUT/GLUT.h>
#include <math.h>
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
//int angle_upper=0;
//int angle_low=0;
int roll_angle=0;   bool rolling = true;    GLfloat roll_z = 0;

int dir_upper = 1;
int dir_low = 1;

GLfloat camx = 0.5, camy = 0.5, camz = 4;
GLfloat cam2x = 0, cam2y = 0, cam2z = 0;
GLfloat cam_upx = 0, cam_upy = 1, cam_upz = 0;

/*=====================콜백 함수===================*/
void mydisplay();
void reshape(int width, int height);
void Mytimer(int value);
void myKeyboard(unsigned char KeyPressed, int x, int y);
/*===============================================*/

/*===================그리기 함수====================*/
//완


//진행
void drawBeanBoy();   //주인공 강낭콩소년

//미완
void drawBag(GLfloat sx, GLfloat sy, GLfloat sz);       //주인공의 짐
void drawBird(GLfloat sx, GLfloat sy, GLfloat sz);      //지나가던 작은 새

/*===============================================*/

/*=================동작 함수=======================*/
//완

//진행
void rollBeanBoy();         //소년 구르기

//미완

void fallBeanBoy();         //굴러가다 구덩이에 빠진 소년
void cryBeanBoy();          //슬픔에 잠긴 소년
void goneTime();            //시간의 흐름(배경의 변화)
void flyingBird();          //날고있는 새
void helpingBird();         //소년을 도우려는 새
void askBird();             //새에게 도움을 요청하는 소년
void growBeanBoy();         //씩씩해져 성장하는 소년
void newBeanBaby();         //새로 태어나는 강낭콩 아기
void startLoop();           //모험을 떠나는 강낭콩 아기들..
/*===============================================*/
int main(int argc, char* argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("강낭콩 소년의 귀환");
    
    glutDisplayFunc(mydisplay);
    glutKeyboardFunc(myKeyboard);
    glutReshapeFunc(reshape);
    glutTimerFunc(20, Mytimer, 1);
    glutMainLoop();
    return 0;
}

//스토리 진행
void mydisplay(){
    
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    //강낭콩 소년의 복귀
    gluLookAt(camx, camy, camz,cam2x, cam2y, cam2z,cam_upx, cam_upy, cam_upz);// 시선 변화
    rollBeanBoy();
    
    
    
    
    
    
    
    glFlush();
}

void reshape(int width, int height){
    glViewport(50, 50, width - 50, height - 50);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat ratio = (float)width / height;
    
    gluPerspective(30, ratio, 0.1, 10);
}

void Mytimer(int value) {
    //   angle_upper += dir_upper;
    //   angle_low += 5*dir_low;
    //   if (angle_upper >= 80)
    //      dir_upper -= 1;
    //   else if (angle_upper <= -90)
    //      dir_upper =  1;
    //
    //   if (angle_low >= 160)
    //      dir_low -= 1;
    //   else if (angle_low <= -90)
    //      dir_low = 1;
    // 구르는 중
    if (rolling) {
        roll_angle += 10;
        roll_z += 0.01;
        
        if (roll_z >= 0.1) roll_z = -6;
    }
    glutTimerFunc(40, Mytimer, 1);
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

void drawBeanBoy(int roll_angle){
    glTranslatef(0, 0, roll_z);
    glPushMatrix();

        glRotatef(roll_angle, 1, 0, 0);
        //본체
        glColor3f(0.2, 1, 0);
        glutSolidSphere(0.4, 60, 10);
        glTranslatef(0, -0.1, 0);
        glutSolidSphere(0.42, 60, 10);
    
        //눈
        glColor3f(0, 0, 0);
        
        glTranslatef(0.1, 0.2, 0);
        glutSolidSphere(0.1, 60, 10);
        glTranslatef(-0.2, 0, 0);
        glutSolidSphere(0.1, 60, 10);
    glPopMatrix();
}

void rollBeanBoy(){
    rolling = true;
    drawBeanBoy(roll_angle);
    
    
    //rolling = false;
}
