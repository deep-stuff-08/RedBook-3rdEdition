#include<GL/freeglut.h>

GLfloat spin = 0.0f;

int main(int argc, char **argv) {
	void Init();
	void Display();
	void Resize(int w, int h);
	void Keyboard(unsigned char key, int x, int y);
	void Mouse(int btn, int state, int x, int y);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(800, 600);
	glutCreateWindow("White Spinning Square");
	Init();
	glutDisplayFunc(Display);
	glutReshapeFunc(Resize);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutMainLoop();
	return 0;
}


void Init() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glShadeModel(GL_FLAT);
}

void Mouse(int btn, int state, int x, int y) {
	void Update();

	if(btn == GLUT_LEFT_BUTTON) {
		glutIdleFunc(Update);
	} else if(btn == GLUT_RIGHT_BUTTON) {
		glutIdleFunc(NULL);
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

void Update() {
	spin = spin + 0.02f;
	if(spin > 360.0f) {
		spin -= 360.0f;
	}
	glutPostRedisplay();
}

void Display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glRotatef(spin, 0.0f, 0.0f, 1.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glRectf(-25.0f, -25.0f, 25.0f, 25.0f);
	glPopMatrix();
	glutSwapBuffers();
}

void Resize(int width, int height) {
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-50.0f, 50.0f, -50.0f, 50.0f, -1.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
