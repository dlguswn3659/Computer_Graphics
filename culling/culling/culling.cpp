/*****************************************************************************************************
Class		: Computer Graphics
Proj Name	: opengl ���� �ʰ� culling�����ϱ�
Student Name: ������
Student #	: 20184060
Due Date	: 20.04.30
******************************************************************************************************/

#include <Windows.h>				//Windows �������
#include <stdio.h>
#include "gl/glut.h"				//openGL �������
#include <math.h>					//sin, cos�Լ��� ���� ���� �������
#define CCW	0
#define CW	1

void SetupRC(void);					//background color ����
void RenderScene(void);				//ť�� ���� �� glulookat ����
void ReduceToUnit(float vector[3]);	//�������ͷ� �ٲ��ִ� �޼ҵ�
void calcNormal(float v[3][3], float out[3]);	//normal vector ��� �޼ҵ�
float InnerProduct(float v[3], float n[3]);		//���� ��� ��� ��ȯ �޼ҵ�


GLfloat my_triangle1[3][3] = { -10.f, 0.f, 0.f, 10.f, 0.f, 0.f, 0.f, 10.f, 0.f };	//�ﰢ�� �ո�
GLfloat my_triangle2[3][3] = { 10.f, 0.f, 0.f, -10.f, 0.f, 0.f, 0.f, 10.f, 0.f };	//�ﰢ�� �޸�
GLfloat faceNorm[3];																//��������
GLfloat eyeVec[3] = { 0.f, 0.f, -80.0f };											//gluLookAt���� eyeview vector
GLint culling = 0;																	//0�̸� CCW, 1�̸� CW
GLfloat inner_product;																//���� ��� ����

void ReduceToUnit(float vector[3]) {												//�������ͷ� �ٲ��ִ� �޼ҵ�
	float length;

	length = (float)sqrt((vector[0] * vector[0]) + (vector[1] * vector[1]) + (vector[2] * vector[2]));
	if (length == 0.0f)
		length = 1.0f;

	vector[0] /= length;
	vector[1] /= length;
	vector[2] /= length;
}

void calcNormal(float v[3][3], float out[3]) {										//normal vector ��� �޼ҵ�
	float v1[3], v2[3];
	static const int x = 0;
	static const int y = 1;
	static const int z = 2;

	// �� ������ ���� �� ���� ���͸� ����
	v1[x] = v[0][x] - v[1][x];
	v1[y] = v[0][y] - v[1][y];
	v1[z] = v[0][z] - v[1][z];

	v2[x] = v[1][x] - v[2][x];
	v2[y] = v[1][y] - v[2][y];
	v2[z] = v[1][z] - v[2][z];

	// out[]�� normal vector�� �����Ѵ�.
	out[x] = v1[y] * v2[z] - v1[z] * v2[y];
	out[y] = v1[z] * v2[x] - v1[x] * v2[z];
	out[z] = v1[x] * v2[y] - v1[y] * v2[x];

	// vector�� normalize�ϱ� (0~1�� �ٲ��ֱ�)
	ReduceToUnit(out);
}

float InnerProduct(float v[3], float n[3]) {										//���� ��� ��� ��ȯ �޼ҵ�
	float result;
	result = (v[0] * n[0]) + (v[1] * n[1]) + (v[2] * n[2]);
	return result;
}

void RenderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	gluLookAt(eyeVec[0], eyeVec[1], eyeVec[2], 0.f, 0.f, 0.f, 0.f, 1.f, 0.f);
	calcNormal(my_triangle1, faceNorm);
	printf("faceNorm[0]	: %f	faceNorm[1]	: %f	faceNorm[2]	: %f\n", faceNorm[0], faceNorm[1], faceNorm[2]);
	printf("eyeVec[0]	: %f	eyeVec[1]	: %f	eyeVec[2]	: %f\n", eyeVec[0], eyeVec[1], eyeVec[2]);

	inner_product = InnerProduct(eyeVec, faceNorm);
	printf("inner_product	: %f\n", inner_product);

	//���� ��������(N)�� view vector�� �̷�� ���� 90���� ������ CW, ��, V����N < 0�� ���� viewer�� ���� CW�̴�.
	if (inner_product < 0.0) {
		culling = CW;
	}
	else {
		culling = CCW;
	}

	printf("culling	: %f\n", culling);

	if (culling == CCW) {
		glColor3f(1.0f, 0.0f, 0.0f);
		glPushMatrix();
			glColor3f(1.0f, 0.0f, 0.0f);
			glTranslatef(25.f, 0.f, 0.f);
			glScaled(2.f, 2.f, 2.f);
			glBegin(GL_TRIANGLES);
				glVertex3f(my_triangle1[0][0], my_triangle1[0][1], my_triangle1[0][2]);
				glVertex3f(my_triangle1[1][0], my_triangle1[1][1], my_triangle1[1][2]);
				glVertex3f(my_triangle1[2][0], my_triangle1[2][1], my_triangle1[2][2]);
			glEnd();
		glPopMatrix();
	}
	
	else if (culling == CW) {
		glColor3f(0.0f, 1.0f, 0.0f);
		glPushMatrix();
			glTranslatef(-25.f, 0.f, 0.f);
			glScaled(2.f, 2.f, 2.f);
			glBegin(GL_TRIANGLES);
				glVertex3f(my_triangle2[0][0], my_triangle2[0][1], my_triangle2[0][2]);
				glVertex3f(my_triangle2[1][0], my_triangle2[1][1], my_triangle2[1][2]);
				glVertex3f(my_triangle2[2][0], my_triangle2[2][1], my_triangle2[2][2]);
			glEnd();
		glPopMatrix();
	}

	glFlush();
}
void SetupRC(void) {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	//glFrontFace(GL_CCW);
}

void ChangeSize(GLsizei w, GLsizei h) {
	if (h == 0)
		h = 1;

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLfloat aspectRatio = (GLfloat)w / (GLfloat)h;
	gluPerspective(90.f, aspectRatio, 10.f, 200.f);
	//glOrtho(-100.f, 100.f, -100.f, 100.f, -100.f, 100.f);
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);	//initialize GL context
	//single or double buffering | RGBA color mode
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutCreateWindow("Lec06");
	//callback function
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);

	SetupRC();
	glutMainLoop();
	//return 0;
}