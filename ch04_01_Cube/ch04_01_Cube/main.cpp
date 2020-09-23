#include <GLUT/GLUT.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

GLfloat defaultCube[8][3] = {
    {-0.5, -0.5, 0.5}, {-0.5, 0.5, 0.5},
    {0.5, -0.5, 0.5}, {0.5, 0.5, 0.5},
    {0.5, -0.5, -0.5}, {0.5, 0.5, -0.5},
    {-0.5, 0.5, -0.5}, {-0.5, -0.5, -0.5}
};
GLfloat color[8][3] = {{0.2, 0.2, 0.2},
    {1.0, 0.0, 0.0}, {1.0, 1.0, 0.0},
    {0.0, 1.0, 0.0},
    {0.0, 0.0, 1.0}, {1.0, 0.0, 1.0},
    {1.0, 1.0, 1.0}, {0.0, 1.0, 1.0}
};
int list_id;

void drawCube(GLfloat size, GLfloat x, GLfloat y, GLfloat z){
    GLfloat myCube[8][3];
    for(int i=0; i<8; i++){
        myCube[i][0] = size * defaultCube[i][0] + x;
        myCube[i][1] = size * defaultCube[i][1] + y;
        myCube[i][2] = size * defaultCube[i][2] + z;
    }
    int idx[6][4] = {
        {0,3,2,1}, {2,3,7,6}, {7,4,5,6},
        {1,2,6,5}, {0,3,7,4}, {0,4,5,1}
    };
    
    for(int i=0; i < 6; i++){
        int idx0 = idx[i][0];
        int idx1 = idx[i][1];
        int idx2 = idx[i][2];
        int idx3 = idx[i][3];
        glBegin(GL_POLYGON);
        glColor3fv(color[idx0]); glVertex3fv(myCube[idx0]);
        glColor3fv(color[idx1]); glVertex3fv(myCube[idx1]);
        glColor3fv(color[idx2]); glVertex3fv(myCube[idx2]);
        glColor3fv(color[idx3]); glVertex3fv(myCube[idx3]);
        glEnd();
        
    }
}

void createList(){
    list_id = glGenLists(1);
    glNewList(list_id, GL_COMPILE);
    int level = 10;
    for(GLfloat y=0; y < level; y++)
        for(GLfloat x = -(level-y); x < (level - y) - 1; x++){
            for(GLfloat z = -(level-y); z < (level - y) - 1; z++)
                drawCube(0.1, x/10.0, y/10.0, z/10.0);
        }
    glEndList();
}
void mydisplay(){
    glClear(GL_COLOR_BUFFER_BIT);   //clear
    glCallList(list_id);
    glFlush();
}

void reshape(int width, int height){
    glViewport(0, 0, width, height);
    GLfloat f_w = (GLfloat)width / (GLfloat)WINDOW_WIDTH;
    GLfloat f_h = (GLfloat)height / (GLfloat)WINDOW_HEIGHT;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0 * f_w, 1.0 * f_w, -1.0 * f_h, 1.0 * f_h, -2, 2);
    gluLookAt(0.5, 0.5, 1, 0, 0, 0, 0, 1, 0);
    
}
int main(int argc, char* argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("pyramid");
    //glClearColor(0.0,0.0,0.0,1.0);
    
    glutDisplayFunc(mydisplay);
    glutReshapeFunc(reshape);
    createList();
    glutMainLoop();
    return 0;
}

