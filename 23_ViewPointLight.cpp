#include<GL/freeglut.h>
#include<math.h>

GLfloat angle1 = 0.0f;
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
	glutDisplayFunc(Display);
	glutReshapeFunc(Resize);
	glutKeyboardFunc(Keyboard);
	glutMainLoop();
	return 0;
}

void Init() {
	GLfloat light[] = {0.0f, 1.0f, 1.0f, 1.0f};

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light);
}

void Display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	gluLookAt(sin(angle1) * 6.0f, 0.0f, cos(angle1) * 6.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	glutSolidTorus(0.275, 0.85, 8, 15);
	glPopMatrix();
	glutSwapBuffers();
}

void Keyboard(unsigned char key, int x, int y) {
	switch(key) {
	case 27:
		glutLeaveMainLoop();
		break;
	case 'y':
		angle1 += 0.1f;
		if(angle1 >= 360.0f) {
			angle1 -= 360.0f;
		}
		glutPostRedisplay();
		break;
	case 'Y':
		angle1 -= 0.1f;
		if(angle1 <= 0.0f) {
			angle1+= 360.0f;
		}
		glutPostRedisplay();
		break;
	case 'f': case 'F':
		glutFullScreenToggle();
		break;
	}
}

void Resize(int width, int height) {
	GLfloat postion[] = {0.0f, 0.0f, 0.0f, 1.0f};
	
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40.0f, (GLfloat)width / (GLfloat)height, 1.0f, 20.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glLightfv(GL_LIGHT0, GL_POSITION, postion);
}