#include<GL/freeglut.h>
#define YELLOWMAT 1
#define BLUEMAT 2

void init(void) {
	GLfloat yellow_diffuse[] = { 0.7f, 0.7f, 0.0f, 1.0f };
	GLfloat yellow_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	GLfloat blue_diffuse[] = { 0.1f, 0.1f, 0.7f, 1.0f };
	GLfloat blue_specular[] = { 0.1f, 1.0f, 1.0f, 1.0f };

	GLfloat position_one[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	glNewList(YELLOWMAT, GL_COMPILE);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, yellow_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, yellow_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 64.0f);
	glEndList();

	glNewList(BLUEMAT, GL_COMPILE);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, blue_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, blue_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 45.0f);
	glEndList();

	glLightfv(GL_LIGHT0, GL_POSITION, position_one);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);

	glClearStencil(0x0);
	glEnable(GL_STENCIL_TEST);
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glStencilFunc(GL_EQUAL, 0x1, 0x1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
	glCallList(BLUEMAT);
	glutSolidSphere(0.5f, 15, 15);

	glStencilFunc(GL_NOTEQUAL, 0x1, 0x1);
	glPushMatrix();
		glRotatef(45.0f, 0.0f, 1.0f, 1.0f);
		glCallList(YELLOWMAT);
		glutSolidTorus(0.275f, 0.85f, 15, 15);
		glPushMatrix();
			glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
			glutSolidTorus(0.275f, 0.85f, 15, 15);
		glPopMatrix();
	glPopMatrix();
	glFlush();
}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if(w <= h) {
		gluOrtho2D(-3.0f, 3.0f, -3.0f * (GLfloat)h / w, 3.0f * (GLfloat)h / w);
	} else {
		gluOrtho2D(-3.0f * (GLfloat)w / h, 3.0f * (GLfloat)w / h, -3.0f, 3.0f);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glClear(GL_STENCIL_BUFFER_BIT);
	glStencilFunc(GL_ALWAYS, 0x1, 0x1);
	glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);

	glBegin(GL_QUADS);
		glVertex2f(-1.0f, 0.0f);
		glVertex2f(0.0f, 1.0f);
		glVertex2f(1.0f, 0.0f);
		glVertex2f(0.0f, -1.0f);
	glEnd();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)w / h, 3.0f, 7.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -5.0f);
}

void keyboard(unsigned char key, int x, int y) {
	switch(key) {
	case 'F': case 'f':
		glutFullScreenToggle();
		break;
	case 27:
		glutLeaveMainLoop();
		break;
	}
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH | GLUT_STENCIL);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(10, 10);
	glutCreateWindow(argv[0]);
	init();
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}