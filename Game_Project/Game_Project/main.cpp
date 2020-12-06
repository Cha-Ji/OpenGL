#include "Header.h"         //라이브러리, 함수, 전역변수 선언
#include "load_object.h"    //obj파일을 불러오기 위한 헤더
#include "Light.h"          //조명 함수
#include "Walking.h"        //주인공의 움직임
#include "CallBack.h"       //타이머 & reshape콜백 함수
#include "Drawing.h"        //그리기 함수

void mydisplay();           //디스플레이 함수
void myKeyboard(unsigned char KeyPressed, int x, int y);        //키보드 콜백 함수


int main(int argc, char** argv){
    ifstream fin(filePath + "hallway.obj");
    third_floor.loadObj(fin);
    fin.close();
    
    ifstream fin2(filePath + "hand.obj");
    hand.loadObj(fin2);
    fin2.close();
    
    ifstream fin3(filePath + "hallway.obj");
    sec_floor.loadObj(fin3);
    fin3.close();
    
    ifstream fin4(filePath + "hand_light.obj");
    hand_light.loadObj(fin4);
    fin4.close();
    
    //gl 관련
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_SINGLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(300, 200);
    
    glutCreateWindow("Escape Here");
    
    glClearColor(0.0, 0.0, 0.0, 1.0);   //R, G, B, A(투명도)
    initLight();
    
    glutDisplayFunc(mydisplay);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(myKeyboard);
    glutMainLoop();
    return 0;
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
    
    //조명, 메테리얼 설정
//    setLight();
//    setMaterialColor();
    
    /*========그리기 시작========*/
    //초기위치 설정
    glTranslated(-15, -0.5, 0);
    
    glPushMatrix();
    //3층 맵
    if(map_num == 0){
        setLight();
        setMaterialColor();
        display3Floor();
    }
    //2층 맵
    if(map_num == 1){
        setLight();
        display2Floor();
    }
    
        //손 그리기
    if(!light_tmp)drawHand();
    else drawHandLight();
    glPopMatrix();
    glFlush();
}

//키보드 콜백 함수
int cnt = 0;
void myKeyboard(unsigned char KeyPressed, int x, int y){
    if(!dontTouch){
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
                glutTimerFunc(40, exit3Floor, 1);
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
        }
    }
    glutPostRedisplay();
}



