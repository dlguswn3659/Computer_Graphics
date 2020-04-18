#include "gl/glut.h"

void ChangeSize(GLsizei w, GLsizei h) {
	GLfloat aspectRatio;
	//Prevent a divide by zero
	if (h == 0) {
		h = 1;
	}
	//Set Viewport to window dimensions
	glViewport(0, 0, w, h);
	// Reset coordinate system
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//Establish clipping volume (left, right, bottom, top, near, far)
	aspectRatio = (GLfloat)w / (GLfloat)h;
	if (w <= h) {
		glOrtho(-100.0, 100.0, -100 / aspectRatio, 100.0 / aspectRatio, 100.0, -100.0);
	}
	else {
		glOrtho(-100.0 * aspectRatio, 100.0 * aspectRatio, -100.0, 100.0, 100.0, -100.0);
	}
}

void RenderScene(void) {
	//���۸� �����. COLOR, DEPTH, STENCIL, ACCUM
	glClear(GL_COLOR_BUFFER_BIT);
	//������ �����Ѵ�. R, G, B
	glColor3f(1.0f, 0.0f, 0.0f);
	glRectf(-25.0f, 25.0f, 25.0f, -25.0f);
	//Draw a filled rectangle with current color
	//OpenGL ����� ������ ����ȭ�� ���� ť�� ����Ǿ��ٰ� �Ѳ����� ����ȴ�.
	glFlush();
}

void SetupRC(void) {
	//R, G, B, A.	A�� ����. 1�̸� ������, 0�̸� ����
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);	//initialize GL context
	// Single or double buffering | RGBA color mode
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutCreateWindow("Lec04");
	//callback function
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	SetupRC();			//initialize render context(RC)
	glutMainLoop();		//run GLUT framework
	return 0;
}