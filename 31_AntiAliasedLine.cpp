#include<GL/freeglut.h>
#include<stdio.h>

static int rot = 20;
bool isAntiAliasOn = false;

void Init(void) {
	GLfloat values[2];
	glGetFloatv(GL_LINE_WIDTH_GRANULARITY, values);
	printf("LINE_WIDTH_GRANULARITY = %3.1f\n", values[0]);
	printf("LINE_WIDTH_RANGE = %3.1f - %3.1f\n", values[0], values[1]);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glLineWidth(10.0f);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void Display() {
	glClear(GL_COLOR_BUFFER_BIT);

	if(isAntiAliasOn) {
		glEnable(GL_BLEND);
		glEnable(GL_LINE_SMOOTH);
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	} else {
		glDisable(GL_BLEND);
		glDisable(GL_LINE_SMOOTH);
		glHint(GL_LINE_SMOOTH_HINT, GL_FASTEST);
	}
	glColor3f(0.0f, 1.0f, 0.0f);
	glPushMatrix();
	glRotatef(-rot, 0.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
		glVertex2f(-0.5f, 0.5f);
		glVertex2f(0.5f, -0.5f);
	glEnd();
	glPopMatrix();

	glColor3f(0.0f, 0.0f, 1.0f);
	glPushMatrix();
	glRotatef(rot, 0.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
		glVertex2f(0.5f, 0.5f);
		glVertex2f(-0.5f, -0.5f);
	glEnd();
	glPopMatrix();

	glutSwapBuffers();
}

void Reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w<=h) {
		gluOrtho2D(-1.0, 1.0, -1.0 * (GLfloat)w / h,  -1.0 * (GLfloat)w / h);
	} else {
		gluOrtho2D(-1.0 * (GLfloat)w / h,  -1.0 * (GLfloat)w / h, -1.0f, 1.0f);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Keyboard(unsigned char key, int x, int y) {
	switch(key) {
	case 'r': case 'R':
		rot += 2 % 360;
		glutPostRedisplay();
		break;
	case 27:
		glutLeaveMainLoop();
		break;
	case 'f': case 'F':
		glutFullScreenToggle();
		break;
	case ' ':
		isAntiAliasOn = !isAntiAliasOn;
		glutPostRedisplay();
		break;
	}
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutCreateWindow(argv[0]);
	Init();

	glutReshapeFunc(Reshape);
	glutDisplayFunc(Display);
	glutKeyboardFunc(Keyboard);
	glutMainLoop();
}