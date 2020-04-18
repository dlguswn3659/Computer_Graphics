#include<Windows.h>
#include "gl/glut.h"
#include<math.h>

void SetupRC(void);
void ChangeSize(int w, int h);
void RenderScene(void);
void init(void);
void timer(int value);

static float point[2][2];
static float theta;

GLfloat g_x = 0.f;
int g_timeDelta = 0, g_prevTime = 0;
GLfloat g_velocityX = 0.0005f;	//시간*속도 = 거리 에서 '속도'

void init(void)
{
	//mouseLeftDown=false;

	point[0][0] = 0;
	point[0][1] = 0;
	point[1][0] = 0;
	point[1][1] = 0;

	theta = 0;
}

void ChangeSize(int w, int h)
{
	if (h == 0)
		h = 1;

	glViewport(0, 0, w, h); //실제로 보이는 화면의 크기(윈도우창과 별개)

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w <= h)
	{
		gluOrtho2D(-2.0, 2.0, -2.0 * (float)h / (float)w, 2.0 * (float)h / (float)w);
	}
	else
	{
		gluOrtho2D(-2.0 * (float)h / (float)w, 2.0 * (float)h / (float)w, -2.0, 2.0);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void timer(int value)
{
	theta += 2.0;
	if (theta >= 360.0)
		theta -= 360.0;

	glutTimerFunc(1000 / 30, timer, 1);
	glutPostRedisplay();
}

void RenderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);

	g_x += g_velocityX + (GLfloat)g_timeDelta / 10000.f;

	glPushMatrix();
		glColor3f(1.0f, 0.0f, 0.0f);

		glTranslatef(g_x, 0.0f, 0.0f);

		glBegin(GL_QUADS);
			glVertex3f(0.2f, 0.2f, 0.0f);
			glVertex3f(-0.2f, 0.2f, 0.0f);
			glVertex3f(-0.2f, -0.2f, 0.0f);
			glVertex3f(0.2f, -0.2f, 0.0f);
		glEnd();

	glPopMatrix();

	glPushMatrix();
	glColor3f(0.0f, 1.0f, 0.0f);

	glTranslatef(g_x, 0.0f, 0.0f);

	glBegin(GL_QUADS);
	glVertex3f(0.2f, 0.6f, 0.0f);
	glVertex3f(-0.2f, 0.6f, 0.0f);
	glVertex3f(-0.2f, 0.2f, 0.0f);
	glVertex3f(0.2f, 0.2f, 0.0f);
	glEnd();

	glPopMatrix();
	
	//rotation start


	glPushMatrix();
	glColor3f(1.0f, 0.0f, 0.0f);

	//glTranslatef(g_x, 0.0f, 0.0f);

	float cos_th = 0.3f*cos(theta * 3.14159 / 180.0);
	float sin_th = 0.3f*sin(theta * 3.14159 / 180.0);

	glColor3f(1, 0, 0);
	glBegin(GL_POLYGON);
	glVertex2f(cos_th, sin_th);
	glVertex2f(-sin_th, cos_th);
	glVertex2f(-cos_th, -sin_th);
	glVertex2f(sin_th, -cos_th);
	glEnd();

	glPopMatrix();

	//rotation end

	glLoadIdentity();
	//gluLookAt(0, 10, 0, 0, 0, -1, 0, 1, 0);
	
	//glFlush();
	glutSwapBuffers();
}

void SetupRC(void) {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void Idie() {
	int currentTime = glutGet(GLUT_ELAPSED_TIME);
	g_timeDelta = currentTime - g_prevTime;
	g_prevTime = currentTime;
	glutPostRedisplay();
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutCreateWindow("Lec04");

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idie);
	glutReshapeFunc(ChangeSize); //크기가 변경되었을때 실행

	glutTimerFunc(1000 / 30, timer, 1);

	init();

	SetupRC();
	glutMainLoop();
	//return 0;
}