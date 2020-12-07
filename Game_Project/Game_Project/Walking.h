#ifndef Walking_h
#define Walking_h
// 동작 변수
int walk_front_cnt = 0;  //걷기 타이머의 카운터
// 걷는 거리
GLfloat walk_xstep;
GLfloat walk_zstep;
//손의 움직임
GLfloat hand_pos_x = 15.2, hand_pos_z = 0;
GLfloat hand_turn_x = -2.8, hand_turn_z = 0;
GLfloat hand_angle = 0;

void walkFront();   //전진
bool walkValid();   //전진 제한
bool isHurdle();    //장애물이 있는지 체크
bool canPass();     //통과할 수 있는 곳 예외
void turnLeft();    //반시계 방향 회전
void turnRight();   //시계 방향 회전

void walkFront(){
    //camx, camy, camz를 1인칭 주인공 위치라고 본다.
    //cam2x, cam2y cam2z를 쳐다보는 초점이라고 본다.
    //이동 속도를 일정하게 한다.
    walk_xstep = (cam2x - camx)/100;
    walk_zstep = (cam2z - camz)/100;
    
    //초점과 주인공 위치의 거리를 일정하게 더해서
    //이동 속도를 일정할 수 있게 만든다.
    camx += walk_xstep; cam2x += walk_xstep;
    camz += walk_zstep; cam2z += walk_zstep;
    
    //걸을 때 위아래로 흔들리는 시야를 표현
    camy += camy_mark * 0.015;
    cam2y += camy_mark * 0.015;
    if(camy >= 1.1 || camy <= 1)
        camy_mark = -camy_mark;
}

void turnLeft(){
    // 초점을 반시계 방향으로 돌리는 함수
    GLfloat x = cam2x - camx;
    GLfloat z = cam2z - camz;
    
    // 손은 항상 앞에 있다.
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
void turnRight(){
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
        if(x >= 14)  {
            cam2x = camx + 14; cam2z = camz;
            hand_angle = 0;
        }if(x <= -14) {
            cam2x = camx - 14; cam2z = camz;
            hand_angle = 180;
        }if(z >= 14)  {
            cam2z = camz + 14; cam2x = camx;
            hand_angle = 270;
        }if(z <= -14) {
            cam2z = camz - 14; cam2x = camx;
            hand_angle = 90;
        }
    }
}

bool walkValid(){
    //지나갈 수 없는 곳
    if(canPass()) return false;
//    왼쪽 벽
    else if(camz < -1.7 && cam2z < -2)return true;
    else if(camz < -2)return true;
//    오른쪽 벽
    else if(camz > 1 && cam2z > 1.5)return true;
    else if(camz > 2)return true;
    // 앞쪽 벽
    else if(camx >= 23 && cam2x >= 35) return true;
    
    // 뒤쪽 벽
    else if(camx <= -24 && cam2x <= -35) return true;
    
    // 의자에 걸릴 때
    else if(isHurdle()){
        if(cam2x < 0){
            camx += 0.1;cam2x += 0.1;
        }else{
            camx -= 0.1;cam2x -= 0.1;
        }
        return true;
    }
    
    return false;
}

bool isHurdle(){
        // 첫 번째 의자
        if(-16 <= camx && camx <= -15
            && -3 <= camz && camz <= 0){ //의자 위치
            if(-32 < cam2x&& cam2x < 0
               && cam2z < 0)  //시점
                return true;
            if(-27 < cam2x && cam2x <= -9
               && -15 < cam2z && cam2z <= -5)
                return true;
        }
        //두 번째 의자 쌍
        if(-7 <= camx && camx <= -2.5
            && -0.5 <= camz && camz <= 1.5){//의자 위치
            if(-13 <= cam2x && cam2x <= 6
               && 0 <= cam2z && cam2z <= 15)// 시점
                return true;
            if(cam2x <= -17
               && cam2z >= 1.5)
                return true;
        }
        
        //세 번째 의자
        if(-3 <= camx && camx <= 0
            && -2 <= camz && camz <= -1){
            if(cam2x <= 10 && cam2z <= 1)
                return true;
        }
        //네 번째 의자
        if(10 <= camx && camx <= 15
           && -1 <= camz && camz <= 1.5){
            if(cam2x >= -1 && cam2x <= 25
                   && -0.5<= cam2z && camz <= 13)
                return true;
        }
    return false;
}
bool canPass(){// 통과할 수 있는 방이나 복도
    if(map_num == 0){
        //첫 번째 방 입장
        if(-2 <= camz && camz <= -1.7 && cam2z < -12.5 &&
           -11.5 <= camx && camx <= -10.5)
            return true;
        // 방 구경
        if(-13 <= camx && camx <= -9
           && -9 <= camz && camz < -2){
            //가로막힌 벽
            if(camz <= -8.5 && cam2z <= -18.0)
                return false;
            if(camx <= -12 && cam2x <= -24)
                return false;
            if(camx >= -8.5 && cam2x >= 3.5)
                return false;
            return true;
        }
        // 방 탈출
        if(-2 <= camz && camz <= -1.7 && cam2z >= 11
           && -11.5 <= camx && camx <= -10.5)
            return true;
        
        
        //두번째 방 입장
        if(-2 <= camz && camz <= -1.7 && cam2z < -10
           && -4.5 <= camx && camx <= -2.5){
            return true;
        }
        // 방 구경
        if(-5 <= camx && camx <= -2
           && -9 <= camz && camz < -2){
            //가로막힌 벽
            if(camz <= -8.5 && cam2z <= -18.0)
                return false;
            if(camx <= -4.5 && cam2x <= -14)
                return false;
            return true;
        }

        
        //세 번째 방
        if(-2 <= camz && camz <= -1.7 && cam2z < -11.5
            && 2.5 <= camx && camx <= 3.5)
            return true;
        // 방 구경
        if(2.5 <= camx && camx <= 6.5
           && -9 <= camz && camz < -2){
            //가로막힌 벽
            if(camz <= -8.5 && cam2z <= -18.0)
                return false;
            if(camx <= 3 && cam2x <= -7)
                return false;
            if(camx >= 6 && cam2x >= 19)
                return false;
            return true;
        }

        //오른쪽 줄 방
        //첫 번째 방 입장
        if(1<= camz && camz <= 3 && cam2z >= 9 &&
           -12 <= camx && camx <= -10)
            return true;
        // 방 구경
        if(-18 <= camx && camx <= -9
           && 3 <= camz && camz < 8){
            //가로막힌 벽
            if(camz >= 7 && cam2z >= 11.0)
                return false;
            if(camx <= -17 && cam2x <= -30)
                return false;
            if(camx >= -8.5 && cam2x >= 0)
                return false;
            if(camz <= 3.5 && cam2z < -3
               && camx <= -12)
                return false;
            return true;
        }
        // 방 탈출
        if(2 <= camz && camz <= 3.5 && cam2z <= -5
           && camx >= -11 && camx <= -10)
            return true;
        
        
        //두번째 방 입장
        if(1 <= camz && camz <= 3 && cam2z >= 7
           && 9.5 <= camx && camx <= 11)
            return true;
        // 방 구경
        if(9.5 <= camx && camx <= 17
           && 2 <= camz && camz <= 9){
            //가로막힌 벽
            if(camz >= 8.5 && cam2z >= 12.0)
                return false;
            
            if(camx >= 14 && cam2z < 0)
                return false;
            if(camx <= 10.5 && cam2x <= 9)
                return false;
            return true;
        }

        
        //휴게실
        if(18 <= camx && camx <= 24){
            if(-8 <= camz && camz <= 1)
                return true;
            if(2 <= camz && camz <= 8)
                return true;
        }
        
        //출구
        if(-24 < camx && camx < -19){
            //탈출
            if(camz >= 11){
                if(getKey && exit_floor_cnt == 0){
                    getKey = false;
                    glutTimerFunc(10, exit2Floor, 1);
                }
                    
                else{
                    camz -= 1;
                    return false;
                }
            }
            if(camz <= -7)
                return false;
            //출구 안
            if(camz >= 13 && cam2z >= 20) return false;
            return true;
        }
       
    }
    if(map_num == 1){
        //왼쪽 방
        if(-2 <= camz && camz <= -1.7 && cam2z < -11.5
            && 10 <= camx && camx <= 12.5)
            return true;
        // 방 구경
        if(10 <= camx && camx <= 16
           && -9 <= camz && camz < -2){
            //가로막힌 벽
            if(camz <= -8.5 && cam2z <= -18.0)
                return false;
            if(camx <= 11 && cam2x <= -7)
                return false;
            if(camx >= 15 && cam2x >= 26)
                return false;
            return true;
        }
        if(-3.5 <= camz && camz <= -2 && cam2z >= 3
           && camx >= 10.5 && camx <=11.5 )
            return true;

        
        //오른쪽 줄 방
        //첫 번째 방 입장 엑스레이방
        if(1<= camz && camz <= 3 && cam2z >= 9 &&
           -12 <= camx && camx <= -10)
            return true;
        // 방 구경 -18
        if(-18 <= camx && camx <= -9
           && 3 <= camz && camz < 8){
            //가로막힌 벽
            if(camz >= 7 && cam2z >= 11.0)
                return false;
            if(camx <= -17 && cam2x <= -30)
                return false;
            if(camx >= -8.5 && cam2x >= 0)
                return false;
            if(camz <= 3.5 && cam2z < -3
               && camx <= -12)
                return false;
            return true;
        }
        
        // 방 탈출
        if(2 <= camz && camz <= 3.5 && cam2z <= -5
           && camx >= -11 && camx <= -10)
            return true;
        
        
        //두번째 방 입장
        if(1 <= camz && camz <= 3 && cam2z >= 8.5
           && 2.5 <= camx && camx <= 4.5)
            return true;
        // 방 구경
        if(2 <= camx && camx <= 8
           && 3 <= camz && camz <= 9){
            //가로막힌 벽
            if(camz >= 8.5 && cam2z >= 20.0)
                return false;
            if(camx <= 3.5 && cam2x < 0)
                return false;
            if(camx >= 7 && cam2x >= 12)
                return false;
            if(3.5 <= camz && camz <= 4 && cam2z < 0
               && 4.5 <=camx)
                return false;
            return true;
        }

        //방 탈출
        if(2.5 <= camx && camx <= 4.5
           && cam2z < -7)
            return true;
        
        //로비
        if(20 <= camx && camx <= 33){
            if(31<= camx && camx <= 33
               && -5 <= camz && camz <= -4)
                if(getKey){
                    getKey = false;
                    glutTimerFunc(10, exit1Floor, 2); //탈출
                }
            if(camx >= 32 && cam2x >= 38)
                return false;
            if(-9 <= camz && camz <= 0)
                return true;
            if(1 <= camz && camz <= 5){
                if(camz >= 4 && cam2z >= 17)
                    return false;
                else
                    return true;
            }
        }
    }
    return false;
}
#endif /* Walking_h */
