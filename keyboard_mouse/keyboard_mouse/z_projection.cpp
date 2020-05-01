//#include "gl/glut.h"
//#include <stdio.h>
//
//void RenderScene(void) {
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	gluLookAt(0.f, 0.f, -80.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f);
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	glPushMatrix();
//	glTranslatef(5.f, -30.f, -30.f);
//	glScaled(2.f, 2.f, 1.f);
//	glBegin(GL_TRIANGLES);
//	glColor3f(1.0f, 0.5f, 0.0f);
//	glVertex3f(-10.f, 0.f, 0.f);
//	glVertex3f(10.f, 0.f, 0.f);
//	glVertex3f(0.f, 20.f, 0.f);
//	glEnd();
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(-5.f, -30.f, 20.f);
//	glScaled(2.f, 2.f, 1.f);
//	glBegin(GL_TRIANGLES);
//	glColor3f(1.0f, 1.0f, 1.0f);
//	glVertex3f(10.f, 0.f, 0.f);
//	glVertex3f(-10.f, 0.f, 0.f);
//	glVertex3f(0.f, 20.f, 0.f);
//	glEnd();
//	glPopMatrix();
//
//	glFlush();
//}
//
//void SetupRC(void) {
//	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//
//	glEnable(GL_DEPTH_TEST);
//}
//
//void ChangeSize(GLsizei w, GLsizei h) {
//	if (h == 0)
//		h = 1;
//
//	glViewport(0, 0, w, h);
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	GLfloat aspectRatio = (GLfloat)w / (GLfloat)h;
//	gluPerspective(90.f, aspectRatio, 10.f, 200.f);
//}
//
//int main(int argc, char* argv[]) {
//	glutInit(&argc, argv);
//
//	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
//	glutCreateWindow("Lec07");
//
//	glutDisplayFunc(RenderScene);
//	glutReshapeFunc(ChangeSize);
//
//	SetupRC();
//	glutMainLoop();
//	return 0;
//}
