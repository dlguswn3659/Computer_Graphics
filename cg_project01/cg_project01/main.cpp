#include "gl/glut.h"

void RenderScene(void) {
	//���۸� �����. COLOR, DEPTH, STENCIL, ACCUM
	glClear(GL_COLOR_BUFFER_BIT);
	//������ �����Ѵ�. R, G, B

	glColor3f(0, 0, 1);
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();

	glutSolidTeapot(0.25);

	glPopMatrix();

	//OpenGL ����� ������ ����ȭ�� ���� ť�� ����Ǿ��ٰ� �Ѳ����� ����ȴ�.
	glFlush();
}

void SetupRC(void) {
	//R, G, B, A.	A�� ����. 1�̸� ������, 0�̸� ����
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);	//initialize GL context
	// Single or double buffering | RGBA color mode
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutCreateWindow("Lec03");
	//callback function
	glutDisplayFunc(RenderScene);
}