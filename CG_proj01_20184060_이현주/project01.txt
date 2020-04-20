/*****************************************************************************************************
Class		: Computer Graphics
Proj Name	: project01
Student Name: 이현주
Student #	: 20184060
Due Date	: 20.04.21
******************************************************************************************************/

#include <Windows.h>				//Windows 헤더파일
#include "gl/glut.h"				//openGL 헤더파일
#include <math.h>					//sin, cos함수를 쓰기 위한 헤더파일

void SetupRC(void);					//background color 지정
void ChangeSize(int w, int h);		//창의 크기가 변경되면 실행
void RenderScene(void);				//stack으로 애니메이션 실행
void init(void);					//theta 초기화 함수
void Idie();						//g_timeDelta, g_prevTime으로 시간을 갱신하는 함수
void timer(int value);				//시간에 따라 각도를 변하게 하는 함수

static float theta;					//timer에 따라 변하는 값 -> 애니메이션 효과
static float zoom_theta;			//scaling에 사용하기 위해 timer에 따라 변하는 또다른 값

int g_timeDelta = 0, g_prevTime = 0;//ldie에서 시간을 갱신할 때 사용하는 변수
//GLfloat g_x = 0.f;
//GLfloat g_velocityX = 0.0005f;	//시간*속도 = 거리 에서 '속도'

void init(void)						//theta 초기화 함수
{
	theta = 0;						//0으로 초기화
}

void ChangeSize(int w, int h)		//창의 크기가 변경되면 실행
{
	if (h == 0)
		h = 1;

	glViewport(0, 0, w, h);			//실제로 보이는 화면의 크기(윈도우창과 별개)

	glMatrixMode(GL_PROJECTION);	//현재의 매트릭스 모드를 GL_PROJECTION로 설정
	glLoadIdentity();

	if (w <= h)						//weight와 height 비율에 따라
	{
		gluOrtho2D(-2.0, 2.0, -2.0 * (float)h / (float)w, 2.0 * (float)h / (float)w);	//glOrtho의 left, right, bottom, top 설정
	}
	else
	{
		gluOrtho2D(-2.0 * (float)h / (float)w, 2.0 * (float)h / (float)w, -2.0, 2.0);	//glOrtho의 left, right, bottom, top 설정
	}

	glMatrixMode(GL_MODELVIEW);		//현재의 매트릭스 모드를 GL_MODELVIEW로 설정
	glLoadIdentity();
}


void timer(int value)				//시간에 따라 각도를 변하게 하는 함수
{
	theta += 2.0;					//시간에 따라 각도가 2씩 증가
	if (theta >= 360.0)				//한바퀴를 다돌면
		theta -= 360.0;				//다시 원래각도로 초기화

	zoom_theta += 1.5;				//같은 시간 텀에 따라 각도가 1.5씩 증가 (scailing 속도)
	if (360.0 >= theta && theta >= 180.0)	//절반에 이르면 감소 scailing 진행
		zoom_theta -= 3.0;			//꾸준히 1.5씩 증가하므로 3.0을 감소시켜 최종적으로 1.5 감소 효과

	glutTimerFunc(1000 / 30, timer, 1);	//다음 타이머 이벤트는 1000 / 30밀리세컨트 후 호출
	glutPostRedisplay();			//현재의 윈도우를 재생하도록 요구
}

void RenderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT);			//색상 버퍼 비트 지우기

	glMatrixMode(GL_MODELVIEW);

	glEnableClientState(GL_VERTEX_ARRAY);

	GLfloat vertices[] = {					//출력될 도형을 위한 좌표 설정
		-0.8f, -0.8f, -0.8f,
		0.8f, -0.8f, -0.8f,
		0.8f, 0.8f, -0.8f,
		-0.8f, 0.8f, -0.8f,
		-0.8f, -0.8f, 0.8f,
		0.8f, -0.8f, 0.8f,
		0.8f, 0.8f, 0.8f,
		-0.8f, 0.8f, 0.8f
	};

	GLubyte indices[] = {					//12개의 삼각형을 위한 정점의 배열 인덱스
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

	//glVertexPointer(3, GL_FLOAT, 0, vertices);					//그래픽 출력을 위한 정점 배열 사용에 대한 설정
	//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, indices);//삼각형 12개를 드로잉(6*2) : 처리할 정점의 수 : 36개
	//glDisableClientState(GL_VERTEX_ARRAY);						//그래픽 출력을 하고 나서 정점 배열 사용에 대한 설정 해제

	//cycling start

	glPushMatrix();
		float cos_th = -0.3f * cos(theta * 3.14159 / 180.0);		//큐브가 타이머에 따라 변하는 세타 값에 따라 회전하도록 하기 위한 좌표 변수
		float sin_th = 0.3f * sin(theta * 3.14159 / 180.0);			//큐브가 타이머에 따라 변하는 세타 값에 따라 회전하도록 하기 위한 좌표 변수

		float sin_val = 0.5f * sin(theta * 3.14159 / 180.0);		//반지름이 0.5f인 원을 중심으로 회전하며 위치를 바꾸기 위한 좌표 변수
		float cos_val = 0.5f * cos(theta * 3.14159 / 180.0);		//반지름이 0.5f인 원을 중심으로 회전하며 위치를 바꾸기 위한 좌표 변수

		glColor3f(0.603922f, 0.803922f, 0.196078f);
		glBegin(GL_POLYGON);										//GL Primitive로 vertex그리기
			glVertex3f(cos_th - 1 + sin_val , sin_th + 1 + cos_val, 0.6f);	//큐브 좌표 설정
			glVertex3f(-sin_th - 1 + sin_val, cos_th + 1 + cos_val, 0.6f);	//큐브 좌표 설정
			glVertex3f(-cos_th - 1 + sin_val, -sin_th + 1 + cos_val, 0.6f);	//큐브 좌표 설정
			glVertex3f(sin_th - 1 + sin_val, -cos_th + 1 + cos_val, 0.6f);	//큐브 좌표 설정
		glEnd();

	glPopMatrix();

	//cycling end

	//zoom in out start

	glPushMatrix();
		float plus = zoom_theta*0.002f + 0.3f;						//scaling으로 큐브가 커질때 해당 큐브가 1사분면에 있으므로 상대적으로 오른쪽과 위쪽에 있는 좌표값은 커지도록 설정한 변수
		float minus = -zoom_theta*0.002f - 0.3f;					//scaling으로 큐브가 커질때 해당 큐브가 1사분면에 있으므로 상대적으로 왼쪽과 아래쪽에 있는 좌표값은 작아지도록 설정한 변수

		glColor3f(1.0f, 0.0f, 0.0f);								//큐브 색상 설정
		glBegin(GL_POLYGON);
			glVertex3f(plus + 1, plus + 1, plus + minus);			//큐브 좌표 설정
			glVertex3f(minus + 1, plus + 1, plus + minus);			//큐브 좌표 설정
			glVertex3f(minus + 1, minus + 1, plus + minus);			//큐브 좌표 설정
			glVertex3f(plus + 1, minus + 1, plus + minus);			//큐브 좌표 설정
		glEnd();

	glPopMatrix();

	//zoom in out end
	
	//rotation start


	glPushMatrix();

		glColor3f(1.0f, 0.6f, 0.0f);								//큐브 색상 설정
		glBegin(GL_POLYGON);
			glVertex3f(cos_th + 1, sin_th -1, 0.6f);				//위에 이미 선언된 회전에 따른 좌표 변경을 위한 변수를 사용하여 큐브 좌표 설정
			glVertex3f(-sin_th + 1, cos_th -1, 0.6f);				//큐브 좌표 설정
			glVertex3f(-cos_th + 1, -sin_th -1, 0.6f);				//큐브 좌표 설정
			glVertex3f(sin_th + 1, -cos_th -1, 0.6f);				//큐브 좌표 설정
		glEnd();

	glPopMatrix();

	//rotation end

	glLoadIdentity();
	//gluLookAt(0, 10, 0, 0, 0, -1, 0, 1, 0);
	
	//glFlush();
	glutSwapBuffers();
}

void SetupRC(void) {												//background color 지정
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);							//bgc = black
}

void Idie() {														//g_timeDelta, g_prevTime으로 시간을 갱신하는 함수
	int currentTime = glutGet(GLUT_ELAPSED_TIME);					//현재 시간 선언
	g_timeDelta = currentTime - g_prevTime;							//시간 변화값(타이머)측정
	g_prevTime = currentTime;										//시간 갱신
	glutPostRedisplay();
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);											//초기화

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);					//디스플레이 모드 설정
	glutCreateWindow("Assignment01");								//실행 window 이름 설정

	glutDisplayFunc(RenderScene);									//stack으로 애니메이션 실행
	glutIdleFunc(Idie);												//g_timeDelta, g_prevTime으로 시간을 갱신하는 함수
	glutReshapeFunc(ChangeSize);									//크기가 변경되었을때 실행

	glutTimerFunc(1000 / 30, timer, 1);								//1회성 타이머를 등록

	init();															//theta 초기화 함수

	SetupRC();
	glutMainLoop();
	//return 0;
}