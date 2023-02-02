#include<GL/freeglut.h>

int main(int argc, char **argv) {
	void Init();
	void Display();
	void Resize(int w, int h);
	void Keyboard(unsigned char key, int x, int y);
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Hello World");
	Init();
	glutDisplayFunc(Display);
	glutReshapeFunc(Resize);
	glutKeyboardFunc(Keyboard);
	glutMainLoop();
	return 0;
}

void Init() {
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_FLAT);
}

void Display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2f(1.0f, 1.0f);
	glVertex2f(-1.0f, 1.0f);
	glVertex2f(-1.0f, -1.0f);
	glVertex2f(1.0f, -1.0f);
	glEnd();
	glColor3f(1.0f, 1.0f, 1.0f);
	glScalef(1.0f, 2.0f, 1.0f);
	glutWireCube(1.0);
	// glBegin(GL_LINE_LOOP);
	// glVertex2f(0.0f, 1.0f);
	// glVertex2f(-1.0f, -1.0f);
	// glVertex2f(1.0f, -1.0f);
	// glEnd();
	glutSwapBuffers();
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

void Resize(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
	gluPerspective(60.0, (GLdouble)width/height, 1.5, 20.0);
	glMatrixMode(GL_MODELVIEW);
}