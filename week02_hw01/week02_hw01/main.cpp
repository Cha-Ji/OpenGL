// glut 모델링

#include <GLUT/GLUT.h>

void mydisplay(){
    glClear(GL_COLOR_BUFFER_BIT);
    //glutSolidCube(0.3); //큐브
    //glutSolidSphere(1, 10, 10); // 구
    //glutSolidTorus(0.3, 0.3, 10, 50);  //원환체
    //glutSolidTeapot(0.3);    // 찻주전자
    //glutSolidOctahedron();   // 정팔면체
    //glutSolidIcosahedron();    //정이십면체
    //glutSolidTetrahedron();  //정사면체
    //glutSolidDodecahedron(); //정십이면체 : 실패
    glutSolidCone(1, 1, 10, 10); //원뿔
    // 원뿔, 정사면체, 정이십면체 등등 실습해보자.
    
    glFlush();
}
int main(int argc, char* argv[]){
    glutInit(&argc, argv);
    glutCreateWindow("Test");
    glutInitWindowSize(900, 900);
    glutDisplayFunc(mydisplay);
    glutMainLoop();
    return 0;
}

