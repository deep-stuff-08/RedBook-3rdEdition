#include<GL/freeglut.h>
#include<stdio.h>

bool gbLight = false;

void Keyboard(unsigned char key, int kx, int ky) {
	switch(key) {
	case 27:
		glutLeaveMainLoop();
		break;
	case 'F': case 'f':
		glutFullScreenToggle();
		break;
	case 'L': case 'l':
		gbLight = !gbLight;
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
	GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_shininess[] = { 50.0f };
	GLfloat white_light[] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat lmodel_ambient[] = {0.4f, 0.4f, 0.4f, 1.0f};
	GLfloat light_pos[] = { 1.0f, 1.0f, 1.0f };

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	glEnable(GL_LIGHTING);
	
	glShadeModel(GL_SMOOTH);
	
	glDepthFunc(GL_LEQUAL);

	glEnable(GL_DEPTH_TEST);
}

void Display() {
	if(gbLight) {
		glEnable(GL_LIGHT0);
	} else {
		glDisable(GL_LIGHT0);
	}
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
	printf("Press 'L': Toggle Lighting\n");
	glutDisplayFunc(Display);
	glutReshapeFunc(Resize);
	glutKeyboardFunc(Keyboard);
	glutMainLoop();
}