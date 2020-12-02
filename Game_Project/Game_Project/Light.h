#ifndef Light_h
#define Light_h
void init_light(){
    glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
}
// 손전등
void set_spotlight(){
    GLfloat light_1_pos[] = {0.1, 0.4, 5.0, 1.0}; // 왼오35 / 위아래30 / 앞뒤 -10
    GLfloat light_1_ambient[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_1_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_1_specaular[] = {1.0, 1.0, 1.0, 1.0};
        GLfloat light_1_dir[] = {0.0, -0.1, -1.0};
    GLfloat SpotAngel[] = {5.0};
    GLfloat SpotExp1[] = {2.0}; //흐려짐
    
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
void set_light(){
    //빛의 색상 & 위치 정의
    GLfloat light_0_pos[] = {2.0, 2.0, 2.0, 1.0};
    GLfloat light_0_ambient[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_0_diffuse[] = {0.1, 0.1, 0.7, 1.0};
    GLfloat light_0_specular[] = {1.0, 1.0, 1.0, 1.0};
    
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_global_ambient);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_0_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_0_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_0_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_0_pos);
}

void set_material_color(){
    GLfloat material_0_ambient[] = { 0.2,0.2,0.2,1.0 };
        GLfloat material_0_diffuse[] = { 0.2,0.2,0.5,1.0 };
        GLfloat material_0_specular[] = { 0.5,0.5,0.5,1.0 };
        GLfloat material_0_shininess[] = { 20.0 }; // 0~ 128
        GLfloat meterial_0_emission[] = { 0.0,0.0,0.1,1.0 };
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, material_0_ambient);
    glMaterialfv(GL_FRONT,GL_AMBIENT, material_0_ambient);
    glMaterialfv(GL_FRONT,GL_DIFFUSE, material_0_diffuse);
    glMaterialfv(GL_FRONT,GL_SPECULAR, material_0_specular);
    glMaterialfv(GL_FRONT,GL_SHININESS, material_0_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, meterial_0_emission);
    
}

#endif /* Light_h */
