#ifndef CallBack_h
#define CallBack_h
void reshape(int width, int height);
void myTimer(int value);

void reshape(int width, int height){
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    GLfloat ratio = (float)width/height;
    gluPerspective(40, ratio, 0.1, 1000);
}

bool init = true;
void myTimer(int value) {
    // 한걸음 걷기
    walkFront();
    walkValid();
    walk_front_cnt++;
    
    if (walk_front_cnt < 12)glutTimerFunc(10, myTimer, 1);
    else walk_front_cnt = 0;
    glutPostRedisplay();
}
#endif /* CallBack_h */
