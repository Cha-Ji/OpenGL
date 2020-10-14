#define GL_SILENCE_DEPRECATION
#include <GLUT/GLUT.h>
#include <math.h>
#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800


//어떤 상태인지
bool rolling = true, is_hole = false, in_hole = false;
bool crying = false, root = false;

int roll_angle = 0, vaccum = 10, vac_count = 0, cry_count = 0;

GLfloat roll_z = -4, cry_y = 0, root_scale = 0; //translatef를 위한 변수
GLfloat back_color = 0, back_temp = -1, back_speed = 10;
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
void drawBeanBoy();   //주인공 강낭콩소년
    void drawBeanBody();
    void drawBeanFace();

//진행

void drawLand();      //집으로 가는 길    //땅, 구덩이 색깔 미완
void drawRoot();
//미완

void drawBag();       //주인공의 짐
void drawBird();      //지나가던 작은 새

/*===============================================*/

/*=================동작 함수=======================*/
//완
void rollBeanBoy();         //소년 구르기
void fallBeanBoy();         //굴러가다 구덩이에 빠진 소년
//진행

void cryBeanBoy();          //슬픔에 잠긴 소년
void rootBeanBoy();         //뿌리내리는 소년
void goneTime();            //시간의 흐름(배경의 변화)

//미완

void growBeanBoy();         //씩씩해져 성장하는 소년
void flyingBird();          //날고있는 새
void helpingBird();         //소년을 도우려는 새
void askBird();             //새에게 도움을 요청하는 소년

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
    goneTime();
    drawLand();         //아랫배경
    if (rolling)rollBeanBoy();      //구르며 집에가는 소년
    if (in_hole)fallBeanBoy();      //구덩이에 끼어버리는데
    
    
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
        if(camy > 0) camy -=0.2;                    //당황한 모습 : 카메라 각도 변경
        else if(vac_count < 40){                    //각도 변경 후 허우적
            roll_angle += vaccum;
            if(vac_count % 4 == 0)vaccum = -vaccum;
            vac_count += 1;
        }
        //울기 시작
        else if(vac_count == 40){
            vac_count = 41;
            crying = true;
        }
        //눈물 연출
        else if(crying){
            cry_y -= 0.02;
            cryBeanBoy();
            if(cry_y < -1) {
                crying = false;
                root = true;
            }
        }
        else if(root){
            if(root_scale < 4)root_scale += 0.1;
        }
    }
    // * 시간의 흐름
    if(back_color >= 100 || back_color <= 0)
        back_temp = -back_temp;
    back_color = (back_color + back_temp/back_speed);
    
    if(in_hole)back_speed = 100;
    if(root)back_speed = 0.1;
    
    
    
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
}
void drawBeanBody(){
    glColor3f(0.7, 1, 0.3);
    glutSolidSphere(0.4, 60, 10);
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
    glTranslatef(0.15, -0.1, 0);
    
    glPushMatrix();
        glScalef(2, 1, 0);
        glColor3f(0, 0, 0);
        glutSolidCube(0.04);
        glColor3f(1, 0.3, 0.3);
        glutSolidCube(0.03);
    glPopMatrix();
}
void fallBeanBoy(){
    glPushMatrix();
        glTranslatef(0, 0, 0.5);
        glRotatef(roll_angle, 1, 1, 0);
        drawBeanBoy();
        if(crying)
            cryBeanBoy();
    glPopMatrix();
}
void drawLand(){
    glPushMatrix();
    glTranslatef(0, -4, 0.5);
    glColor3f(0.4, 0.2, 0.1);     //땅 색깔
    
    //땅
    glutSolidCube(8);
    
    //구덩이
    if(is_hole){
        glColor3f(0.3, 0.15, 0.05); //구덩이 색깔
        glTranslatef(0, 3.8, 0);
        glutSolidSphere(0.4, 60, 10);
        if(root)rootBeanBoy();
    }
    glPopMatrix();
}
void cryBeanBoy(){
    GLfloat start = 0;
    while(start < 5){
        if(start/10 + cry_y < 0 && start/10 + cry_y > -0.5){
            glPushMatrix();
            glColor3f(0, 0.2, 1);       //눈물색깔
            glTranslatef(0.35, start/10 + cry_y, 0.2);
            
            //왼쪽 눈물
            glPushMatrix();
            glutSolidSphere(0.01, 60, 10);
            glPopMatrix();
            
            //오른쪽 눈물
            glTranslatef(-0.3, 0,0);
            glutSolidSphere(0.01, 60, 10);
            glPopMatrix();
        }
        start ++;
    }
}
void goneTime(){
    glClearColor(back_color/100, back_color/100, back_color/100, 0);
    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslatef(3, 2, -3);
    glRotatef(roll_angle, 0, 0, 1);
    glutSolidSphere(0.2, 60, 10);
    glPopMatrix();
    
}

void rootBeanBoy(){
    for(int i=0; i<4; i++){
        glPushMatrix();
        glColor3f(0.8, 0.6, 0.1);         //뿌리색깔
        glTranslatef(0, -0.25, 0.1);
        glPushMatrix();
            glScalef(0.5, root_scale + 20, 0.5);
            glutSolidCube(0.05);
        glPopMatrix();
        glTranslatef(0, -0.1*i, 0);
        drawRoot();
        glPopMatrix();
    }
}

void drawRoot(){
    glPushMatrix();
    glTranslatef(-0.06, -0.15, 0);
    for(int i=0; i<4;i++){
        glTranslatef(0.03, 0, 0);
        glPushMatrix();
        glTranslatef(0, -0.05, 0);
        glRotatef(-60 + 60*i, 0, 1, 1);
        glScalef(0.5, root_scale + 6, 0.5);
        glutSolidCube(0.02);
        glPopMatrix();
    }
    glPopMatrix();
}
