#ifndef Walking_h
#define Walking_h
void walk_front(){
    GLfloat xtmp = (cam2x - camx)/100;
    GLfloat ztmp = (cam2z - camz)/100;
    
    camx += xtmp; cam2x += xtmp;
    camz += ztmp; cam2z += ztmp;
    
    //걸을 때 위아래로 흔들리는 시야를 표현
    camy += camy_mark * 0.015; cam2y += camy_mark * 0.015;
    if(camy >= 1.1 || camy <= 1) camy_mark = -camy_mark;
}

void turn_left(){
    // 초점을 반시계 방향으로 돌리는 함수
    GLfloat x = cam2x - camx;
    GLfloat z = cam2z - camz;
    
    hand_angle += 90/14.0;
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
        camx = round(camx);cam2x = round(cam2x);
        camz = round(camz);cam2z = round(cam2z);
        if(x > 14)  {
            cam2x = camx + 14; cam2z = camz;
            hand_angle = 0;
        }if(x < -14) {
            cam2x = camx - 14; cam2z = camz;
            hand_angle = 180;
        }if(z > 14)  {
            cam2z = camz + 14; cam2x = camx;
            hand_angle = 270;
        }if(z < -14) {
            cam2z = camz - 14; cam2x = camx;
            hand_angle = 90;
        }
    }
    
}
void turn_right(){
    // 초점을 시계 방향으로 돌리는 함수
    GLfloat x = cam2x - camx;
    GLfloat z = cam2z - camz;
    hand_angle -= 90/14.0;
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
        camx = round(camx);cam2x = round(cam2x);
        camz = round(camz);cam2z = round(cam2z);
        if(x > 14)  {
            cam2x = camx + 14; cam2z = camz;
            hand_angle = 0;
        }if(x < -14) {
            cam2x = camx - 14; cam2z = camz;
            hand_angle = 180;
        }if(z > 14)  {
            cam2z = camz + 14; cam2x = camx;
            hand_angle = 270;
        }if(z < -14) {
            cam2z = camz - 14; cam2x = camx;
            hand_angle = 90;
        }
    }
}


#endif /* Walking_h */
