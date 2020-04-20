/*****************************************************************************************************
Class		: Computer Graphics
Proj Name	: project01
Student Name: ������
Student #	: 20184060
Due Date	: 20.04.21
******************************************************************************************************/

#include <Windows.h>				//Windows �������
#include "gl/glut.h"				//openGL �������
#include <math.h>					//sin, cos�Լ��� ���� ���� �������

void SetupRC(void);					//background color ����
void ChangeSize(int w, int h);		//â�� ũ�Ⱑ ����Ǹ� ����
void RenderScene(void);				//stack���� �ִϸ��̼� ����
void init(void);					//theta �ʱ�ȭ �Լ�
void Idie();						//g_timeDelta, g_prevTime���� �ð��� �����ϴ� �Լ�
void timer(int value);				//�ð��� ���� ������ ���ϰ� �ϴ� �Լ�

static float theta;					//timer�� ���� ���ϴ� �� -> �ִϸ��̼� ȿ��
static float zoom_theta;			//scaling�� ����ϱ� ���� timer�� ���� ���ϴ� �Ǵٸ� ��

int g_timeDelta = 0, g_prevTime = 0;//ldie���� �ð��� ������ �� ����ϴ� ����
//GLfloat g_x = 0.f;
//GLfloat g_velocityX = 0.0005f;	//�ð�*�ӵ� = �Ÿ� ���� '�ӵ�'

void init(void)						//theta �ʱ�ȭ �Լ�
{
	theta = 0;						//0���� �ʱ�ȭ
}

void ChangeSize(int w, int h)		//â�� ũ�Ⱑ ����Ǹ� ����
{
	if (h == 0)
		h = 1;

	glViewport(0, 0, w, h);			//������ ���̴� ȭ���� ũ��(������â�� ����)

	glMatrixMode(GL_PROJECTION);	//������ ��Ʈ���� ��带 GL_PROJECTION�� ����
	glLoadIdentity();

	if (w <= h)						//weight�� height ������ ����
	{
		gluOrtho2D(-2.0, 2.0, -2.0 * (float)h / (float)w, 2.0 * (float)h / (float)w);	//glOrtho�� left, right, bottom, top ����
	}
	else
	{
		gluOrtho2D(-2.0 * (float)h / (float)w, 2.0 * (float)h / (float)w, -2.0, 2.0);	//glOrtho�� left, right, bottom, top ����
	}

	glMatrixMode(GL_MODELVIEW);		//������ ��Ʈ���� ��带 GL_MODELVIEW�� ����
	glLoadIdentity();
}


void timer(int value)				//�ð��� ���� ������ ���ϰ� �ϴ� �Լ�
{
	theta += 2.0;					//�ð��� ���� ������ 2�� ����
	if (theta >= 360.0)				//�ѹ����� �ٵ���
		theta -= 360.0;				//�ٽ� ���������� �ʱ�ȭ

	zoom_theta += 1.5;				//���� �ð� �ҿ� ���� ������ 1.5�� ���� (scailing �ӵ�)
	if (360.0 >= theta && theta >= 180.0)	//���ݿ� �̸��� ���� scailing ����
		zoom_theta -= 3.0;			//������ 1.5�� �����ϹǷ� 3.0�� ���ҽ��� ���������� 1.5 ���� ȿ��

	glutTimerFunc(1000 / 30, timer, 1);	//���� Ÿ�̸� �̺�Ʈ�� 1000 / 30�и�����Ʈ �� ȣ��
	glutPostRedisplay();			//������ �����츦 ����ϵ��� �䱸
}

void RenderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT);			//���� ���� ��Ʈ �����

	glMatrixMode(GL_MODELVIEW);

	glEnableClientState(GL_VERTEX_ARRAY);

	GLfloat vertices[] = {					//��µ� ������ ���� ��ǥ ����
		-0.8f, -0.8f, -0.8f,
		0.8f, -0.8f, -0.8f,
		0.8f, 0.8f, -0.8f,
		-0.8f, 0.8f, -0.8f,
		-0.8f, -0.8f, 0.8f,
		0.8f, -0.8f, 0.8f,
		0.8f, 0.8f, 0.8f,
		-0.8f, 0.8f, 0.8f
	};

	GLubyte indices[] = {					//12���� �ﰢ���� ���� ������ �迭 �ε���
		7, 5, 6,
		7, 4, 5,
		3, 2, 1,
		3, 1, 0,
		2, 6, 5,
		2, 5, 1,
		3, 7, 6,
		3, 6, 2,
		0, 4, 7, 
		0, 7, 3,
		1, 5, 4,
		1, 4, 0
	};

	//glVertexPointer(3, GL_FLOAT, 0, vertices);					//�׷��� ����� ���� ���� �迭 ��뿡 ���� ����
	//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, indices);//�ﰢ�� 12���� �����(6*2) : ó���� ������ �� : 36��
	//glDisableClientState(GL_VERTEX_ARRAY);						//�׷��� ����� �ϰ� ���� ���� �迭 ��뿡 ���� ���� ����

	//cycling start

	glPushMatrix();
		float cos_th = -0.3f * cos(theta * 3.14159 / 180.0);		//ť�갡 Ÿ�̸ӿ� ���� ���ϴ� ��Ÿ ���� ���� ȸ���ϵ��� �ϱ� ���� ��ǥ ����
		float sin_th = 0.3f * sin(theta * 3.14159 / 180.0);			//ť�갡 Ÿ�̸ӿ� ���� ���ϴ� ��Ÿ ���� ���� ȸ���ϵ��� �ϱ� ���� ��ǥ ����

		float sin_val = 0.5f * sin(theta * 3.14159 / 180.0);		//�������� 0.5f�� ���� �߽����� ȸ���ϸ� ��ġ�� �ٲٱ� ���� ��ǥ ����
		float cos_val = 0.5f * cos(theta * 3.14159 / 180.0);		//�������� 0.5f�� ���� �߽����� ȸ���ϸ� ��ġ�� �ٲٱ� ���� ��ǥ ����

		glColor3f(0.603922f, 0.803922f, 0.196078f);
		glBegin(GL_POLYGON);										//GL Primitive�� vertex�׸���
			glVertex3f(cos_th - 1 + sin_val , sin_th + 1 + cos_val, 0.6f);	//ť�� ��ǥ ����
			glVertex3f(-sin_th - 1 + sin_val, cos_th + 1 + cos_val, 0.6f);	//ť�� ��ǥ ����
			glVertex3f(-cos_th - 1 + sin_val, -sin_th + 1 + cos_val, 0.6f);	//ť�� ��ǥ ����
			glVertex3f(sin_th - 1 + sin_val, -cos_th + 1 + cos_val, 0.6f);	//ť�� ��ǥ ����
		glEnd();

	glPopMatrix();

	//cycling end

	//zoom in out start

	glPushMatrix();
		float plus = zoom_theta*0.002f + 0.3f;						//scaling���� ť�갡 Ŀ���� �ش� ť�갡 1��и鿡 �����Ƿ� ��������� �����ʰ� ���ʿ� �ִ� ��ǥ���� Ŀ������ ������ ����
		float minus = -zoom_theta*0.002f - 0.3f;					//scaling���� ť�갡 Ŀ���� �ش� ť�갡 1��и鿡 �����Ƿ� ��������� ���ʰ� �Ʒ��ʿ� �ִ� ��ǥ���� �۾������� ������ ����

		glColor3f(1.0f, 0.0f, 0.0f);								//ť�� ���� ����
		glBegin(GL_POLYGON);
			glVertex3f(plus + 1, plus + 1, plus + minus);			//ť�� ��ǥ ����
			glVertex3f(minus + 1, plus + 1, plus + minus);			//ť�� ��ǥ ����
			glVertex3f(minus + 1, minus + 1, plus + minus);			//ť�� ��ǥ ����
			glVertex3f(plus + 1, minus + 1, plus + minus);			//ť�� ��ǥ ����
		glEnd();

	glPopMatrix();

	//zoom in out end
	
	//rotation start


	glPushMatrix();

		glColor3f(1.0f, 0.6f, 0.0f);								//ť�� ���� ����
		glBegin(GL_POLYGON);
			glVertex3f(cos_th + 1, sin_th -1, 0.6f);				//���� �̹� ����� ȸ���� ���� ��ǥ ������ ���� ������ ����Ͽ� ť�� ��ǥ ����
			glVertex3f(-sin_th + 1, cos_th -1, 0.6f);				//ť�� ��ǥ ����
			glVertex3f(-cos_th + 1, -sin_th -1, 0.6f);				//ť�� ��ǥ ����
			glVertex3f(sin_th + 1, -cos_th -1, 0.6f);				//ť�� ��ǥ ����
		glEnd();

	glPopMatrix();

	//rotation end

	glLoadIdentity();
	//gluLookAt(0, 10, 0, 0, 0, -1, 0, 1, 0);
	
	//glFlush();
	glutSwapBuffers();
}

void SetupRC(void) {												//background color ����
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);							//bgc = black
}

void Idie() {														//g_timeDelta, g_prevTime���� �ð��� �����ϴ� �Լ�
	int currentTime = glutGet(GLUT_ELAPSED_TIME);					//���� �ð� ����
	g_timeDelta = currentTime - g_prevTime;							//�ð� ��ȭ��(Ÿ�̸�)����
	g_prevTime = currentTime;										//�ð� ����
	glutPostRedisplay();
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);											//�ʱ�ȭ

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);					//���÷��� ��� ����
	glutCreateWindow("Assignment01");								//���� window �̸� ����

	glutDisplayFunc(RenderScene);									//stack���� �ִϸ��̼� ����
	glutIdleFunc(Idie);												//g_timeDelta, g_prevTime���� �ð��� �����ϴ� �Լ�
	glutReshapeFunc(ChangeSize);									//ũ�Ⱑ ����Ǿ����� ����

	glutTimerFunc(1000 / 30, timer, 1);								//1ȸ�� Ÿ�̸Ӹ� ���

	init();															//theta �ʱ�ȭ �Լ�

	SetupRC();
	glutMainLoop();
	//return 0;
}