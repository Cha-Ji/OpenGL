#ifndef Light_h
#define Light_h
//조명 변수
GLfloat light_global_ambient[] = {-0.2, 0, -0.1, 1.0}; //전역 조명
bool light_tmp = true; //손전등 온오프

void initLight(){
    glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
}
// 손전등 : 획득하면 키고 끌 수 있다.
void setSpotLight(){
    GLfloat light_1_pos[] = {0.3, 0.0, 70.0, 1.0};
    GLfloat light_1_ambient[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_1_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_1_specaular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_1_dir[] = {0.0, 0.0, -2.0};
    GLfloat SpotAngel[] = {1.0};
    GLfloat SpotExp1[] = {2.0}; //흐려짐
    
    glEnable(GL_RESCALE_NORMAL);
    
    if(light_tmp)
        glEnable(GL_LIGHT1);
    else
        glDisable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_AMBIENT, light_1_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_1_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_1_specaular);
    glLightfv(GL_LIGHT1, GL_POSITION, light_1_pos);
    
    glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, SpotAngel);
    glLightfv(GL_LIGHT1, GL_SPOT_EXPONENT, SpotExp1);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light_1_dir);
}
void setLight(){
    //빛의 색상 & 위치 정의
    GLfloat light_0_pos[] = {2.0, 2.0, -2.0, 1.0};
    GLfloat light_0_ambient[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_0_diffuse[] = {0.3, 0.3, 1.0, 1.0};
    GLfloat light_0_specular[] = {1.0, 1.0, 1.0, 1.0};
    
    
    glEnable(GL_RESCALE_NORMAL);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_0_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_0_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_0_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_0_pos);
}
void setMaterialColor(){
    GLfloat material_0_ambient[] = { 0.2,0.2,0.2,1.0 };
    GLfloat material_0_diffuse[] = { 0.2,0.2,0.5,1.0 };
    GLfloat material_0_specular[] = { 1.0,1.0,1.0,1.0 };
    GLfloat material_0_shininess[] = { 10.0 }; // 0~ 128
    GLfloat meterial_0_emission[] = { 0.0,0.0,0.1,1.0 };
    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_RESCALE_NORMAL);
    glMaterialfv(GL_FRONT, GL_AMBIENT, material_0_ambient);
    glMaterialfv(GL_FRONT,GL_DIFFUSE, material_0_diffuse);
    glMaterialfv(GL_FRONT,GL_SPECULAR, material_0_specular);
    glMaterialfv(GL_FRONT,GL_SHININESS, material_0_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, meterial_0_emission);
    
}
//엔딩 조명
void exitLight(){
    //빛의 색상 & 위치 정의
    GLfloat light_0_pos[] = {30, 0.0, 70.0, 1.0};
    GLfloat light_0_ambient[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_0_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_0_specular[] = {1.0, 1.0, 1.0, 1.0};
    
    
    glEnable(GL_RESCALE_NORMAL);
    glEnable(GL_LIGHT2);
    glLightfv(GL_LIGHT2, GL_AMBIENT, light_0_ambient);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, light_0_diffuse);
    glLightfv(GL_LIGHT2, GL_SPECULAR, light_0_specular);
    glLightfv(GL_LIGHT2, GL_POSITION, light_0_pos);
}
#endif /* Light_h */
