#ifndef CallBack_h
#define CallBack_h
void reshape(int width, int height);
void walkFrontTimer(int value);     //1번 걷는 애니메이션
void exit3Floor(int value);         // 3층 탈출 애니메이션

void reshape(int width, int height){
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    GLfloat ratio = (float)width/height;
    gluPerspective(40, ratio, 0.1, 1000);
}

bool init = true;
void walkFrontTimer(int value) {
    // 한걸음 걷기
    if (walk_front_cnt < 12 && !walkValid()){
        walkFront();
        walk_front_cnt++;
        glutTimerFunc(10, walkFrontTimer, 1);
    }
    else{
        walk_front_cnt = 0;
        return;
    }
    glutPostRedisplay();
}
void exit3Floor(int value){
    dontTouch  = true;
    hand_angle = 0;
    //출구의 중심으로 이동
    if(exit_floor_cnt == 0){
        camx = -23; camy = 1; camz = 16;
        cam2x = -37; cam2y = 0.1; cam2z = 14;
    }
    //계단 앞까지 걸어감
    else if(exit_floor_cnt < 50){
        camx -= 0.06; cam2x -= 0.06;
        
        camy += camy_mark * 0.03;
        cam2y += camy_mark * 0.03;
        if(camy >= 1.1 || camy <= 0.9)
            camy_mark = -camy_mark;
        
    }
    //내려다보기
    else if(exit_floor_cnt < 80)cam2y -= 0.1;
    //계단 내려가기
    else if(exit_floor_cnt < 200){
        camx -= 0.02; cam2x -= 0.02;
        
        if(exit_floor_cnt % 10 == 0)
            camy_mark = -camy_mark;
        
        if(camy_mark < 0)
            camy += camy_mark/50.0;
        else
            camy += camy_mark/100.0;
        
    }
    
    //맵 변경을 위해 서서히 어두워짐
    if(100 < exit_floor_cnt &&exit_floor_cnt < 160){
        light_global_ambient[0] -= 0.1;
        light_global_ambient[1] -= 0.1;
        light_global_ambient[2] -= 0.1;
    }else if(exit_floor_cnt == 160){
        //1인칭 시점, 위치 초기화
        camx = -14; camz = 0; cam2y = 0.1;
        cam2x = 0; cam2z = 0;
    }else if(160 < exit_floor_cnt && exit_floor_cnt < 220){
        light_global_ambient[0] += 0.1;
        light_global_ambient[1] += 0.1;
        light_global_ambient[2] += 0.1;
    }
    
    exit_floor_cnt ++;
    if(exit_floor_cnt < 220){
        glutTimerFunc(10, exit3Floor, 1);
        glutPostRedisplay();
    }else{
        exit_floor_cnt = 0;
        dontTouch = false;  //애니메이션 종료 신호
        map_num = 1;        //2층 맵으로 이동
        //1인칭 시점, 위치 초기화
        camy = 1; cam2y = 0.1; camy_mark = 1;
        hand_angle = 0;
        glutPostRedisplay();
    }
        
}
#endif /* CallBack_h */
