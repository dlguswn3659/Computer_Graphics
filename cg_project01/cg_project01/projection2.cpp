#include "gl/glut.h"

int g_timeDelta, g_prevTime;

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
	
	/*if (w <= h) {
		glOrtho(-100.0, 100.0, -100 / aspectRatio, 100.0 / aspectRatio, 100.0, -100.0);
	}
	else {
		glOrtho(-100.0 * aspectRatio, 100.0 * aspectRatio, -100.0, 100.0, 100.0, -100.0);
	}*/
	aspectRatio = (GLfloat)w / (GLfloat)h;
	gluPerspective(90.f, aspectRatio, 10.f, 200.f);
	/*glOrtho(-100.f, 100.f, -100.f, 100.f, -100.f, 100.f);*/
}

void RenderScene(void) {
	//버퍼를 지운다. COLOR, DEPTH, STENCIL, ACCUM
	glClear(GL_COLOR_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0.f, 0.f, -80.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f);

	glPushMatrix();
		glTranslatef(26.f, -30.f, -60.f);
		glScaled(2.f, 2.f, 1.f);
		glBegin(GL_TRIANGLES);
			glColor3f(1.0f, 0.6f, 0.0f);
			glVertex3f(-10.f, 0.f, 0.f);
			glVertex3f(10.f, 0.f, 0.f);
			glVertex3f(0.f, 20.f, 0.f);
		glEnd();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(26.f, -30.f, 0.f);
		glScaled(2.f, 2.f, 1.f);
		glBegin(GL_TRIANGLES);
			glColor3f(1.0f, 1.0f, 1.0f);
			glVertex3f(10.f, 0.f, 0.f);
			glVertex3f(-10.f, 0.f, 0.f);
			glVertex3f(0.f, 20.f, 0.f);
		glEnd();
	glPopMatrix();


	glutSwapBuffers();
}

void SetupRC(void) {
	//R, G, B, A.	A는 투명도. 1이면 불투명, 0이면 투명
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void Idie() {
	int currentTime = glutGet(GLUT_ELAPSED_TIME);
	g_timeDelta = currentTime - g_prevTime;
	g_prevTime = currentTime;
	glutPostRedisplay();
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);	//initialize GL context
	// Single or double buffering | RGBA color mode
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutCreateWindow("Lec04");
	//callback function
	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idie);
	//glutReshapeFunc(ChangeSize);


	SetupRC();			//initialize render context(RC)
	glutMainLoop();		//run GLUT framework
	return 0;
}