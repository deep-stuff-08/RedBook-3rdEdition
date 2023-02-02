#include<GL/freeglut.h>

#define DRAW_LINEF(x1, y1, x2, y2) \
glBegin(GL_LINES);\
glVertex2f((x1), (y1));\
glVertex2f((x2), (y2));\
glEnd()

void Keyboard(unsigned char key, int x, int y) {
	switch(key) {
	case 'f': case 'F':
		glutFullScreenToggle();
		break;
	case 27:
		glutLeaveMainLoop();
		break;
	}
}

int main(int argc, char **argv) {
	void Init();
	void Display();
	void Resize(int w, int h);
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Lines");
	Init();
	glutDisplayFunc(Display);
	glutReshapeFunc(Resize);
	glutKeyboardFunc(Keyboard);
	glutMainLoop();
	return 0;
}


void Init() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glShadeModel(GL_FLAT);
}

void Display() {
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.0f, 1.0f, 1.0f);

	glEnable(GL_LINE_STIPPLE);
	//Line 1
	glLineStipple(1, 0x0101);
	DRAW_LINEF(0.0f, 125.0f, 200.0f, 125.0f);
	glLineStipple(1, 0x00FF);
	DRAW_LINEF(200.0f, 125.0f, 400.0f, 125.0f);
	glLineStipple(1, 0x1C47);
	DRAW_LINEF(400.0f, 125.0f, 600.0f, 125.0f);
	//Line 2
	glLineWidth(5.0f);
	glLineStipple(1, 0x0101);
	DRAW_LINEF(0.0f, 100.0f, 200.0f, 100.0f);
	glLineStipple(1, 0x00FF);
	DRAW_LINEF(200.0f, 100.0f, 400.0f, 100.0f);
	glLineStipple(1, 0x1C47);
	DRAW_LINEF(400.0f, 100.0f, 600.0f, 100.0f);
	glLineWidth(1.0f);
	//Line 3
	glLineStipple(1, 0x1C47);
	glBegin(GL_LINE_STRIP);
	for(int i = 0; i < 7; i++) {
		glVertex2f(0.0f + ((GLfloat) i * 100.0f), 75.0f);
	}
	glEnd();
	//Line 4
	for(int  i = 0; i < 6; i++) {
		DRAW_LINEF(((GLfloat)i * 100.0f), 50.0f, ((GLfloat)(i+1) * 100.0f), 50.0f);
	}
	//Line 5
	glLineStipple(5, 0x1C47);
	DRAW_LINEF(0.0f, 25.0f, 600.0f, 25.0f);

	glDisable(GL_LINE_STIPPLE);
	glutSwapBuffers();
}

void Resize(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0f, (GLdouble)w, 0.0f, (GLdouble)h);
}