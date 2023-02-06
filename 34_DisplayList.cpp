#include<GL/freeglut.h>
#define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>

GLuint idTorus;

void torus(int numc, int numt) {
	int i, j, k;
	double s, t, x, y, z, nx, ny, nz, twopi;

	twopi = 2.0 * M_PI;
	for(int i = 0; i < numc; i++) {
		glBegin(GL_QUAD_STRIP);
		for(int j = 0; j <= numt; j++) {
			for(int k = 1; k >= 0; k--) {
				s = (i + k) % numc + 0.5;
				t = j % numt;

				nx = cos(s * twopi / numc) * cos(t * twopi / numt);
				ny = cos(s * twopi / numc) * sin(t * twopi / numt);
				nz = sin(s * twopi / numc);

				x = (1.5 + 0.4 * cos(s * twopi / numc)) * cos(t * twopi / numt);  
				y = (1.5 + 0.4 * cos(s * twopi / numc)) * sin(t * twopi / numt);
				z = 0.4 * nz;

				glNormal3f(nx, ny, nz);
				glVertex3f(x, y, z);
			}
		}
		glEnd();
	}
}

void init(void) {
	GLfloat ambient[] = {0.0f, 0.0f, 0.0f, 1.0f};
	GLfloat diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat position1[] = {0.0f, 1.0f, 1.0f, 0.0f};
	GLfloat amb_dif[] = {0.7f, 0.5f, 1.0f, 1.0f};
	GLfloat specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat shininess = 60.0f;
	
	idTorus = glGenLists(1);
	glNewList(idTorus, GL_COMPILE);
	torus(2000, 2000);
	glEndList();

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, position1);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, amb_dif);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

	glEnable(GL_BLEND);
	glEnable(GL_POLYGON_SMOOTH);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_FLAT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0f, 1.0f, 1.0f);
	glCallList(idTorus);
	glutSwapBuffers();
	glutPostRedisplay();
}

void resize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30, (GLfloat)w / h, 1.0f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);
}

void keyboard(unsigned char key, int x, int y) {
	switch(key) {
	case 'F': case 'f':
		glutFullScreenToggle();
		break;
	case 'x': case 'X':
		glRotatef(30, 1.0f, 0.0f, 0.0f);
		glutPostRedisplay();
		break;
	case 'y': case 'Y':
		glRotatef(30, 0.0f, 1.0f, 0.0f);
		glutPostRedisplay();
		break;
	case 'i': case 'I':
		glLoadIdentity();
		gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);
		glutPostRedisplay();
		break;
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
	printf("Press 'X': Rotate on X Axis\n");
	printf("Press 'Y': Rotate on Y Axis\n");
	printf("Press 'I': Reset Torus\n");
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}