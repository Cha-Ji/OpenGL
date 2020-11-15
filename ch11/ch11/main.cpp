//
#define GL_SILENCE_DEPRECATION
#include <GLUT/GLUT.h>
#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 500

void mydisplay();
void reshape(int width, int height);
void drawFloor(GLfloat y);
void drawWall(GLfloat z);
void init_light();

GLfloat camx = 0, camy = 5, camz = -7;
GLfloat cam2x = 0, cam2y = 0, cam2z = 0;
GLfloat cam_upx = 0, cam_upy = 1, cam_upz = 0;

int main(int argc, char* argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_SINGLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(300, 200);

    glutCreateWindow("Lighting");
    glClearColor(0.0, 0.0, 0.0, 1.0);
    init_light();

    glutDisplayFunc(mydisplay);
    glutReshapeFunc(reshape);

    glutMainLoop();
    return 0;
}

void mydisplay(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //각각의 용도?
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(camx, camy, camz, cam2x, cam2y, cam2z, cam_upx, cam_upy, cam_upz);

    drawFloor(-2.5);
    drawWall(2.5);



    glutSolidSphere(0.3, 20, 20);
    glutSwapBuffers();
    glFlush();
}

void reshape(int width, int height){
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    GLfloat ratio = (float)width/height;
    gluPerspective(40, ratio, 0.1, 1000);

}

void drawFloor(GLfloat y){
    GLfloat x = -2.5, z = -2.5, w = 5;
    glBegin(GL_POLYGON);
            glNormal3f(-2, 1, 0); //법선 벡터의 합은 1이 되어야 한다.
        glVertex3f(x, y, z);
        glVertex3f(x, y, z+w);
            glNormal3f(2, 1, 0);
        glVertex3f(x+w, y, z+w);
        glVertex3f(x+w, y, z);
    glEnd();
}

void drawWall(GLfloat z){
    GLfloat x = -2.5, y = -2.5, w = 5;
    glNormal3f(0, 0, -1);
    glBegin(GL_POLYGON);
        glVertex3f(x, y, z);
        glVertex3f(x, y+w, z);
        glVertex3f(x+w, y+w, z);
        glVertex3f(x+w, y, z);
    glEnd();
}

void init_light(){
    glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);

    GLfloat bNonDirectionalLight = 1;   //directional light가 아닌 것
    //전역 주변광
    GLfloat light_global_ambient[] ={0.5, 0.5, 0.5, 1.0};   //R, G, B, A
    GLfloat light_0_pos[] = {5.0, 5.0, 0.0, bNonDirectionalLight};

    GLfloat light_0_ambient[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_0_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_0_specaular[] = {1.0, 1.0, 1.0, 1.0};

    //==================광원1 추가====================
    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_AMBIENT, light_0_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_0_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_0_specaular);

        //광원의 위치, 방향, spotlight
    GLfloat light_1_pos[] = {0.0, 0.0, -5.0, 1};
    GLfloat light_1_dir[] = {0.0, 0.0, -0.0, 1};
    GLfloat SpotAngel[] = {20.0};
    glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, SpotAngel);

        //흐려짐
    GLfloat SpotExp1[] = {0.0};
    glLightfv(GL_LIGHT1, GL_SPOT_EXPONENT, SpotExp1);
    //glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light_1_dir);
    //===================================================
    
    
    
    
    glEnable(GL_NORMALIZE); //법선 벡터 세 개의 합을 1로 만들어 준다.
//    전역 주변광 만으로는 물체끼리 구별을 하기 힘들어진다.
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_POSITION, light_0_pos);
   

    //물체가 반사하는 빛
    GLfloat material_0_ambient[] = { 1.0,0.0,0.0,0.0 };
    GLfloat material_0_diffuse[] = { 0.8,0.0,0.0,1.0 };
    GLfloat material_0_specular[] = { 1.0,1.0,1.0,1.0 };
    GLfloat material_0_shininess[] = { 10.0 }; // 0~ 128
    GLfloat meterial_0_emission[] = { 0.0,0.0,1.0,1.0 };
    
    glMaterialfv(GL_FRONT,GL_AMBIENT, material_0_ambient);
    glMaterialfv(GL_FRONT,GL_DIFFUSE, material_0_diffuse);
    glMaterialfv(GL_FRONT,GL_SPECULAR, material_0_specular);
    glMaterialfv(GL_FRONT,GL_SHININESS, material_0_shininess);
//    glMaterialfv(GL_FRONT, GL_EMISSION, meterial_0_emission);
    glLightfv(GL_LIGHT1, GL_POSITION, light_1_pos);
//
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_global_ambient);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);    //부드럽게

}
