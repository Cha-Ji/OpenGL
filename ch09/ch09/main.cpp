#define GL_SILENCE_DEPRECATION
#include <GLUT/GLUT.h>
#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 500

GLfloat camx = 0, camy = 5, camz = -4;
GLfloat cam2x = 0, cam2y = 0, cam2z = 10;
GLfloat cam_upx = 0, cam_upy = 1, cam_upz = 0;

GLenum src = GL_SRC_ALPHA;
GLenum dest = GL_ONE_MINUS_SRC_ALPHA;


void mydisplay();
void reshape(int width, int height);
void drawRect(GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat r, GLfloat g, GLfloat b);
void drawBlackWhiteRect(GLint nx,GLint nz,
                        GLfloat sx, GLfloat sy, GLfloat sz,
                        GLfloat w, int bBlack);
void myKeyboard(unsigned char key, int x, int y);
int main(int argc, char* argv[]){
    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(0, 0);
    
    glutCreateWindow("Anti-Aliasing");
    
    glutDisplayFunc(mydisplay);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}

void mydisplay(){
    glClear(GL_COLOR_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    gluLookAt(camx, camy, camz,cam2x, cam2y, cam2z,cam_upx, cam_upy, cam_upz);
    
//    glEnable(GL_BLEND);
//    glBlendFunc(src, dest);
//    
//    glEnable(GL_POINT_SMOOTH);
//    glEnable(GL_LINE_SMOOTH);
//    glEnable(GL_POLYGON_SMOOTH);
//    glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);
//    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
//    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    

    for(int i=0; i<1000; i++)
        for(int j=0; j<1000; j++){
            int bBlack = (i + j) % 2;
            drawBlackWhiteRect(i, j, -10, 0, 0, 0.2, bBlack);
        }
    
    //glDisable(GL_BLEND);
    
    
    glFlush();
}

void reshape(int width, int height){
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    GLfloat ratio = (float)width/height;
    gluPerspective(40, ratio, 0.1, 1000);
}


void drawRect(GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLfloat r, GLfloat g, GLfloat b){
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
        glVertex3f(x, y, z);
        glVertex3f(x + w, y, z);
        glVertex3f(x + w, y, z + w);
        glVertex3f(x, y, z + w);
    glEnd();
}

void drawBlackWhiteRect(GLint nx,GLint nz,
                        GLfloat sx, GLfloat sy, GLfloat sz,
                        GLfloat w, int bBlack){
    GLfloat x, y, z;
    x = sx + nx * w;
    y = sy;
    z = sz + nz * w;
    
    if(bBlack == 1)
        drawRect(x, y, z, w, 0, 0, 0);
    else
        drawRect(x, y, z, w, 1, 1, 1);
}
void myKeyboard(unsigned char key, int x, int y){

    
}
