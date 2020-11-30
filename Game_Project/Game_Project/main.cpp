#include "Header.h"         //라이브러리, 함수, 전역변수 선언
#include "load_object.h"    //obj파일을 불러오기 위한 헤더
#include "Light.h"      //조명 함수
#include "CallBack.h"   //타이머 & reshape콜백 함수
#include "Walking.h"    //주인공의 움직임
int main(int argc, char** argv){
    ifstream fin(filePath + "hallway.obj");
    hallway.loadObj(fin);
    fin.close();
    
    ifstream fin2(filePath + "hand.obj");
    hand.loadObj(fin2);
    fin2.close();
    
    //gl 관련
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_SINGLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(300, 200);
    
    glutCreateWindow("Escape Here");
    
    glClearColor(0.0, 0.0, 0.0, 0.0);   //R, G, B, A(투명도)
    init_light();
    
    glutDisplayFunc(mydisplay);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(myKeyboard);
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
    set_spotlight();
    glTranslated(-15, -0.5, 0);
    glPushMatrix();
        display_hallway_objs();
        glTranslated(hand_pos_x + camx, 0, hand_pos_z + camz);
        glRotated(-90 + hand_angle, 0, 1, 0);
        glTranslated(hand_turn_z, 0, hand_turn_x);
        glScalef(0.1, 0.1, 0.1);
        display_hand_objs();
    glPopMatrix();
    glFlush();
}

void myKeyboard(unsigned char KeyPressed, int x, int y){
    switch (KeyPressed){
        case 'w':
            if(walk_front_cnt == 0)
                glutTimerFunc(10, myTimer, 1);
            break;
        case 'a':
            turn_left();
            break;
        case 's':
            camx -= 0.01;
            break;
        case 'd':
            turn_right();
            break;
        case 'l':
            light_global_ambient[0] -= 0.002;
            light_global_ambient[1] -= 0.01;
            light_global_ambient[2] -= 0.01;
            break;
    }
    glutPostRedisplay();
}



