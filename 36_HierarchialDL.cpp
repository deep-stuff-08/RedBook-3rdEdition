#include<GL/freeglut.h>
#define _USE_MATH_DEFINES
#include<math.h>

GLuint icecream;

void cone(GLfloat height, GLfloat radius) {
	const GLint stacks = 300, slices = 300;
	GLfloat x, y, z;
	GLfloat nx, ny, nz;
	GLfloat theta;
	GLfloat delta_nh = 1.0f;
	GLfloat delta_h = height / 2;
	GLfloat delta_r = radius;
	GLfloat r_dec = radius / stacks;
	GLfloat nh_dec = 2.0f / stacks;
	GLfloat h_dec = height / stacks;

	for(int i = 0; i < stacks; i++) {
		glBegin(GL_QUAD_STRIP);
		for(int j = 0; j <= slices; j++) {
			theta = 2.0f * M_PI * ((GLfloat)j / slices);
			nx = cos(theta);
			ny = delta_nh;
			nz = sin(theta);
			x = nx * delta_r;
			y = delta_h;
			z = nz * delta_r;
			glNormal3f(nx, ny, nz);
			glVertex3f(x, y, z);
			x = nx * (delta_r - r_dec);
			z = nz * (delta_r - r_dec);
			glNormal3f(nx, ny - nh_dec, nz);
			glVertex3f(x, y - h_dec, z);
		}
		glEnd();
		delta_nh -= nh_dec;
		delta_h -= h_dec;
		delta_r -= r_dec;
	}
}

void sphere(GLfloat radius) {
	const GLint stacks = 300, slices = 300;
	GLfloat x, y, z;
	GLfloat nx, ny, nz;
	GLfloat theta, phi_1, phi_2;

	for(int i = 0; i < stacks; i++) {
		phi_1 = M_PI * i / stacks; 
		phi_2 = M_PI * (i + 1) / stacks;

		glBegin(GL_QUAD_STRIP);
		for(int j = 0; j <= slices; j++) {
			theta = 2.0f * M_PI * j / slices;
		
			nx = cos(theta) * cos(phi_1);
			ny = sin(theta);
			nz = cos(theta) * sin(phi_1); 
		
			x = nx * radius;
			y = ny * radius;
			z = nz * radius;
		
			glNormal3f(nx, ny, nz);
			glVertex3f(x, y, z);
		
			nx = cos(theta) * cos(phi_2);
			ny = sin(theta);
			nz = cos(theta) * sin(phi_2); 
		
			x = nx * radius;
			y = ny * radius;
			z = nz * radius;
		
			glNormal3f(nx, ny, nz);
			glVertex3f(x, y, z);
		}
		glEnd();
	}
}

void init(void) {
	GLuint sphere_list;
	GLfloat ambient[] = {0.0f, 0.0f, 0.0f, 1.0f};
	GLfloat diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat position1[] = {0.0f, 1.0f, 1.0f, 0.0f};
	GLfloat amb_dif[] = {0.3f, 1.0f, 1.0f, 1.0f};
	GLfloat specular[] = {0.0f, 0.0f, 0.0f, 1.0f};
	GLfloat shininess = 1.0f;
	
	sphere_list = glGenLists(1);
	glNewList(sphere_list, GL_COMPILE);
	sphere(0.7f);
	glEndList();

	icecream = glGenLists(1);
	glNewList(icecream, GL_COMPILE);
	glPushMatrix();
	glTranslatef(0.0f, -1.0f, 0.0f);
	cone(2.0f, 0.6f);
	glTranslatef(0.0f, 1.3f, 0.0f);
	glCallList(sphere_list);
	glTranslatef(0.0f, 0.6f, 0.0f);
	glCallList(sphere_list);
	glPopMatrix();
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
	glCallList(icecream);
	glutSwapBuffers();
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
	case 'x': case 'X':
		glRotatef(3, 1.0f, 0.0f, 0.0f);
		glutPostRedisplay();
		break;
	case 'y': case 'Y':
		glRotatef(3, 0.0f, 1.0f, 0.0f);
		glutPostRedisplay();
		break;
	case 'z': case 'Z':
		glRotatef(3, 0.0f, 0.0f, 1.0f);
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
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}