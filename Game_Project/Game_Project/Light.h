#ifndef Light_h
#define Light_h
void init_light(){
    glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
}
void set_spotlight(){
    //==============sportlight 추가===========

    GLfloat light_0_ambient[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_0_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_0_specaular[] = {1.0, 1.0, 1.0, 1.0};

    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_AMBIENT, light_0_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_0_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_0_specaular);

        //광원의 위치, 방향, spotlight
    GLfloat light_1_pos[] = {-10.0, 1.0, -15.0, 1.0};
    GLfloat light_1_dir[] = {0.5, 0.1, 0.5, 1.0};
    GLfloat SpotAngel[] = {30.0};
    glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, SpotAngel);

        //흐려짐
    GLfloat SpotExp1[] = {1.0};
    glLightfv(GL_LIGHT1, GL_SPOT_EXPONENT, SpotExp1);
    glLightfv(GL_LIGHT1, GL_POSITION, light_1_pos);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light_1_dir);


//    ====================================
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
    //물체 색상 정의 & 지정
//    GLfloat material_0_ambient[] = {0.3, 0.3, 0.3, 1.0};
//    GLfloat material_0_diffuse[] = {0.8, 0.0, 0.3, 1.0};
//    GLfloat material_0_specular[] = {1.0, 1.0, 1.0, 1.0};
//    GLfloat material_0_shininess[] = {10.0};
//    GLfloat meterial_0_emission[] = { 0.0,0.0,1.0,1.0 };
    GLfloat material_0_ambient[] = { 0.2,0.2,0.2,1.0 };
        GLfloat material_0_diffuse[] = { 0.2,0.2,0.5,1.0 };
        GLfloat material_0_specular[] = { 0.5,0.5,0.5,1.0 };
        GLfloat material_0_shininess[] = { 20.0 }; // 0~ 128
        GLfloat meterial_0_emission[] = { 0.0,0.0,0.1,1.0 };
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, material_0_ambient);
//    glLightfv(GL_FRONT, GL_DIFFUSE, matrial_0_diffuse);
//    glLightfv(GL_FRONT, GL_SPECULAR, matrial_0_specular);
//    glLightfv(GL_FRONT, GL_SHININESS, matrial_0_shininess);
    glMaterialfv(GL_FRONT,GL_AMBIENT, material_0_ambient);
    glMaterialfv(GL_FRONT,GL_DIFFUSE, material_0_diffuse);
    glMaterialfv(GL_FRONT,GL_SPECULAR, material_0_specular);
    glMaterialfv(GL_FRONT,GL_SHININESS, material_0_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, meterial_0_emission);
    
}






#endif /* Light_h */
