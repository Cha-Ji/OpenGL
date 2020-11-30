#ifndef Header_h
#define Header_h

#define GL_SILENCE_DEPRECATION
#include <opencv2/opencv.hpp>
#include <GLUT/GLUT.h>
#include <vector>
#include <string>
#include <fstream>
#include <math.h>
#include <iostream>
using namespace std;
#include "load_object.h"    //obj파일을 불러오기 위한 헤더

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
GLfloat camx = -14, camy = 0.2, camz = 0;
GLfloat cam2x = 0, cam2y = 0.1, cam2z = 0;
GLfloat cam_upx = 0, cam_upy = 1, cam_upz = 0;
GLint camy_mark = 1;
GLfloat light_global_ambient[] = {0.3, 0.3, 0.3, 1.0};//전역 조명
//=========화면 출력을 위한 함수========================
void mydisplay();
void reshape(int width, int height);
void init_light();
void set_light();
void set_material_color();
void myKeyboard(unsigned char KeyPressed, int x, int y);
void display_objs(CModel m);
//===============================================
//========주인공 동작 함수=========================
void turn_left();
void turn_right();
void walk_front();
//=========================================
#endif /* Header_h */
