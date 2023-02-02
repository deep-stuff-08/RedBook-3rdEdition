#include<GL/freeglut.h>

void Resize(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLdouble)w / (GLdouble)h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
}

void Init() {
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);
}

void Display() {
	glShadeModel(GL_SMOOTH);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -5.0f);
	glPushMatrix();
	glTranslatef(-1.0f, 0.0f ,0.0f);
	glColor3f(0.5f, 0.0f, 0.0f);
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(0.0f, 1.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(-1.0f, -1.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2f(1.0f, -1.0f);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(1.0f, 0.0f, 0.0f);
	glShadeModel(GL_FLAT);
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(0.0f, 1.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(-1.0f, -1.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2f(1.0f, -1.0f);
	glEnd();
	glPopMatrix();
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

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow(argv[0]);
	Init();
	glutDisplayFunc(Display);
	glutReshapeFunc(Resize);
	glutKeyboardFunc(Keyboard);
	glutMainLoop();
}