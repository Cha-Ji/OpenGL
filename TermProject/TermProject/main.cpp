#define GL_SILENCE_DEPRECATION
#include <GLUT/GLUT.h> //=> Mac OS
//#include <GL/glut.h>
//#include <GL/gl.h>
//#include <GL/glu.h>

#include <math.h>
#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800

//어떤 상태인지
bool rolling = true, is_hole = false, in_hole = false;
bool crying = false, root = false, growing = false;
bool baby = false;
bool appear_bird = false, meet_bird = false;
bool reminding = false, help_bird = false;
bool speed_up = false, fail_bird = false;

//물체의 움직임을 위한 변수 (회전, 횟수 카운팅)
int roll_angle = 0, sun_angle = 180, vaccum = 10;
int vac_count = 0, cry_count = 0;
int wing_angle = -30, zoom_out_count = 0, confused_count = 0;
int help_count = 0, bird_zoom_count = 0;
int surprise_count = 0, remind_count = 0, brave_count = 0;
int baby_roll = 0;
//길이, 좌표 조정을 위한 변수
GLfloat roll_z = -4, cry_y = 0;
GLfloat root_scale = -10, bud_scale = -2, grow_scale = -5;
GLfloat wing_scale = 0, wing_temp = -1;
GLfloat bird_x = 0, bird_y = 0, bird_y_temp = 1;
GLfloat baby_y = 0, baby_x = 0;
GLfloat back_color = 0, back_temp = -1, back_speed = 1;
GLfloat camx = -1, camy = 4, camz = 5;
GLfloat cam2x = 0, cam2y = 0, cam2z = 0;
GLfloat cam_upx = 0, cam_upy = 1, cam_upz = 0;

/*=====================콜백 함수===================*/
void mydisplay();
void reshape(int width, int height);
void Mytimer(int value);
/*===============================================*/

/*===================그리기 함수====================*/
void drawBeanBoy();   //주인공 완두콩소년
    void drawBeanBody();
    void drawBeanFace();
void drawLand();      //집으로 가는 길
void drawRoot(GLfloat floor);
void drawBird();      //지나가던 작은 새
    void drawBirdLeg(); //새의 발가락 표현(반복생략)
    void drawExclamationMark(); //콩을 발견한 새 표현
void drawRemind();  //어머니를 회상하는 소년
void drawTree();    //나무로 자라는 소년
    void drawBranch(int angle, GLfloat x, GLfloat y);
/*===============================================*/

/*=================동작 함수=======================*/
void rollBeanBoy();         //소년 구르기
void fallBeanBoy();         //굴러가다 구덩이에 빠진 소년
void cryBeanBoy();          //슬픔에 잠긴 소년
void rootBeanBoy();         //뿌리내리는 소년
void flyingBird();          //날고있는 새
void growBeanBoy();         //씩씩해져 성장하는 소년
void newBeanBaby();         //새로 태어나는 완두콩 아기
void goneTime();            //시간의 흐름(배경의 변화)
/*===============================================*/
int main(int argc, char* argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("완두콩 소년의 귀환");
    
    glutDisplayFunc(mydisplay);
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
    goneTime();         //뒷배경
    drawLand();         //아랫배경
    if (growing)growBeanBoy();      //씩씩해진 소년은 새싹이 튼다
    if (rolling)rollBeanBoy();      //구르며 집에가는 소년
    if (in_hole)fallBeanBoy();      //구덩이에 끼어버리는데
    if (appear_bird)flyingBird();   //등장하는 새!
    if (baby) newBeanBaby();        //완두콩 나무에서 태어나는 아기콩
    
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
        // 구덩이 등장
        if (roll_z >= 3){
            roll_z = -7;
            is_hole = true;
        }
        // 구덩이에 빠짐ㅠ
        if (is_hole && roll_z >= 0.4){
            rolling = false;
            in_hole = true;
        }
    }
    // 2. 구덩이에서 허우적!
    if (in_hole){
        if(confused_count < 20) {//당황한 모습 : 카메라 각도 변경
            camy -=0.1;
            confused_count ++;
        }
        else if(vac_count < 30){                    //허우적 거리는 모습 : 일정한 각도 진동
            if(vac_count % 4 == 0)vaccum = -vaccum;
            roll_angle += vaccum;
            vac_count += 1;
        }
        else crying = true;                        //그만 허우적대고 울기 시작
    }
    // 3. 눈물
    if (crying){
        if(cry_y >= -1){
            cry_y -= 0.02;
            cryBeanBoy();
        }
        else{
            cry_y = 0;  //눈물의 출발점을 눈으로 초기화 (여러번 우는 것을 표현하기 위함)
            crying = false; root = true;    //눈물이 양분이 되어 뿌리가 됨
        }
    }
    // 4. 뿌리 내리기
    if(root){
        crying = true;
        speed_up = true;
        if(root_scale < 5)root_scale += 0.15;
        else appear_bird = true;
    }
    // 5. 새 등장
    if(appear_bird){
        speed_up = false;
        //날개 퍼덕임
        if(help_count == 0 || fail_bird){
            if(wing_scale >= 0.03)wing_temp = 1;
            if(wing_scale <= -0.03)wing_temp = -1;
            wing_angle += 9*wing_temp;
            wing_scale -= 0.015 * wing_temp;
        }
        //새의 움직임
        if(!help_bird){
            if(bird_y >= 1)bird_y_temp = -1;
            if(bird_x >= 0.5 && bird_y <= 0.5)bird_y_temp = 0;
            if(bird_x <= 1)bird_x += 0.01;
            bird_y += 0.015 * bird_y_temp;
            
            //카메라 줌아웃
            if(bird_zoom_count < 60){
                camy = camy * cos(0.1) - camx*sin(0.1); //카메라 줌을 멀리한다.
                bird_zoom_count ++;
            }
            
            //새를 만난 순간
            meet_bird =(bird_x >= 0.5 && bird_x <=0.9);
        }
    }
    // 6. 새와의 만남
    if(meet_bird){
        if(surprise_count > 10)meet_bird = false;
        surprise_count ++;
        reminding = true;
    }
    // 7. 어머니를 떠올리는 소년
    if(reminding){
        if(remind_count > 100) {
            reminding = false;
            help_bird = true;
        }
        remind_count ++;
    }
    // 8. 새의 도움
    if(help_bird){
        //접근
        if(bird_x <= 2.5)bird_x += 0.04;
        if(bird_y >= 0.4)bird_y -= 0.01;
        //도움
        else if(help_count <= 80){
            if(wing_scale >= 0.03)wing_temp = 1;
            if(wing_scale <= -0.03)wing_temp = -1;
            wing_angle += 18*wing_temp;
            wing_scale -= 0.03 * wing_temp;
            help_count++;
        }else fail_bird = true;
    }
    // 9. 새의 실패
    if(fail_bird){
        bird_x += 0.1;
        bird_y += 0.1;
        camy = camy * cos(0.1) + camx*sin(0.1);
        if(bird_x >= 7){
            help_bird = false;
            appear_bird = false;
            meet_bird = false;
            fail_bird = false;
            growing = true;
        }
    }
    // 10. 새싹트기, 나무로 자라기
    if(growing){
        crying = false;
        //씩씩한 표정
        if(brave_count < 30){
            brave_count ++;
            if(bud_scale <= 2)bud_scale += 0.2;
            else speed_up = true;
        }
        else{
            if(zoom_out_count < 30){
                zoom_out_count ++;
            }
            else if(grow_scale < 5){
                grow_scale += 0.5;
                camy = camy * cos(0.1) - camx*sin(0.1);
                camy = camy * cos(0.1) - camx*sin(0.1);
            }
            else baby = true;
        }
    }
    // 11. 아기의 탄생
    if(baby){
        if(baby_y > -3){
            baby_y -= 0.1;
            speed_up = true;
        }
        else {
            baby_roll = (baby_roll - 40) % 360;
            baby_x -= 0.08;
        }
    }
    
    // * 시간의 흐름
    if(back_color >= 0.6 || back_color <= 0)
        back_temp = -back_temp;  //낮밤 변화
    back_color = (back_color + 0.0001 * back_speed * back_temp);
    back_speed = speed_up ? 100 : 1;
    sun_angle += back_speed;
    
    glutTimerFunc(40, Mytimer, 1);
    glutPostRedisplay();
}
void drawBeanBoy(){
    glPushMatrix();
    // 구를 때 보이지 않는 면 제거
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
    if(brave_count > 10){
        glPushMatrix();
        glTranslatef(0, 0.1, 0);
        glScalef(1, 0.2, 0.5);
        glRotatef(-60, 0, 1, 1);
        glutSolidCube(0.1);
        glPopMatrix();
    }
    
    glTranslatef(-0.3, 0, 0);
    glutSolidSphere(0.03, 60, 10);
    
    //굳건한 눈썹
    if(brave_count > 10){
        glPushMatrix();
        glTranslatef(0, 0.1, 0);
        glScalef(1, 0.2, 0.5);
        glRotatef(60, 0, 1, 1);
        glutSolidCube(0.1);
        glPopMatrix();
    }
    //입
    glTranslatef(0.15, -0.1, 0);
    glPushMatrix();
        glScalef(2, 1, 0);
        glutSolidCube(0.04);
        glColor3f(1, 0.3, 0.3);
        glutSolidCube(0.03);
    glPopMatrix();
    
    if(0<confused_count && confused_count < 10)drawExclamationMark();
    if(reminding)drawRemind();
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
    
    //새 꼬리!
        glPushMatrix();
            glTranslatef(-0.5, -0.1, 0);
            glScalef(10, 1, 1);
            glutSolidCube(0.05);
    
            glTranslatef(0, -0.03, 0);
            glutSolidCube(0.03);
        glPopMatrix();
    
    //새 다리!
        glPushMatrix();
            glTranslatef(-0.3, -0.65, 0.15);
            drawBirdLeg();
    
            glTranslatef(0.3, 0.1, 0);
            drawBirdLeg();
        glPopMatrix();
    
    //새 머리 & 몸!
        glColor3f(1, 1, 1);
        glutSolidSphere(0.35, 60, 10);
    
        glTranslatef(-0.1, -0.2, -0.05);
        glutSolidSphere(0.45, 60, 10);
    
    //새 얼굴!
        glPushMatrix();
    glScalef(2, 2, 2);
    glColor3f(0, 0, 0);     //얼굴 색깔
        
        //눈
        if(40<help_count && help_count < 75){
            glTranslatef(0.35, 0.3, 0.2);

            for(GLfloat i=1; i<3; i++){
                glPushMatrix();
                    glTranslatef(0.02*i, 0.05*i,0);
                    glRotatef(30*i, 1, 0, 1);
                    glScalef(1, 5, 1);
                    glutSolidCube(0.02);
                glPopMatrix();
            }
            glTranslatef(-0.2, 0, 0);
            for(GLfloat i=1; i<3; i++){
                glPushMatrix();
                    glTranslatef(0.02*i, 0.05*i,0);
                    glRotatef(90 - 30*i, 1, 0, 1);
                    glScalef(1, 5, 1);
                    glutSolidCube(0.02);
                glPopMatrix();
            }
        }
        else{
            glTranslatef(0.35, 0.3, 0.2);
            glutSolidSphere(0.025, 60, 10);
        
            glTranslatef(-0.2, 0, 0);
            glutSolidSphere(0.025, 60, 10);
        }
        
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
    
    //느김표!
        if(meet_bird)drawExclamationMark();
    glPopMatrix();
}
void flyingBird(){
    glPushMatrix();
    glTranslatef(-2 + bird_x, bird_y, -0.3);
    glScalef(1.5, 1.5, 1.5);
    drawBird();
    glPopMatrix();
}
void goneTime(){
    //낮(0.6,0.8,1) ~ 밤(0.1,0.3,0.5)
    glClearColor(0.6 - back_color,
                 0.8 - back_color,
                 1 - back_color,
                 0);
    
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
        for(GLfloat i=0; i<6; i++)
            drawRoot(i);
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
        glTranslatef(0.3, 0.1, -0.2);
    
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
    if(grow_scale > -2) drawTree();
    glPopMatrix();
}
void drawBirdLeg(){
    glPushMatrix();
        glScalef(1, 5, 1);
        glutSolidCube(0.03);
    glPopMatrix();
    //발가락
    glTranslatef(0, -0.1, 0);
    for(GLfloat i=0; i<3; i++){
        glPushMatrix();
            glTranslatef(0.02*i, 0.02*i,0);
            glRotatef(30*i, 1, 0, 1);
            glScalef(1, 5, 1);
            glutSolidCube(0.02);
        glPopMatrix();
    }

}
void drawExclamationMark(){
    glPushMatrix();
    glTranslatef(0.5, 0.3, 0);
    glutSolidCube(0.04);
    
    glTranslatef(0, 0.2, 0);
    glScalef(1, 5, 1);
    glutSolidCube(0.04);
    glPopMatrix();
}
void drawRemind(){
    glPushMatrix();
    //말풍선
    if(remind_count > 20){
        glColor3f(1, 1, 1);
        glTranslatef(0.3, 0.5, 0);
        glutSolidSphere(0.04, 60, 10);
    }
    if(remind_count > 25){
        glTranslatef(0.1, 0.2, 0);
        glutSolidSphere(0.05, 60, 10);
    }
    if(remind_count > 30){
        glTranslatef(0.1, 0.2, 0);
        glutSolidSphere(0.06, 60, 10);
    }
    if(remind_count > 35){
        glTranslatef(0.5, 1, 0);
        glutSolidSphere(1, 60, 10);
    }
    //어머니
    if(remind_count > 40){
        //몸
        glColor3f(0.7, 1, 0.3);
        glutSolidSphere(0.4, 60, 10);
        glTranslatef(-0.05, -0.1, -0.05);
        glutSolidSphere(0.45, 60, 10);
        
        //뽀글머리
        glColor3f(0, 0, 0);     //얼굴 색깔
        glPushMatrix();
            glTranslatef(-0.3, 0.2, 0);
            
            glPushMatrix();
                for(GLfloat i = 0; i<5; i++){
                    glTranslatef(0.1, i/200, 0);
                    glutSolidSphere(0.1, 60, 10);
                }
                for(GLfloat i = 5; i<7; i++){
                    glTranslatef(0.1, - i/200, 0);
                    glutSolidSphere(0.1, 60, 10);
                }
            glPopMatrix();
        glPopMatrix();
        
        
        //눈
        glTranslatef(0.35, 0.1, 0.2);
        glutSolidSphere(0.03, 60, 10);
        
        glTranslatef(-0.3, 0, 0);
        glutSolidSphere(0.03, 60, 10);
        
        //입
        glTranslatef(0.15, -0.1, 0);
        glColor3f(1, 0, 0);
        glPushMatrix();
            glScalef(1, 0.5, 0);
            glutSolidCone(0.04, 0.04, 10, 10);
            glTranslatef(0, -0.03, 0);
            glutSolidCone(0.04, 0.04, 10, 10);
        glPopMatrix();
        
        
        //팔자주름
        glTranslatef(-0.1, 0, 0);
        glPushMatrix();
        glColor3f(0, 0, 0);
            glTranslatef(0.02, 0.02,0);
            glRotatef(-30, 1, 0, 1);
            glScalef(1, 8, 1);
            glutSolidCube(0.01);
        glPopMatrix();
        
        glTranslatef(0.2, 0, 0);
        glPushMatrix();
        glColor3f(0, 0, 0);
            glTranslatef(0.02, 0.02,0);
            glRotatef(30, 1, 0, 1);
            glScalef(1, 10, 1);
            glutSolidCube(0.01);
        glPopMatrix();
        
    }
    glPopMatrix();
}
void drawTree(){
    glPushMatrix();
        glTranslatef(-0.2, 1, 0.5);
        glColor3f(0.8, 0.8, 0.3);       //나무색깔
        glScalef(1, 2 + grow_scale*2, 1);
        glutSolidCube(0.3);
    glPopMatrix();
    GLfloat left = -0.8, right = 0.8;
    drawBranch(30, left, 0);
    drawBranch(-30, left, 1);
    drawBranch(60, right, 0);
    drawBranch(10, right, 1.5);
}
void drawBranch(int angle, GLfloat x, GLfloat y){
    glPushMatrix();
    //나뭇가지
        glColor3f(0.8, 0.8, 0.3);//나뭇가지색
        glRotated(angle, 0, 1, 0);
        glTranslatef(x, y, 0);
        glPushMatrix();
            glScalef(15, 1, 1);
            glutSolidCube(0.1);
        glPopMatrix();
        //나뭇잎
        glColor3f(0.5, 1, 0.25);
        glTranslatef(x * 1.2, 0, 0);
        glScalef(3, 1, 1);
        glRotated(60, 1, 1, 0);
        glutSolidCube(0.2);
    glPopMatrix();
    
}
void newBeanBaby(){
    glPushMatrix();
        glTranslatef(-0.5, 1.2, 0);
        glColor3f(1, 1, 0);
            glPushMatrix();
            glScalef(0.5, 1.5, 0);
            glutSolidCone(0.2, 0.04, 10, 10);
            glPopMatrix();
        glTranslatef(baby_x, baby_y, 0);
        glutSolidSphere(0.1, 60, 10);
        
    glPopMatrix();
    
}
