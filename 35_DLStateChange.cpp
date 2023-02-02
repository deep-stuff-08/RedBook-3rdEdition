#include<GL/freeglut.h>

GLuint displayTri;

void init(void) {
	displayTri = glGenLists(1);
	glNewList(displayTri, GL_COMPILE);
		glColor3f(1.0f, 0.0f, 0.0f);
		glBegin(GL_TRIANGLES);
			glVertex2f(0.0f, 0.0f);
			glVertex2f(0.1f, 0.0f);
			glVertex2f(0.0f, 0.1f);
		glEnd();
		glTranslatef(0.15f, 0.0f, 0.0f);
	glEndList();
	glShadeModel(GL_FLAT);
}

void drawLine(void) {
	glBegin(GL_LINES);
		glVertex2f(0.0f, 0.5f);
		glVertex2f(15.0f, 0.5f);
	glEnd();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0f, 1.0f, 0.0f);

	for(GLuint i = 0; i < 10; i++) {
		glCallList(displayTri);
	}
	drawLine();
	glutSwapBuffers();
}

void resize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w <= h) {
		gluOrtho2D(0.0, 2.0, -0.5 * (GLdouble)h / w, 1.5 * (GLdouble)h / w);
	} else {
		gluOrtho2D(0.0, 2.0 * (GLdouble)w / h, -0.5, 1.5);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y) {
	switch(key) {
	case 27:
		glutLeaveMainLoop();
		break;
	}
}

int main(int argc, char **argv) {
	glutInitWindowSize(500, 500);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow(argv[0]);
	init();
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}