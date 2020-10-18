#define GL_SILENCE_DEPRECATION
#include <GLUT/GLUT.h>
#include <math.h>
#include <stdio.h>
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800


GLfloat camx = 0.5, camy = 1, camz = 1.5;
GLfloat cam2x = 0, cam2y = 0, cam2z = 0;
GLfloat cam_upx = 0, cam_upy = 1, cam_upz = 0;

void InitLight() {
   GLfloat mat_diffuse[] = { 0.5, 0.4, 0.3, 1.0 };
   GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat mat_ambient[] = { 0.5, 0.4, 0.3, 1.0 };
   GLfloat mat_shininess[] = { 50, 0 };
   GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat light_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
   GLfloat light_ambient[] = { 0.3, 0.3, 0.3, 1.0 };
   GLfloat light_position[] = { -3, 2, 3.0, 0.0 };
   glShadeModel(GL_SMOOTH);
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glLightfv(GL_LIGHT0, GL_POSITION, light_position);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
   glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
   glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

void InitVisibility() {
   //glEnable(GL_CULL_FACE);
   glDisable(GL_CULL_FACE);
   glPolygonMode(GL_FILL, GL_FILL);
   glPolygonMode(GL_BACK, GL_LINE);
   
   
   glFrontFace(GL_CW);
   //glCullFace(GL_BACK);
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_CLIP_PLANE0);
   glEnable(GL_CLIP_PLANE1);
//   glEnable(GL_CLIP_PLANE2);
}

void Mydisplay() {
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   gluLookAt(camx, camy, camz,
      cam2x, cam2y, cam2z,
      cam_upx, cam_upy, cam_upz);
//   GLdouble eq2[4] = { 0, 0, 1, 0 };
//   glClipPlane(GL_CLIP_PLANE2, eq2);
   GLdouble eq[4] = { 0.5, 0.5, 1, 0 };   // y = 0 plane
   glClipPlane(GL_CLIP_PLANE0, eq);
   GLdouble eq1[4] = { 0.5, 0.5, -1, 0 };
   glClipPlane(GL_CLIP_PLANE1, eq1);

   glutSolidTeapot(0.2);
   glutSwapBuffers();
}

void Myreshape(int width, int height) {
   GLfloat left = 0, bottom = 0;
   glViewport(left, bottom, width - left, height - bottom);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   GLfloat ratio = (float)(width - left) / (height - bottom);
   gluPerspective(40, ratio, 0.1, 10);
}

void Mytimer(int value) {
   GLfloat theta = 0.01;
   GLfloat tmp_x = camx;
   camx = camx * cos(theta) + camz * sin(theta);
   camz = -tmp_x * sin(theta) + camz * cos(theta);

   glutTimerFunc(20, Mytimer, 1);
   glutPostRedisplay();
}
int main(int argc, char** argv) {
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
   glutInitWindowSize(700, 700);
   glutInitWindowPosition(50, 50);
   glutCreateWindow("Week 7");
   glClearColor(0.0, 0.0, 0.0, 0.0);
   InitLight();
   InitVisibility();
   glutDisplayFunc(Mydisplay);
   glutReshapeFunc(Myreshape);
   glutTimerFunc(20, Mytimer, 1);
   int num;
   glGetIntegerv(GL_MAX_CLIP_PLANES, &num);
   printf("number of Clip planes%d", num);

   glutMainLoop();
   return 0;

}
