#include "gl/glut.h"

void RenderScene(void) {
	//버퍼를 지운다. COLOR, DEPTH, STENCIL, ACCUM
	glClear(GL_COLOR_BUFFER_BIT);
	//색상을 결정한다. R, G, B

	glColor3f(0, 0, 1);
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();

	glutSolidTeapot(0.25);

	glPopMatrix();

	//OpenGL 명령은 성능의 최적화를 위해 큐에 저장되었다가 한꺼번에 실행된다.
	glFlush();
}

void SetupRC(void) {
	//R, G, B, A.	A는 투명도. 1이면 불투명, 0이면 투명
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