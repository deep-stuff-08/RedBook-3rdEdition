#include<GL/freeglut.h>

static int shoulder = 0, elbow = 0, finger1 = 0, finger2 = 0, finger3 = 0, fingerp1 = 0, fingerp2 = 0, fingerp3 = 0;

int main(int argc, char **argv) {
	void Init();
	void Display();
	void Resize(int w, int h);
	void Keyboard(unsigned char key, int x, int y);
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Robotic Arm");
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
	glPushMatrix();
		glPushMatrix();
			glTranslatef(-2.0f, 1.0f, 0.0f);
			glTranslatef(-1.0f, 0.0f, 0.0f);
			glRotatef((GLfloat) shoulder, 0.0f, 0.0f, 1.0f);
			glTranslatef(1.0f, 0.0f, 0.0f);
			glPushMatrix();
				glScalef(2.0f, 0.4f, 1.0f);
				glutWireCube(1.0);
			glPopMatrix();

			glTranslatef(1.0f, 0.0f, 0.0f);
			glRotatef((GLfloat) elbow, 0.0f, 0.0f, 1.0f);
			glTranslatef(1.0f, 0.0f, 0.0f);
			glPushMatrix();
				glScalef(2.0f, 0.4f, 1.0f);
				glutWireCube(1.0);
			glPopMatrix();
			glTranslatef(1.05f, 0.1f, 0.0f);
			glPushMatrix();
				glTranslatef(0.0f, 0.0f, 0.25f);
				glRotatef((GLfloat) finger1, 0.0f, 0.0f, 1.0f);
				glTranslatef(0.3f, 0.0f, 0.0f);
				glPushMatrix();
					glScalef(0.75f, 0.2f, 0.2f);
					glutWireCube(1.0);
				glPopMatrix();
				glTranslatef(0.38f, 0.0f, 0.0f);
				glRotatef((GLfloat) fingerp1, 0.0f, 0.0f, 1.0f);
				glTranslatef(0.3f, 0.0f, 0.0f);
				glPushMatrix();
					glScalef(0.6f, 0.2f, 0.2f);
					glutWireCube(1.0);
				glPopMatrix();
			glPopMatrix();
			glPushMatrix();
				glRotatef((GLfloat) finger2, 0.0f, 0.0f, 1.0f);
				glTranslatef(0.3f, 0.0f, 0.0f);
				glPushMatrix();
					glScalef(0.75f, 0.2f, 0.2f);
					glutWireCube(1.0);
				glPopMatrix();
				glTranslatef(0.38f, 0.0f, 0.0f);
				glRotatef((GLfloat) fingerp2, 0.0f, 0.0f, 1.0f);
				glTranslatef(0.3f, 0.0f, 0.0f);
				glPushMatrix();
					glScalef(0.6f, 0.2f, 0.2f);
					glutWireCube(1.0);
				glPopMatrix();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0.0f, 0.0f, -0.25f);
				glRotatef((GLfloat) finger3, 0.0f, 0.0f, 1.0f);
				glTranslatef(0.3f, 0.0f, 0.0f);
				glPushMatrix();
					glScalef(0.75f, 0.2f, 0.2f);
					glutWireCube(1.0);
				glPopMatrix();
				glTranslatef(0.38f, 0.0f, 0.0f);
				glRotatef((GLfloat) fingerp3, 0.0f, 0.0f, 1.0f);
				glTranslatef(0.3f, 0.0f, 0.0f);
				glPushMatrix();
					glScalef(0.6f, 0.2f, 0.2f);
					glutWireCube(1.0);
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
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
	case 'S':
		shoulder = (shoulder - 5) % 360;
		glutPostRedisplay();
		break;
	case 's':
		shoulder = (shoulder + 5) % 360;
		glutPostRedisplay();
		break;
	case 'E':
		elbow = (elbow - 5) % 360;
		glutPostRedisplay();
		break;
	case 'e':
		elbow = (elbow + 5) % 360;
		glutPostRedisplay();
		break;
	case 'A':
		finger1 = (finger1 - 5) % 360;
		glutPostRedisplay();
		break;
	case 'a':
		finger1 = (finger1 + 5) % 360;
		glutPostRedisplay();
		break;
	case 'W':
		finger2 = (finger2 - 5) % 360;
		glutPostRedisplay();
		break;
	case 'w':
		finger2 = (finger2 + 5) % 360;
		glutPostRedisplay();
		break;
	case 'D':
		finger3 = (finger3 - 5) % 360;
		glutPostRedisplay();
		break;
	case 'd':
		finger3 = (finger3 + 5) % 360;
		glutPostRedisplay();
		break;
	case 'J':
		fingerp1 = (fingerp1 - 5) % 360;
		glutPostRedisplay();
		break;
	case 'j':
		fingerp1 = (fingerp1 + 5) % 360;
		glutPostRedisplay();
		break;
	case 'I':
		fingerp2 = (fingerp2 - 5) % 360;
		glutPostRedisplay();
		break;
	case 'i':
		fingerp2 = (fingerp2 + 5) % 360;
		glutPostRedisplay();
		break;
	case 'L':
		fingerp3 = (fingerp3 - 5) % 360;
		glutPostRedisplay();
		break;
	case 'l':
		fingerp3 = (fingerp3 + 5) % 360;
		glutPostRedisplay();
		break;
	}
}

void Resize(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0, (GLdouble)width/(GLdouble)height, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}