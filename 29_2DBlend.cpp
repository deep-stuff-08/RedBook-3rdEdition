#include<GL/freeglut.h>

static bool isYellowFirst = true;

void Init() {
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glShadeModel(GL_FLAT);
	glEnable(GL_BLEND);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void Reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w <= h) {
		gluOrtho2D(0.0f, 1.0f, 0.0f, 1.0f * (GLdouble)h / w);
	} else {
		gluOrtho2D(0.0f, 1.0f * (GLdouble)w / h, 0.0f, 1.0f);
	}
}

void DrawLeftTriangle() {
	glColor4f(1.0f, 1.0f, 0.0f, 0.75f);
	glBegin(GL_TRIANGLES);
	glVertex2f(0.1f, 0.9f);
	glVertex2f(0.1f, 0.1f);
	glVertex2f(0.7f, 0.5f);
	glEnd();
}

void DrawRightTriangle() {
	glColor4f(0.0f, 1.0f, 1.0f, 0.75f);
	glBegin(GL_TRIANGLES);
	glVertex2f(0.9f, 0.9f);
	glVertex2f(0.3f, 0.5f);
	glVertex2f(0.9f, 0.1f);
	glEnd();
}

void Display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	if(isYellowFirst) {
		DrawLeftTriangle();
		DrawRightTriangle();
	} else {
		DrawRightTriangle();
		DrawLeftTriangle();
	}
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
	case 't': case 'T':
		isYellowFirst = !isYellowFirst;
		glutPostRedisplay();
		break;
	}
}

int main(int argc, char** argv) {
	glutInit (&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(500, 500);
	glutCreateWindow(argv[0]);
	Init();
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutDisplayFunc (Display);
	glutMainLoop();
}