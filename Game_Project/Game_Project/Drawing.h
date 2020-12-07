#ifndef Drawing_h
#define Drawing_h
void drawHand();            //손 그리기
void drawHandLight();       //손전등을 쥔 손 그리기

void drawHand(){
    glPushMatrix();
        glTranslated(hand_pos_x + camx, 0, hand_pos_z + camz);
        glRotated(-90 + hand_angle, 0, 1, 0);
        glTranslated(hand_turn_z, 0, hand_turn_x);
        glScalef(0.1, 0.1, 0.1);
        displayHand();
    glPopMatrix();
}
void drawHandLight(){
    glPushMatrix();
        glTranslated(hand_pos_x + camx, 0, hand_pos_z + camz);
        glRotated(-90 + hand_angle, 0, 1, 0);
        glTranslated(hand_turn_z, 0, hand_turn_x);
        glScalef(0.1, 0.1, 0.1);
        displayHandLight();
    glPopMatrix();
}
#endif /* Drawing_h */
