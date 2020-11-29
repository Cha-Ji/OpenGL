#ifndef Header_h
#define Header_h

#define GL_SILENCE_DEPRECATION
#include <GLUT/GLUT.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

GLfloat camx = -7, camy = 0.2, camz = 0;
GLfloat cam2x = 0, cam2y = 0.1, cam2z = 0;
GLfloat cam_upx = 0, cam_upy = 1, cam_upz = 0;

//=========화면 출력을 위한 함수========================
void mydisplay();
void reshape(int width, int height);
void init_light();
void set_light();
void set_material_color();
void myKeyboard(unsigned char KeyPressed, int x, int y);
void display_objs();
//===============================================
#endif /* Header_h */
