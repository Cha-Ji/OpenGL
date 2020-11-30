#ifndef Header_h
#define Header_h
#define GL_SILENCE_DEPRECATION
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

#include <opencv2/opencv.hpp>
#include <GLUT/GLUT.h>
#include <vector>
#include <string>
#include <fstream>
#include <math.h>
#include <iostream>
using namespace std;

//============변수============
GLfloat camx = -14, camy = 1, camz = 0;
GLfloat cam2x = 0, cam2y = 0.1, cam2z = 0;
GLfloat cam_upx = 0, cam_upy = 1, cam_upz = 0;
GLint camy_mark = 1; //걸을 때, 들썩임을 표현

GLfloat light_global_ambient[] = {0.3, 0.3, 0.3, 1.0}; //전역 조명
string filePath = "/Users/cha-ji/Downloads/blender/";
int walk_front_cnt = 0;  //걷기 타이머의 카운터

//손의 움직임
GLfloat hand_pos_x = 15.2, hand_pos_z = 0;
GLfloat hand_turn_x = -2.8, hand_turn_z = 0, hand_angle = 0;
//============================


//===============콜백 & 조명 함수=======================
void mydisplay();
void reshape(int width, int height);
void init_light();
void set_light();
void set_spotlight();
void set_material_color();
void myKeyboard(unsigned char KeyPressed, int x, int y);
void myTimer(int value);
//===============================================


//========주인공 동작 함수=========================
void turn_left();
void turn_right();
void walk_front();
//=========================================
#endif /* Header_h */
