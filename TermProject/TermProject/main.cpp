#define GL_SILENCE_DEPRECATION
#include <GLUT/GLUT.h>
#include <math.h>
#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 1200

int roll_angle = 0;   bool rolling = true;    GLfloat roll_z = -4;  //1. 구르는 각, 구르는가, 구르는 거리
bool is_hole = false, in_hole = false;                              //2. 구덩이가 있는가, 구덩이에 빠졌는가

GLfloat camx = -1, camy = 4, camz = 5;
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
    void drawBeanBody();
    void drawBeanFace();
void drawLand();      //집으로 가는 길
//미완

void drawBag();       //주인공의 짐
void drawBird();      //지나가던 작은 새

/*===============================================*/

/*=================동작 함수=======================*/
//완

//진행
void rollBeanBoy();         //소년 구르기
void fallBeanBoy();         //굴러가다 구덩이에 빠진 소년
//미완


void cryBeanBoy();          //슬픔에 잠긴 소년1
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
    glutTimerFunc(40, Mytimer, 1);
    glutMainLoop();
    return 0;
}

//스토리 진행
void mydisplay(){
    
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(camx, camy, camz,cam2x, cam2y, cam2z,cam_upx, cam_upy, cam_upz);// 시선 변화
    
    //강낭콩 소년의 복귀
    drawLand();         //아랫배경
    rollBeanBoy();      //구르며 집에가는 소년
    fallBeanBoy();      //구덩이에 끼어버리는데
    
    
    
    
    
    
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
    // 1. 구르는 중
    if (rolling) {
        roll_angle = (roll_angle + 10) % 360;
        roll_z += 0.2;
        
        // 장면전환 연출
        if (roll_z >= 3){
            roll_z = -7;
            is_hole = true;
        }
        
        // 구덩이 등장!
        if (is_hole && roll_z >= 0.4){
            rolling = false;
            in_hole = true;
        }
    }
    
    // 2. 구덩이에서 허우적!
    if (in_hole){
        if(camy > 0) camy -=0.2;
        
    }
    
    
    glutTimerFunc(40, Mytimer, 1);
    glutPostRedisplay();
}

void myKeyboard(unsigned char KeyPressed, int x, int y){
    switch (KeyPressed){
        case 'w':
            camy += 1;
//            camy = -camx*sin(0.1) + camy*cos(0.1);
            break;
        case 'a':
            camx -= 1;
//            camz = -camx*sin(0.1) + camz*cos(0.1);
            break;
        case 's':
            camy -= 1;
//            camz = camz * cos(0.1) + camx*sin(0.1);
            break;
        case 'd':
            camx += 1;
//            camx = camx * cos(0.1) + camz*sin(0.1);
            break;
    }
    glutPostRedisplay();
}

void drawBeanBoy(){
    glPushMatrix();
    glTranslatef(0, 0, 0.2);
        if(roll_angle < 100 || roll_angle > 260){
            drawBeanBody();
            drawBeanFace();
        }else{
            drawBeanFace();
            drawBeanBody();
        }
    glPopMatrix();
}

void rollBeanBoy(){
    glPushMatrix();
        glTranslatef(0, 0, roll_z);
        glRotatef(roll_angle, 0.5, 0, 0);
        drawBeanBoy();
    glPopMatrix();
    
    //rolling = false;
}

void drawBeanBody(){
    glColor3f(0.2, 1, 0);
    glutSolidSphere(0.4, 60, 10);
//    glScalef(1, 1.1, 1.1);
    glTranslatef(-0.05, -0.1, -0.05);
    glutSolidSphere(0.45, 60, 10);
}

void drawBeanFace(){
    glColor3f(0, 0, 0);     //얼굴 색깔
    
    //눈
    glTranslatef(0.35, 0.1, 0.2);
    glutSolidSphere(0.03, 60, 10);
    glTranslatef(-0.3, 0, 0);
    glutSolidSphere(0.03, 60, 10);
    
    //입
    
    glTranslatef(0.2, -0.2, 0);
    glPushMatrix();
    glScalef(2, 1, 0);
    glutSolidCube(0.05);
    glPopMatrix();
}

void fallBeanBoy(){

    
    
}
void drawLand(){
    glPushMatrix();
    glTranslatef(0, -4, 0.5);
    glColor3f(1, 1, 1);     //땅 색깔
    
    //땅
    glutSolidCube(8);
    
    //구덩이
    if(is_hole){
        glColor3f(0, 0, 0);
        glTranslatef(0, 3.8, 0);
        glutSolidSphere(0.4, 60, 10);
    }
    glPopMatrix();
    
}


