#include "Header.h"         //라이브러리, 함수, 전역변수 선언
#include "load_object.h"    //obj파일을 불러오기 위한 헤더
#include "Light.h"          //조명 함수
#include "Walking.h"        //주인공의 움직임
#include "CallBack.h"       //타이머 & reshape콜백 함수
#include "Drawing.h"        //그리기 함수
#include "Intro.h"          //opencv로 게임 시작 인트로 그리기

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_SINGLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(300, 200);
    initGame();
//    drawIntro(); TODO: 인트로
    
    return 0;
}
void initGame(){
    ifstream fin(filePath + "floor3.obj");
    floor2.loadObj(fin);
    fin.close();
    
    ifstream fin2(filePath + "floor1.obj");
    floor1.loadObj(fin2);
    fin2.close();
    
    ifstream fin3(filePath + "key.obj");
    key.loadObj(fin3);
    fin3.close();
    
    ifstream fin4(filePath + "hand.obj");
    hand.loadObj(fin4);
    fin4.close();
    
    ifstream fin5(filePath + "hand_light.obj");
    hand_light.loadObj(fin5);
    fin5.close();
    
    //gl 관련
    glutCreateWindow("Escape Here");
    glClearColor(0.0, 0.0, 0.0, 1.0);   //R, G, B, A(투명도)
    initLight();
    glutDisplayFunc(mydisplay);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(myKeyboard);
        glutMainLoop();
        
}
void mydisplay(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    //손전등 설정
    glPushMatrix();
        setSpotLight();
    glPopMatrix();
    
    //카메라 뷰 설정
    gluLookAt(camx, camy, camz,
              cam2x, cam2y, cam2z,
              cam_upx, cam_upy, cam_upz);
    
    /*========그리기 시작========*/
    //초기위치 설정
    glTranslated(-15, -0.5, 0);
    glPushMatrix();
    //3층 맵
    if(map_num == 0){
        setLight();
        setMaterialColor();
        display2Floor();
        
        //열쇠 위치 설정
        glPushMatrix();
            glTranslated(13, 1.5, -10);
            glRotated(90, 1, 0, 0);
            if(!getKey)displayKey();
        glPopMatrix();
        
        //시체 놀래키기
        glPushMatrix();
        
        glPopMatrix();
    }
    //2층 맵
    if(map_num == 1){
        setLight();
        display1Floor();
        //열쇠 위치 설정
        if(!getKey){
            glPushMatrix();
                glTranslated(35, 1.5, 4);
                glRotated(30, 3, 0, 0);
                displayKey();
            glPopMatrix();
        }
    }
    
        //손 그리기
    if(!light_tmp)drawHand();
    else if(light_tmp && !ending)drawHandLight();
    glPopMatrix();
    glFlush();
}
void myKeyboard(unsigned char KeyPressed, int x, int y){
    if(!dontTouch){//TODO: 키입력 다고치기
        switch (KeyPressed){
                //전진
            case 'w':
                if(!walkValid() && walk_front_cnt == 0)
                    glutTimerFunc(10, walkFrontTimer, 1);
                break;
                //왼쪽 회전
            case 'a':
                turnLeft();
                break;
                //
            case 's':
                glutTimerFunc(40, exit1Floor, 2);
                break;
                //오른쪽 회전
            case 'd':
                turnRight();
                break;
            case 'l':
                light_tmp = !light_tmp;
                break;
            case 'g':
                light_global_ambient[1] += 0.05;
                break;
            case 'b':
                light_global_ambient[2] -=0.05;
                break;
            case 'm':
                printf("x : %f, 2x : %f, z : %f, 2z : %f\n",camx, cam2x, camz, cam2z);
                printf("cnt : %d",walk_front_cnt);
                break;
            case 'k':
                if(keyArea()) getKey = true;
                break;
        }
    }
    glutPostRedisplay();
}



