#define GL_SILENCE_DEPRECATION
#include <GLUT/GLUT.h>
#include <math.h>
#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800

//어떤 상태인지
bool rolling = true, is_hole = false, in_hole = false;
bool crying = false, root = true, growing = false;
bool appear_bird = false;

//물체의 움직임을 위한 변수 (회전, 횟수 카운팅)
int roll_angle = 0, sun_angle = 0, vaccum = 10, vac_count = 0, cry_count = 0;
int wing_angle = -30;
//길이, 좌표 조정을 위한 변수
GLfloat roll_z = -4, cry_y = 0;
GLfloat root_scale = -10, bud_scale = -5, grow_scale = -5;
GLfloat wing_scale = 0, wing_temp = -1;
GLfloat back_color = 0, back_temp = -1, back_speed = 1;
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
void drawBeanBoy();   //주인공 완두콩소년
    void drawBeanBody();
    void drawBeanFace();

//진행
void drawLand();      //집으로 가는 길    //땅, 구덩이 색깔 미완
void drawRoot(GLfloat floor);
void drawBird();      //지나가던 작은 새
//미완

void drawBag();       //주인공의 짐


/*===============================================*/

/*=================동작 함수=======================*/
//완
void rollBeanBoy();         //소년 구르기
void fallBeanBoy();         //굴러가다 구덩이에 빠진 소년
//진행
void cryBeanBoy();          //슬픔에 잠긴 소년
void rootBeanBoy();         //뿌리내리는 소년
void flyingBird();          //날고있는 새
void growBeanBoy();         //씩씩해져 성장하는 소년

void goneTime();            //시간의 흐름(배경의 변화)
//미완


void helpingBird();         //소년을 도우려는 새
void askBird();             //새에게 도움을 요청하는 소년

void newBeanBaby();         //새로 태어나는 완두콩 아기
void startLoop();           //모험을 떠나는 아기들..
/*===============================================*/
int main(int argc, char* argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("완두콩 소년의 귀환");
    
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
    if (appear_bird)flyingBird();   //등장하는 새!
    if (growing)growBeanBoy();      //씩씩해진 소년은 새싹이 튼다
    
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
        if(camy > 0 && !growing) camy -=0.2;                    //당황한 모습 : 카메라 각도 변경
        else if(vac_count < 40){                    //허우적 거리는 모습 : 일정한 각도 진동
            if(vac_count % 4 == 0)vaccum = -vaccum;
            roll_angle += vaccum;
            vac_count += 1;
        }
        else
            crying = true;                        //그만 허우적대고 울기 시작
    }
    // 3. 눈물
    if (crying){
        if(cry_y >= -1){
            cry_y -= 0.02;
            cryBeanBoy();
        }
        else{
            cry_y = 0;  //눈물의 출발점을 눈으로 초기화 (여러번 우는 것을 표현하기 위함)
            crying = false; root = true;
        }
    }
    // 4. 뿌리 내리기
    if(root){
        crying = true;
            
        if(root_scale < 5)root_scale += 0.2;
        else appear_bird = true;
    }
    // 5. 새와의 만남
    if(appear_bird){
        if(wing_scale >= 0.03)wing_temp = 1;
        else if(wing_scale <= -0.03)wing_temp = -1;
        wing_angle += 9*wing_temp;
        wing_scale -= 0.015 * wing_temp;

        //growing = true;
    }
    // 6. 새싹트기, 나무로 자라기
    if(growing){
        crying = false;
        if(bud_scale <= 2)bud_scale += 0.2;
        else if(camy < 5){
                camy = camy * cos(0.1) - camx*sin(0.1); //카메라 줌을 멀리한다.
        }
        
        if(camy <= 3 & camy >= 1){      //줌을 멀리하는 도중에 자라기 시작한다.
            grow_scale += 0.5;
        }
    }
    // 7.
    
    
    
    
    // * 시간의 흐름
    if(back_color >= 0.6 || back_color <= 0) back_temp = -back_temp;  //낮밤 변화
    back_color = (back_color + 0.0001 * back_speed * back_temp);
    
    
    if(growing && bud_scale >= 2)back_speed = 100;
    else back_speed = 1;
    sun_angle += back_speed;
    
    
    glutTimerFunc(40, Mytimer, 1);
    glutPostRedisplay();
}
void myKeyboard(unsigned char KeyPressed, int x, int y){
    switch (KeyPressed){
        case 'w':
//            camy += 1;
            camy = -camx*sin(0.1) + camy*cos(0.1);
            break;
        case 'a':
            camx -= 1;
//            camz = -camx*sin(0.1) + camz*cos(0.1);
            break;
        case 's':
//            camy -= 1;
            camy = camy * cos(0.1) + camx*sin(0.1);
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
    // 구를 때 은면 제거
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
        glutSolidCube(0.04);
        glColor3f(1, 0.3, 0.3);
        glutSolidCube(0.03);
    glPopMatrix();
}
void fallBeanBoy(){
    glPushMatrix();
        glTranslatef(0.1, 0, 0.5);
        glRotatef(roll_angle, 1, 1, 0); //허우적
        drawBeanBoy();
        if(crying)cryBeanBoy();
    glPopMatrix();
}
void drawLand(){
    glPushMatrix();
        glTranslatef(0, -4, 0.5);
        glColor3f(0.4, 0.2, 0.1);
        
        //땅
        glutSolidCube(8);
        
        //구덩이
        if(is_hole){
            glColor3f(0.3, 0.15, 0.05);
            glTranslatef(0, 3.8, 0);
            glutSolidSphere(0.4, 60, 10);
            if(root)rootBeanBoy();
        }
    glPopMatrix();
}
void cryBeanBoy(){
    for(GLfloat start = 0; start<5; start++){
        if(start/10 + cry_y < 0 && start/10 + cry_y > -0.5){
            glPushMatrix();
            glColor3f(0, 0.2, 1);       //눈물색깔
            glTranslatef(0.3, start/10 + cry_y, 0.2);
            
            //왼쪽 눈물
            glPushMatrix();
            glutSolidSphere(0.01, 60, 10);
            glPopMatrix();
            
            //오른쪽 눈물
            glTranslatef(-0.35, 0,0);
            glutSolidSphere(0.01, 60, 10);
            glPopMatrix();
        }
    }
}
void drawBird(){
    //새 그리기
    glPushMatrix();
        glColor3f(0, 0, 0);
        glTranslatef(0, 0, 0);
    
    //새 꼬리!
    glPushMatrix();
        glTranslatef(-0.5, -0.1, 0);
        glScalef(10, 1, 1);
        glutSolidCube(0.05);
        glTranslatef(0, -0.03, 0);
        glutSolidCube(0.03);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-0.1, -0.7, 0);
        glScalef(1, 5, 1);
        glutSolidCube(0.05);
    glPopMatrix();
    
    
    
    //새 몸!
    glColor3f(1, 1, 1);
    glutSolidSphere(0.35, 60, 10);
    glTranslatef(-0.1, -0.2, -0.05);
    glutSolidSphere(0.45, 60, 10);
    
    //새 얼굴!
    glPushMatrix();
        glColor3f(0, 0, 0);     //얼굴 색깔
    
    //눈
        glTranslatef(0.35, 0.3, 0.2);
        glutSolidSphere(0.025, 60, 10);
    
        glTranslatef(-0.2, 0, 0);
        glutSolidSphere(0.025, 60, 10);
    
    //입
        glTranslatef(0.12, -0.05, 0);
        glScalef(1, 0.5, 0);
        glutSolidCone(0.04, 0.04, 10, 10);
    glPopMatrix();
    
    //날개
    glPushMatrix();
        glTranslatef(-0.3, 0.2, 0);
            glTranslatef(0, wing_scale, 0);
            glRotatef(wing_angle, 0, 1, 1);
        glScalef(5, 1, 1);
        glutSolidCube(0.06);
        glTranslatef(0, -0.03, 0);
        glutSolidCube(0.05);
        glTranslatef(0, -0.03, 0);
        glutSolidCube(0.04);
    glPopMatrix();
    
    glPopMatrix();
    
    
}
void flyingBird(){
    drawBird();
}
void goneTime(){
    //낮(0.6,0.8,1) ~ 밤(0.1,0.3,0.5)
    glClearColor(0.6 - back_color, 0.8 - back_color, 1 - back_color, 0);
    
    //해
    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslatef(-1, 0, -2);
    glRotatef(sun_angle/10.0, 1, 0, 1);
    glTranslatef(0, 0, 4);
    glutSolidSphere(0.2, 60, 10);
    glPopMatrix();
    
}
void rootBeanBoy(){
    glColor3f(0.8, 0.6, 0.1);         //뿌리색깔
    glTranslatef(0, -0.25, 0.1);
    
    //큰뿌리
    glPushMatrix();
        glScalef(0.5, root_scale + 20, 0.5);
        glutSolidCube(0.05);
    glPopMatrix();
    
    //1차 잔뿌리
    if(root_scale >= 0)
        for(GLfloat i=0; i<6; i++){
            drawRoot(i);
            
        }
}
void drawRoot(GLfloat floor){
    for(GLfloat sign = -1; sign< 2; sign+=2){    //i는 부호
        glPushMatrix();
            glTranslatef(sign*(0.2 - floor/50), -0.1 -floor/10, 0);
        //잔잔 뿌리
        for(GLfloat j =0;j< 4;j++){
            glPushMatrix();
                glTranslatef(sign*(j/20 - floor/50), -0.05 + floor/30 - j/15, 0);
                glRotatef(sign*30, 0, 1, 1);
                glScalef(0.5, root_scale + 10 - floor*2, 0.5);
                glutSolidCube(0.01);
            glPopMatrix();
        }
        //잔 뿌리
            glRotatef(sign*60, 0, 1, 1);
            glScalef(0.5, root_scale + 30 - floor*4, 0.5);
            glutSolidCube(0.02);
        glPopMatrix();
    }
}
void growBeanBoy(){
    glPushMatrix();
        glColor3f(0, 1, 0);
        glTranslatef(0.3, 0.2, -0.2);
    
        // 새싹 줄기
    if(bud_scale > -2){
        glPushMatrix();
            glScalef(1, 2 + bud_scale, 1);
            glutSolidCube(0.05);
        glPopMatrix();
    }
        //새싹 잎
    if(bud_scale > 1)
        for(int sign=-1; sign<2; sign+=2){
            glPushMatrix();
                glTranslatef(-sign*0.03, 0.15, 0);
                glRotatef(sign*60, 0, 1, 1);
                glScalef(0.5, bud_scale, 1);
                glutSolidCube(0.05);
            glPopMatrix();
        }
    
        //나무 기둥
    glTranslatef(0, -0.2, 0);
    if(grow_scale > -2){
        glPushMatrix();
            glColor3f(1, 1, 0.5);       //나무색깔
            glScalef(1, 2 + grow_scale*2, 1);
            glutSolidCube(0.1);
        glPopMatrix();
    }
    
    
    glPopMatrix();
}
