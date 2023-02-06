#include<GL/freeglut.h>
#include<stdio.h>

GLint rot_x = 0.0f;
GLint rot_y = 0.0f;
GLfloat trans_z = 0.0f;
GLfloat rot_torus = 0.0f;

int main(int argc, char **argv) {
	void Init();
	void Display();
	void Resize(int w, int h);
	void Keyboard(unsigned char key, int x, int y);
	void Update();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(800, 600);
	glutCreateWindow(argv[0]);
	Init();
	printf("Press 'X': Rotate in X\n");
	printf("Press 'Y': Rotate in Y\n");
	printf("Press 'Z': Translate in Z\n");
	glutDisplayFunc(Display);
	glutReshapeFunc(Resize);
	glutKeyboardFunc(Keyboard);
	glutIdleFunc(Update);
	glutMainLoop();
	return 0;
}

void Init() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
}

void Display() {
	GLfloat postion[] = {0.0f, 0.0f, trans_z, 1.0f};
	GLfloat light[] = {0.0f, 1.0f, 0.0f, 1.0f};

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	gluLookAt(0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	glPushMatrix();
	glRotatef(rot_x, 1.0f, 0.0f, 0.0f);
	glRotatef(rot_y, 0.0f, 1.0f, 0.0f);
	glLightfv(GL_LIGHT0, GL_POSITION, postion);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light);
	glTranslatef(0.0f, 0.0f, trans_z);
	glDisable(GL_LIGHTING);
	glColor3f(0.0f, 1.0f, 1.0f);
	glutWireCube(0.1f);
	glEnable(GL_LIGHTING);
	glPopMatrix();
	glRotatef(rot_torus, 1.0f, 1.0f, 1.0f);
	glutSolidTorus(0.275, 0.85, 8, 15);
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
	case 'x':
		rot_x = (rot_x + 3) % 360;
		glutPostRedisplay();
		break;
	case 'X':
		rot_x = (rot_x - 3) % 360;
		glutPostRedisplay();
		break;
	case 'y':
		rot_y = (rot_y + 3) % 360;
		glutPostRedisplay();
		break;
	case 'Y':
		rot_y = (rot_y - 3) % 360;
		glutPostRedisplay();
		break;
	case 'z':
		if(trans_z <= 2.0f) {
			trans_z = trans_z + 0.1f;
		}
		glutPostRedisplay();
		break;
	case 'Z':
		if(trans_z >= -2.0f) {
			trans_z = trans_z - 0.1f;
		}
		glutPostRedisplay();
		break;
	}
}

void Update() {
	rot_torus += 0.1f;
	if(rot_torus >= 360.0f) {
		rot_torus -= 360.0f;
	}
	glutPostRedisplay();
}

void Resize(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40.0f, (GLfloat)width / (GLfloat)height, 1.0f, 20.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}