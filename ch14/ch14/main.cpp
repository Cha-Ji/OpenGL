#include <opencv2/opencv.hpp>
#include <GLUT/GLUT.h>
#include "model.h"

using namespace cv;

#define _WINDOW_WIDTH 500
#define _WINDOW_HEIGHT 500

CModel m;
Mat image[2];
GLuint tex_ids[2] = {1,2};
int nTex = 2;

GLfloat camx = 2, camy = 4, camz = 10;
GLfloat cam2x = 0, cam2y = 0, cam2z = 0;
GLfloat cam_upx = 0, cam_upy = 1, cam_upz = 0;

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat ratio = (float)width / height;
    gluPerspective(40, ratio, 0.1, 1000);
}

void set_light() {
    //빛의 색상 및 위치 정의
    int bNonDirectionalLight = 1;
    GLfloat light_global_ambient[] = { 0.3, 0.3 , 0.3 ,1.0 };
    GLfloat light_0_pos[] = { 8.0, 8.0, 8.0 , 1.0 };
    GLfloat light_0_ambient[] = { 1.0,1.0,1.0,1.0 };
    GLfloat light_0_diffuse[] = { 1.0,1.0,1.0,1.0 };
    GLfloat light_0_specular[] = { 1.0,1.0,1.0,1.0 };

    //빛 활성화, 빛 색상 & 위치 적용
    glEnable(GL_LIGHT0);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_global_ambient);
    glLightfv(GL_LIGHT1, GL_AMBIENT, light_0_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_0_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_0_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_0_pos);
}

void set_metrial_color() {
    //물체 색상 정의 & 지정
    glDisable(GL_COLOR_MATERIAL);
    GLfloat material_0_ambient[] = { 1.0,1.0,1.0,1.0 };
    GLfloat material_0_diffuse[] = { 1.0,1.0,1.0,1.0 };
    GLfloat material_0_specular[] = { 1.0,1.0,1.0,1.0 };
    GLfloat material_0_shininess[] = { 50.0 }; // 0~ 128
    glMaterialfv(GL_FRONT, GL_AMBIENT, material_0_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material_0_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, material_0_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, material_0_shininess);
}
void display_objs() {
    GLfloat x, y, z, nx, ny, nz , tx, ty;
    int v_id = 0, vt_id = 0, vn_id = 0;
    int idx;

    for (int o = 0; o < m.objs.size(); o++) {
        if (o == 0) {
            idx = 0;
        }
        else {
            idx = 1;
        }
        glBindTexture(GL_TEXTURE_2D, tex_ids[0]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB
            ,image[idx].cols, image[idx].rows, 0, GL_RGB, GL_UNSIGNED_BYTE, image[idx].data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        int nFaces = m.objs[o].f.size();
        for (int k = 0; k < nFaces; k++) {
            int nPoints = m.objs[o].f[k].v_pairs.size();
            glBegin(GL_POLYGON);
            for (int i = 0; i < nPoints; i++) {
                v_id = m.objs[o].f[k].v_pairs[i].d[0];
                vt_id = m.objs[o].f[k].v_pairs[i].d[1];
                vn_id = m.objs[o].f[k].v_pairs[i].d[2];

                x = m.objs[o].v[v_id - 1].d[0];
                y = m.objs[o].v[v_id - 1].d[1];
                z = m.objs[o].v[v_id - 1].d[2];

                nx = m.objs[o].vn[vn_id - 1].d[0];
                ny = m.objs[o].vn[vn_id - 1].d[1];
                nz = m.objs[o].vn[vn_id - 1].d[2];

                tx = m.objs[o].vt[vt_id - 1].d[0];
                ty = m.objs[o].vt[vt_id - 1].d[1];

                glNormal3f(nx, ny, nz);
                glTexCoord2f(tx, ty);
                glVertex3f(x, y, z);
            }
            glEnd();
        }
    }

}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(camx, camy, camz, cam2x, cam2y, cam2z, cam_upx, cam_upy, cam_upz);

    set_light();
    set_metrial_color();
    display_objs();

    glFlush();
}

void init_light() {
    glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);

    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

}
void init_texture() {
    glGenTextures(nTex, tex_ids);
    glEnable(GL_TEXTURE_2D);
}

int main(int argc, char** argv) {

    //택스쳐 이미지 읽어오기
    image[0] = imread("/Users/cha-ji/Downloads/blender/wood.jpg", IMREAD_COLOR);
    cvtColor(image[0], image[0], COLOR_BGR2RGB);
    image[1] = imread("/Users/cha-ji/Downloads/blender/stone.jpg", IMREAD_COLOR);
    cvtColor(image[1], image[1], COLOR_BGR2RGB);

    //모델 읽어오기
    string filepath = "/Users/cha-ji/Downloads/blender/cube.obj";
    ifstream fin(filepath);

    m.loadObj(fin);
    fin.close();


    //glu 초기화
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_SINGLE);
    glutInitWindowSize(_WINDOW_WIDTH, _WINDOW_HEIGHT);
    glutInitWindowPosition(0, 0);
    

    glutCreateWindow("two Texture");
    glClearColor(0.0, 0.0, 0.0, 0.0);
    init_light();
    init_texture();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
