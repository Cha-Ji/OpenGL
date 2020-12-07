#ifndef Header_h
#define Header_h
#define GL_SILENCE_DEPRECATION
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 800

#include <opencv2/opencv.hpp>
#include <GLUT/GLUT.h>
#include <vector>
#include <string>
#include <fstream>
#include <math.h>
#include <iostream>

using namespace std;

//============전역 변수============
//파일 경로
string filePath = "/Users/cha-ji/Downloads/blender/";
//카메라 변수
GLfloat camx = -14, camy = 1, camz = 0;
GLfloat cam2x = 0, cam2y = 0.1, cam2z = 0;
GLfloat cam_upx = 0, cam_upy = 1, cam_upz = 0;
GLint camy_mark = 1;            //걸을 때, 들썩임을 표현

int map_num = 0;                // 0 : 2층, 1 : 1층
int exit_floor_cnt = 0;         //탈출 애니메이션 카운트

bool dontTouch = false;         //키입력을 막는 상태인지
bool ending = false;            //엔딩을 보는 상태인지
bool getKey = false;            //키를 얻은 상태인지

//층 넘어가기
void exit2Floor(int value);
void exit1Floor(int value);
void initGame();    //게임 시작

void mydisplay();           //디스플레이 함수
void myKeyboard(unsigned char KeyPressed, int x, int y);        //키보드 콜백 함수
bool keyArea(){
    if(map_num == 0){
        return (-3 <= camx && camx <= -2
           && -10 <= camz && camz <= -8
                && cam2z <= -16);
    }else if(map_num == 1){
        return (19<= camx && camx <= 21.5
                && 0.5 <= camz && cam2z >= 9);
    }
    return false;
}         //키를 습득할 수 있는 위치인지
bool inZombieRoom = false;
#endif /* Header_h */
