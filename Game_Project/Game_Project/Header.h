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


//============변수============
    //파일 경로
string filePath = "/Users/cha-ji/Downloads/blender/";
  //카메라 변수
GLfloat camx = -14, camy = 1, camz = 0;
GLfloat cam2x = 0, cam2y = 0.1, cam2z = 0;
GLfloat cam_upx = 0, cam_upy = 1, cam_upz = 0;
GLint camy_mark = 1; //걸을 때, 들썩임을 표현

  //현재 맵이 몇 번 맵인지
int map_num = 1; // 0 : 3층, 1 : 2층, 2: 1층, 3: 탈출
int exit_floor_cnt = 0; //탈출 애니메이션 카운트
//애니메이션 진행 중 키보드 인식 불가
bool dontTouch = false;

bool getKey = false;
//층 넘어가기
void exit3Floor(int value);

void initGame();
#endif /* Header_h */
