#define GL_SILENCE_DEPRECATION
#include <GLUT/GLUT.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 500

string imgPath = "/Users/cha-ji/Git/OpenGL/ch13/ch13/귤화냄.png";
GLfloat camx = 2, camy = 2, camz = 5;
GLfloat cam2x = 0, cam2y = 0, cam2z = 0;
GLfloat cam_upx = 0, cam_upy = 1, cam_upz = 0;

//=========화면 출력을 위한 함수========================
void mydisplay();
void reshape(int width, int height);
void init_light();
void set_light();
void set_material_color();
void display_objs();
void init_texture(uchar* pImageArray, int width, int height);
//===============================================
int main(int argc, char** argv){
    Mat image = imread(imgPath, IMREAD_COLOR);
    cvtColor(image, image, COLOR_BGR2RGB);
    //gl 관련
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_SINGLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(300, 200);
    
    glutCreateWindow("Texture");
    
    glClearColor(0.0, 0.0, 0.0, 0.0);   //R, G, B, A(투명도)
    init_light();
    init_texture(image.data, image.cols, image.rows);
    glutDisplayFunc(mydisplay);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}


void mydisplay(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(camx, camy, camz,
              cam2x, cam2y, cam2z,
              cam_upx, cam_upy, cam_upz);
    
    set_light();
    set_material_color();
    
    display_objs();
    
    glFlush();
}

void reshape(int width, int height){
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    GLfloat ratio = (float)width/height;
    gluPerspective(40, ratio, 0.1, 1000);
    
}

void init_light(){
    glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
}
GLfloat light_global_ambient[] = {0.3, 0.3, 0.3, 1.0}; //전역 조명
void set_light(){
    //빛의 색상 & 위치 정의
    
    GLfloat light_0_pos[] = {2.0, 2.0, 5.0, 1.0};
    GLfloat light_0_ambient[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_0_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_0_specular[] = {1.0, 1.0, 1.0, 1.0};
    
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_global_ambient);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_0_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_0_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_0_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_0_pos);
    

    
}

void set_material_color(){
    
    //물체 색상 정의 & 지정
    GLfloat matrial_0_ambient[] = {0.3, 0.3, 0.3, 1.0};
    GLfloat matrial_0_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat matrial_0_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat matrial_0_shininess[] = {25.0};
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, matrial_0_ambient);
    glLightfv(GL_FRONT, GL_DIFFUSE, matrial_0_diffuse);
    glLightfv(GL_FRONT, GL_SPECULAR, matrial_0_specular);
    glLightfv(GL_FRONT, GL_SHININESS, matrial_0_shininess);
    
}



void display_objs(){
    GLfloat v1[3] = {-1, -1, 1};
    GLfloat v2[3] = {-1, 1, 1};
    GLfloat v3[3] = {1, 1, 1};
    GLfloat v4[3] = {1, -1, 1};
    
        
    for(int i=0; i<8; i++){
    //한 평면
        int a = i > 4 ? 1 : 0;
        int b = i <= 4  ? 1 : 0;
        
        glRotatef(90*i, a, b, 0);
        glBegin(GL_POLYGON);

        glNormal3f(0, 0, 1);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(v1[0], v1[1], v1[2]);
        glTexCoord2f(0.0, 0.0);
        glVertex3f(v2[0], v2[1], v2[2]);
        glTexCoord2f(0.8, 0.0);
        glVertex3f(v3[0], v3[1], v3[2]);
        glTexCoord2f(0.8, 1.0);
        glVertex3f(v4[0], v4[1], v4[2]);
        glEnd();
    }
    
    
}

void init_texture(uchar* pImageArray, int width, int height){
    GLuint tex_id = 1;
    glGenTextures(1, &tex_id);
    glBindTexture(GL_TEXTURE_2D, tex_id);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB, width, height,
                 0, GL_RGB, GL_UNSIGNED_BYTE, pImageArray);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glEnable(GL_TEXTURE_2D);
}
