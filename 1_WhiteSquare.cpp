#include<GL/freeglut.h>

int main(int argc, char **argv) {
	void Init();
	void Display();
	void Resize(int w, int h);
	void Keyboard(unsigned char key, int x, int y);
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(800, 600);
	glutCreateWindow("White Square");
	Init();
	glutDisplayFunc(Display);
	glutReshapeFunc(Resize);
	glutKeyboardFunc(Keyboard);
	glutMainLoop();
	return 0;
}


void Init() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
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

void Display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_POLYGON);
		glVertex3f(0.25f, 0.25f, 0.0f);
		glVertex3f(0.75f, 0.25f, 0.0f);
		glVertex3f(0.75f, 0.75f, 0.0f);
		glVertex3f(0.25f, 0.75f, 0.0f);
	glEnd();
	glFinish();
}

void Resize(int width, int height) {
	glViewport(0.0f, 0.0f, (GLsizei)width, (GLsizei)height);
}