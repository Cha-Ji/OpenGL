#include "Header.h"         //라이브러리, 함수, 전역변수 선언
#include "Light.h"          //조명 함수
#include "Walking.h"        //주인공의 움직임
#include "load_object.h"    //obj파일을 불러오고 그린다.
#include "CallBack.h"       //타이머 & reshape콜백 함수
#include "Intro.h"          //opencv로 게임 시작 인트로 그리기

/* intro -> initGame -> display2floor
 -> exit2floor -> display1floor -> exit1floor
 */
int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_SINGLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(300, 200);
    drawIntro();
    
    return 0;
}



