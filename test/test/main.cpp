#include <GLUT/glut.h>
#include <stdio.h>

#define _WINDOW_WIDTH 500
#define _WINDOW_HEIGHT 500

GLfloat camx = 0, camy = 5, camz = -4;
GLfloat cam2x = 0, cam2y = 0, cam2z = 10;
GLfloat cam_upx = 0, cam_upy = 1, cam_upz = 0;

void reshape(int width, int height) {
   glViewport(0, 0, width, height);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   GLfloat ratio = (float)width / height;
   gluPerspective(40, ratio, 0.1, 1000);
}

void drawRect(GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat r, GLfloat g, GLfloat b) {
   glColor3f(r, g, b);
   glBegin(GL_POLYGON);
   glVertex3f(x, y, z);
   glVertex3f(x + width, y, z);
   glVertex3f(x + width, y, z + width);
   glVertex3f(x, y, z + width);
   glEnd();
}

void drawBlackWhiteRect(GLint nx, GLint nz, GLint sx, GLint sy, GLint sz, GLfloat w, int bBlack) {
   GLfloat x, y, z;
   x = sx + nx * w;
   y = sy;
   z = sz + nz * w;
   if (bBlack)
      drawRect(x, y, z, w, 0.0, 0.0, 0.0);
   else
      drawRect(x, y, z, w, 1.0, 1.0, 1.0);
}

void display() {
   glClear(GL_COLOR_BUFFER_BIT);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt(camx, camy, camz, cam2x, cam2y, cam2z, cam_upx, cam_upy, cam_upz);

   //glShadeModel(GL_SMOOTH);
   glDisable(GL_DEPTH_TEST);

   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   glEnable(GL_POLYGON_SMOOTH);
   //glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
   glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

   for(int i = 0; i < 1000; i++)
      for (int j = 0; j < 1000; j++) {
         int bBlack = (i + j) % 2;
         drawBlackWhiteRect(i, j, -10, 0, 0, 0.2, bBlack);
      }
   glDisable(GL_BLEND);

   glFlush();
}

int main(int argc, char** argv) {
   glutInit(&argc, argv);
   
   glutInitDisplayMode(GLUT_RGB);
   glutInitWindowSize(_WINDOW_WIDTH, _WINDOW_HEIGHT);
   glutInitWindowPosition(0, 0);

   glutCreateWindow("Anti-Aliasing");

   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutMainLoop();
   return 0;
}
