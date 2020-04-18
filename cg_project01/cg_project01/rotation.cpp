//#include<Windows.h>
//#include "gl/glut.h"
//#include<math.h>
//
//void SetupRC(void);
//void ChangeSize(int w, int h);
//void RenderScene(void);
//void init(void);
//void timer(int value);
//
//static float point[2][2];
//static float theta;
//
//void main(int argc, char* argv[])
//{
//    glutInit(&argc, argv); //라이브러리 초기화
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // 디스플레이모드 설정
//    glutInitWindowSize(500, 500);   //윈도우 창 크기 설정
//    glutCreateWindow("Hello OpenGL!!"); //윈도우 생성 및 제목
//    glutDisplayFunc(RenderScene); //이벤트 발생시 실행
//    glutReshapeFunc(ChangeSize); //크기가 변경되었을때 실행
//
//    glutTimerFunc(1000 / 30, timer, 1);
//
//    init();
//    SetupRC(); //초기화 함수
//    glutMainLoop(); //이벤트 루프 진입
//
//}
//
//void SetupRC(void)
//{
//    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); //RGB로 초기화
//}
//
//void init(void)
//{
//    //mouseLeftDown=false;
//
//    point[0][0] = 0;
//    point[0][1] = 0;
//    point[1][0] = 0;
//    point[1][1] = 0;
//
//    theta = 0;
//}
//
//void ChangeSize(int w, int h)
//{
//    if (h == 0)
//        h = 1;
//
//    glViewport(0, 0, w, h); //실제로 보이는 화면의 크기(윈도우창과 별개)
//
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//
//    if (w <= h)
//    {
//        gluOrtho2D(-2.0, 2.0, -2.0 * (float)h / (float)w, 2.0 * (float)h / (float)w);
//    }
//    else
//    {
//        gluOrtho2D(-2.0 * (float)h / (float)w, 2.0 * (float)h / (float)w, -2.0, 2.0);
//    }
//
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//}
//
//
//void timer(int value)
//{
//    theta += 2.0;
//    if (theta >= 360.0)
//        theta -= 360.0;
//
//    glutTimerFunc(1000 / 30, timer, 1);
//    glutPostRedisplay();
//}
//
//void RenderScene(void)
//{
//    glClear(GL_COLOR_BUFFER_BIT);
//
//    float cos_th = cos(theta * 3.14159 / 180.0);
//    float sin_th = sin(theta * 3.14159 / 180.0);
//
//    glColor3f(1, 0, 0);
//    glBegin(GL_POLYGON);
//    glVertex2f(cos_th, sin_th);
//    glVertex2f(-sin_th, cos_th);
//    glVertex2f(-cos_th, -sin_th);
//    glVertex2f(sin_th, -cos_th);
//    glEnd();
//    //glFlush();
//    glutSwapBuffers();
//}