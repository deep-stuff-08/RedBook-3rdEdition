#include<GL/freeglut.h>
#include<stdio.h>

void Keyboard(unsigned char key, int kx, int ky) {
	switch(key) {
	case 27:
		glutLeaveMainLoop();
		break;
	case 'F': case 'f':
		glutFullScreenToggle();
		break;
	case 'L': case 'l':
		glutPostRedisplay();
		break;
	}
}

void Resize(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w <= h) {
		glOrtho(-1.5, 1.5, -1.5 * (GLdouble)h / (GLdouble)w, 1.5 * (GLdouble)h / (GLdouble)w, -10.0, 10.0);
	} else {
		glOrtho(-1.5 * (GLdouble)w / (GLdouble)h, 1.5 * (GLdouble)w / (GLdouble)h, -1.5, 1.5, -10.0, 10.0);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Init() {
	
	GLfloat mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat mat_shininess = 50.0f;

	GLfloat l_ambient[] = {0.2f, 0.2f, 0.2f, 1.0f};
	GLfloat l_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat l_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat l_position[] = {-1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat spot_direction[] = {1.0f, -1.0f, 0.0f};
	GLfloat lmodel_ambient[] = {0.4f, 0.4f, 0.4f, 1.0f}; 

	glLightfv(GL_LIGHT0, GL_AMBIENT, l_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, l_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, l_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, l_position);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.5f);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.5f);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.2f);

	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 80.0f);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 2.0f);

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);
	
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	
	glShadeModel(GL_SMOOTH);
	
	glDepthFunc(GL_LEQUAL);

	glEnable(GL_DEPTH_TEST);
}

void Display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutSolidSphere(1.0f, 50, 50);
	glutSwapBuffers();
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