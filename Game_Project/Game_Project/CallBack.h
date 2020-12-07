#ifndef CallBack_h
#define CallBack_h
int cnt = 0; //좀비 타이머 카운트
//reshape 콜백
void reshape(int width, int height){
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    GLfloat ratio = (float)width/height;
    gluPerspective(40, ratio, 0.1, 1000);
}
//전진 애니메이션
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
//2층 탈출 애니메이션
void exit2Floor(int value){
    getKey = false;
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
        map_num = 1;
    }else if(160 < exit_floor_cnt && exit_floor_cnt < 220){
        light_global_ambient[0] += 0.1;
        light_global_ambient[1] += 0.1;
        light_global_ambient[2] += 0.1;
    }
    
    exit_floor_cnt ++;
    if(exit_floor_cnt < 220){
        glutTimerFunc(10, exit2Floor, 1);
    }else{
        exit_floor_cnt = 0;
        dontTouch = false;  //애니메이션 종료 신호
        map_num = 1;        //2층 맵으로 이동
        //1인칭 시점, 위치 초기화
        camy = 1; cam2y = 0.1; camy_mark = 1;
        hand_angle = 0;
    }
    glutPostRedisplay();
}
//1층 탈출 애니메이션
void exit1Floor(int value){
    //탈출 애니메이션 시작
    if(exit_floor_cnt == 0){
        getKey = false;
        dontTouch  = true;
        hand_angle = 0;
        light_tmp = true;
        camx = 32; cam2x = 45;
        camz = -5; cam2z = -2;
    }
    
    exit_floor_cnt ++;
    if (exit_floor_cnt < 150){
        camx += 0.2; cam2x += 0.2;
        camy += camy_mark * 0.05;
        cam2y += camy_mark * 0.05;
        if(camy >= 1.1 || camy <= 0.8)
            camy_mark = -camy_mark;
        
        glutTimerFunc(10, exit1Floor, 2);
        
    }else if(exit_floor_cnt == 150){
        glutTimerFunc(10, exit1Floor, 2);
        ending = true;
        cam2y = 3; camz --;
        init_texture();
    }else if(exit_floor_cnt < 300){
        cam2x -= 0.3;
        cam2z -= 0.15; camz -= 0.15;
        camy += 0.15;
        glutTimerFunc(10, exit1Floor, 2);
    }
    else{
        exit_floor_cnt = 0;
        dontTouch = false;
    }
    glutPostRedisplay();
}
//좀비 등장 씬
void zombieTimer(int value){
    inZombieRoom = true;
    cnt ++;
    if(cnt <= 100)
        glutTimerFunc(40, zombieTimer, 4);
    else{
        inZombieRoom = false;
        glDisable(GL_TEXTURE_2D);
        glutPostRedisplay();
    }
    
}
void mydisplay(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    //손전등 설정
    glPushMatrix();
        setSpotLight();
    glPopMatrix();
    
    //카메라 뷰 설정
    gluLookAt(camx, camy, camz,
              cam2x, cam2y, cam2z,
              cam_upx, cam_upy, cam_upz);
    
    /*========그리기 시작========*/
    //초기위치 설정
    glTranslated(-15, -0.5, 0);
    glPushMatrix();
    //3층 맵
    setLight();
    setMaterialColor();
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_global_ambient);
    
    if(ending){
        exitLight();
        glPushMatrix();
        glTranslatef(0, 0, -20);
        displayEnding();
        glPopMatrix();
        glClearColor(0.6, 0.8, 1, 1);
    }else if(map_num == 0){
        display2Floor();
        
        //열쇠 위치 설정
        glPushMatrix();
            glTranslated(13, 1.5, -10);
            glRotated(90, 1, 0, 0);
            if(!getKey)displayKey();
        glPopMatrix();
        
        //시체 놀래키기
        glPushMatrix();
            if(inZombieRoom)displayZombie();
        glPopMatrix();
    }
    //2층 맵
    else if(map_num == 1){
        display1Floor();
        //열쇠 위치 설정
        if(!getKey){
            glPushMatrix();
                glTranslated(35, 1.5, 4);
                glRotated(30, 3, 0, 0);
                displayKey();
            glPopMatrix();
        }
    }
    
    //탈출 맵
    
    
        //손 그리기
    if(!light_tmp)drawHand();
    else if(light_tmp && !ending)drawHandLight();
    glPopMatrix();
    glFlush();
}
void myKeyboard(unsigned char KeyPressed, int x, int y){
    if(!dontTouch){
        switch (KeyPressed){
                //전진
            case 'w':
                if(!walkValid() && walk_front_cnt == 0)
                    glutTimerFunc(10, walkFrontTimer, 1);
                break;
                //왼쪽 회전
            case 'a':
                turnLeft();
                break;
                //오른쪽 회전
            case 'd':
                turnRight();
                break;
                
                
            case 'l':
                light_tmp = !light_tmp;
                break;
            //검사용
            case 'z':
                glutTimerFunc(40, exit1Floor, 2);
                break;

            case'x':
                glutTimerFunc(40, exit2Floor, 1);
                break;
            case'c':
                getKey = true;
                break;

            case 'm':
                printf("x : %f, 2x : %f, z : %f, 2z : %f\n",camx, cam2x, camz, cam2z);
                printf("r : %f g : %f b :%f \n",light_global_ambient[0],light_global_ambient[1],light_global_ambient[2]);
                break;
            case 'k':
                if(keyArea()) {
                    getKey = true;
                    glutTimerFunc(40, zombieTimer, 4);
                }
                break;
        }
    }
    glutPostRedisplay();
}
void initGame(){
    image = imread(filePath + "zombie.jpg",IMREAD_COLOR);
    cvtColor(image,image, COLOR_BGR2RGB);

    image2 = imread(filePath + "end_map.jpg",IMREAD_COLOR);
    cvtColor(image2,image2, COLOR_BGR2RGB);
    
    ifstream fin(filePath + "floor2.obj");
    floor2.loadObj(fin);
    fin.close();
    
    ifstream fin2(filePath + "floor1.obj");
    floor1.loadObj(fin2);
    fin2.close();
    
    ifstream fin3(filePath + "key.obj");
    key.loadObj(fin3);
    fin3.close();
    
    ifstream fin4(filePath + "hand.obj");
    hand.loadObj(fin4);
    fin4.close();
    
    ifstream fin5(filePath + "hand_light.obj");
    hand_light.loadObj(fin5);
    fin5.close();
    
    ifstream fin6(filePath + "human.obj");
    zombie.loadObj(fin6);
    fin6.close();
    
    ifstream fin7(filePath + "end_map.obj");
    end_map.loadObj(fin7);
    fin7.close();
    
    //gl 관련
    glutCreateWindow("Escape Here");
    glClearColor(0.1, 0.3, 0.5, 1.0);   //R, G, B, A(투명도)
    init_texture();
    initLight();
    glutDisplayFunc(mydisplay);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(myKeyboard);
        glutMainLoop();
        
}


#endif /* CallBack_h */
