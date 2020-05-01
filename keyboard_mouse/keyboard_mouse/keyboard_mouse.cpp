#include "gl/glut.h"
#include <stdio.h>

void RenderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	gluLookAt(0.f, 0.f, -80.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f);

	glFlush();
}

void SetupRC(void) {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glEnable(GL_DEPTH_TEST);
}

void ChangeSize(GLsizei w, GLsizei h) {
	if (h == 0)
		h = 1;

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLfloat aspectRatio = (GLfloat)w / (GLfloat)h;
	gluPerspective(90.f, aspectRatio, 10.f, 200.f);
}

void MenuHandler(int value) {
	switch (value)
	{
	case 13:
		glClearColor(1.f, 0.f, 0.f, 1.f);
		break;
	case 14:
		glClearColor(0.f, 0.f, 1.f, 1.f);
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

void MenuHandler2(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN)
			glClearColor(1.f, 0.f, 0.f, 1.f);
		if (state == GLUT_UP)
			glClearColor(0.f, 0.f, 1.f, 1.f);
	}
	glutPostRedisplay();
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow("Lec07");

	int submenuid = glutCreateMenu(MenuHandler);
	glutAddMenuEntry("CW", 11);
	glutAddMenuEntry("CCW", 12);

	int menuid = glutCreateMenu(MenuHandler);
	glutAddMenuEntry("RED", 13);
	glutAddMenuEntry("BLUE", 14);
	glutAddSubMenu("CullFace", submenuid);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMouseFunc(MenuHandler2);

	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);

	SetupRC();
	glutMainLoop();
	return 0;
}
