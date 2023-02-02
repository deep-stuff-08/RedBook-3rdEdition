#include<GL/freeglut.h>
#include<stdio.h>

void Init() {
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);
}

void Display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutSwapBuffers();
}

void Reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLdouble)w / (GLdouble)h, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

void Mouse(int btn, int state, int x, int y) {
	GLint viewport[4];
	GLdouble mvmatrix[16];
	GLdouble projmatrix[16];
	GLint realy;
	GLdouble wx, wy, wz;

	if(btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		glGetIntegerv(GL_VIEWPORT, viewport);
		glGetDoublev(GL_PROJECTION_MATRIX, projmatrix);
		glGetDoublev(GL_MODELVIEW_MATRIX, mvmatrix);
		realy = viewport[3] - (GLint)y - 1;
		printf("Real Coordinates Are: %4d, %4d\n", x, realy);
		gluUnProject(x, realy, 0.0, mvmatrix, projmatrix, viewport, &wx, &wy, &wz);
		printf("World Coordinates at z=0.0 Are: %f %f %f\n", wx, wy, wz);
		gluUnProject(x, realy, 1.0, mvmatrix, projmatrix, viewport, &wx, &wy, &wz);
		printf("World Coordinates at z=1.0 Are: %f %f %f\n\n", wx, wy, wz);
	}
}

void Keyboard(unsigned char key, int x, int y) {
	switch(key) {
	case 27:
		glutLeaveMainLoop();
		break;
	case 'f': case 'F':
		glutFullScreenToggle();
		break;
	}
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	Init();
	glutDisplayFunc(Display);
	glutReshapeFunc (Reshape);
	glutMouseFunc(Mouse);
	glutKeyboardFunc(Keyboard);
	glutMainLoop();
	return 0;
}