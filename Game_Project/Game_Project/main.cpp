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
    drawIntro();
    
    return 0;
}
void initGame(){
    image = imread(filePath + "zombie.jpg",IMREAD_COLOR);
    cvtColor(image,image, COLOR_BGR2RGB);

    image2 = imread(filePath + "end_map.jpg",IMREAD_COLOR);
    cvtColor(image2,image2, COLOR_BGR2RGB);
    
    ifstream fin(filePath + "floor2.obj");
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
    
    ifstream fin6(filePath + "human.obj");
    zombie.loadObj(fin6);
    fin6.close();
    
    ifstream fin7(filePath + "end_map.obj");
    end_map.loadObj(fin7);
    fin7.close();
    
    //gl 관련
    glutCreateWindow("Escape Here");
    glClearColor(0.1, 0.3, 0.5, 1.0);   //R, G, B, A(투명도)
    init_texture();
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
    setLight();
    setMaterialColor();
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_global_ambient);
    
    if(ending){
        exitLight();
        glPushMatrix();
        glTranslatef(0, 0, -20);
        displayEnding();
        glPopMatrix();
        glClearColor(0.6, 0.8, 1, 1);
    }else if(map_num == 0){
        display2Floor();
        
        //열쇠 위치 설정
        glPushMatrix();
            glTranslated(13, 1.5, -10);
            glRotated(90, 1, 0, 0);
            if(!getKey)displayKey();
        glPopMatrix();
        
        //시체 놀래키기
        glPushMatrix();
            if(inZombieRoom)displayZombie();
        glPopMatrix();
    }
    //2층 맵
    else if(map_num == 1){
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
    
    //탈출 맵
    
    
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
            case 'd':
                turnRight();
                break;
                
            case 'l':
                light_tmp = !light_tmp;
                break;
                
            //검사용
            case 'z':
                glutTimerFunc(40, exit1Floor, 2);
                break;
                //오른쪽 회전
            case'x':
                glutTimerFunc(40, exit2Floor, 1);
                break;
            case'c':
                getKey = true;
                break;

            case 'm':
                printf("x : %f, 2x : %f, z : %f, 2z : %f\n",camx, cam2x, camz, cam2z);
                printf("r : %f g : %f b :%f \n",light_global_ambient[0],light_global_ambient[1],light_global_ambient[2]);
                break;
            case 'k':
                if(keyArea()) {
                    getKey = true;
                    glutTimerFunc(40, zombieTimer, 4);
                }
                break;
        }
    }
    glutPostRedisplay();
}



