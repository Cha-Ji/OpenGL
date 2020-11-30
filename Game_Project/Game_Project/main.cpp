#include "Header.h"         //라이브러리, 함수, 전역변수 선언

int main(int argc, char** argv){

    loadObject("hallway", hallway);
    
    
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
    
    glTranslated(-15, -0.5, 0);
        display_objs(hallway);
    
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

void set_light(){
    //빛의 색상 & 위치 정의
    GLfloat light_0_pos[] = {2.0, 2.0, 2.0, 1.0};
    GLfloat light_0_ambient[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_0_diffuse[] = {0.1, 0.1, 0.7, 1.0};
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
    GLfloat matrial_0_diffuse[] = {0.8, 0.0, 0.3, 1.0};
    GLfloat matrial_0_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat matrial_0_shininess[] = {25.0};
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, matrial_0_ambient);
    glLightfv(GL_FRONT, GL_DIFFUSE, matrial_0_diffuse);
    glLightfv(GL_FRONT, GL_SPECULAR, matrial_0_specular);
    glLightfv(GL_FRONT, GL_SHININESS, matrial_0_shininess);
}


void walk_front(){
    
    GLfloat xtmp = (cam2x - camx)/200;
    GLfloat ztmp = (cam2z - camz)/200;
    
    camx += xtmp; cam2x += xtmp;
    camz += ztmp; cam2z += ztmp;
    
    //걸을 때 위아래로 흔들리는 시야를 표현
    camy += camy_mark * 0.015;
    cam2y += camy_mark * 0.015;
    if(camy >= 0.28 || camy <= 0.2)
        camy_mark = -camy_mark;
}

void turn_left(){
    // 초점을 반시계 방향으로 돌리는 함수
    GLfloat x = cam2x - camx;
    GLfloat z = cam2z - camz;
    
    if(0 < x && - 14 < z && z <= 0){ //앞 -> 왼
        cam2x -= 1;
        cam2z -= 1;
    }else if(- 14 < x && x <= 0 && z < 0){ // 왼 -> 뒤
        cam2x -= 1;
        cam2z += 1;
    }else if(x < 0 && 0 <= z && z < 14){ // 뒤 -> 오
        cam2x += 1;
        cam2z += 1;
    }else if( 0 <= x && x < 14 && 0 < z){ // 오 -> 앞
        cam2x += 1;
        cam2z -= 1;
    }else{
        //float 형의 자릿수 한계로 발생하는 오류 해결
        camx = round(camx);
        cam2x = round(cam2x);
        camz = round(camz);
        cam2z = round(cam2z);
        if(x > 14)  {
            cam2x = camx + 14;
            cam2z = camz;
        }
        if(x < -14) {
            cam2x = camx - 14;
            cam2z = camz;
        }
        if(z > 14)  {
            cam2z = camz + 14;
            cam2x = camx;
        }
        if(z < -14) {
            cam2z = camz - 14;
            cam2x = camx;
        }
    }
}
void turn_right(){
    // 초점을 시계 방향으로 돌리는 함수
    GLfloat x = cam2x - camx;
    GLfloat z = cam2z - camz;
    
    if(0 < x && 0 <= z && z < 14){ // 앞 -> 오
        cam2x -= 1;
        cam2z += 1;
    }else if(-14 < x && x <= 0 && 0 < z){ // 오 -> 뒤
        cam2x -= 1;
        cam2z -= 1;
    }else if(x < 0 && -14 < z && z <= 0){ // 뒤 -> 왼
        cam2x += 1;
        cam2z -= 1;
    }else if(x >= 0 && x < 14 && z < 0){
        cam2x += 1;
        cam2z += 1;
    }else{
        //float 형의 자릿수 한계로 발생하는 오류 해결
        camx = round(camx);
        cam2x = round(cam2x);
        camz = round(camz);
        cam2z = round(cam2z);
        if(x > 14)  {
            cam2x = camx + 14;
            cam2z = camz;
        }
        if(x < -14) {
            cam2x = camx - 14;
            cam2z = camz;
        }
        if(z > 14)  {
            cam2z = camz + 14;
            cam2x = camx;
        }
        if(z < -14) {
            cam2z = camz - 14;
            cam2x = camx;
        }
    }
}

void myKeyboard(unsigned char KeyPressed, int x, int y){
    switch (KeyPressed){
        case 'w':
            walk_front();
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

void display_objs(CModel m){
    GLfloat x, y, z, nx, ny, nz;
    int v_id, vt_id, vn_id;

    //여러 오브젝트를 나타내 보자
    for(int o = 0; o< m.objs.size(); o++){
        unsigned long nFaces = m.objs[o].f.size();

        //obj가 하나일 때 가정
        for(int k = 0; k < nFaces; k++){
            unsigned long nPoints = m.objs[o].f[k].v_pairs.size();
            glBegin(GL_POLYGON);
            for(int i = 0; i< nPoints; i++){
                v_id = m.objs[o].f[k].v_pairs[i].d[0];
                vt_id = m.objs[o].f[k].v_pairs[i].d[1];
                vn_id = m.objs[o].f[k].v_pairs[i].d[2];
                x = m.objs[o].v[v_id - 1].d[0];
                y = m.objs[o].v[v_id - 1].d[1];
                z = m.objs[o].v[v_id - 1].d[2];

                //법선 벡터
                nx = m.objs[o].vn[vn_id - 1].d[0];
                ny = m.objs[o].vn[vn_id - 1].d[1];
                nz = m.objs[o].vn[vn_id - 1].d[2];
                glNormal3f(nx, ny, nz);
                glVertex3f(x,y,z);
            }
            glEnd();
        }


    }
}
