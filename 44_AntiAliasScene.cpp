#include<GL/freeglut.h>
#include<stdlib.h>
#define _USE_MATH_DEFINES
#include<math.h>
#include"jitter.h"

void init() {
	GLfloat mat_ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat light_postion[] = { 0.0f, 0.0f, 10.0f, 1.0f };
	GLfloat lm_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 50.0f);

	glLightfv(GL_LIGHT0, GL_POSITION, light_postion);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lm_ambient);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	
	glShadeModel(GL_FLAT);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearAccum(0.0f, 0.0f, 0.0f, 0.0f);
}

void displayObjects() {
	GLfloat torus_diffuse[] = { 0.7f, 0.7f, 0.0f, 1.0f };
	GLfloat cube_diffuse[] = { 0.0f, 0.7f, 0.7f, 1.0f };
	GLfloat sphere_diffuse[] = { 0.7f, 0.0f, 0.7f, 1.0f };
	GLfloat octa_diffuse[] = { 0.7f, 0.4f, 0.4f, 1.0f };

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -5.0f);
	glRotatef(30.0f, 1.0f, 0.0f, 0.0f);
	
	glPushMatrix();
	glTranslatef(-0.8f, 0.35f, 0.0f);
	glRotatef(100.0f, 1.0f, 0.0f, 0.0f);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, torus_diffuse);
	glutSolidTorus(0.275f, 0.85f, 16, 16);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.75f, -0.5f, 0.0f);
	glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
	glRotatef(45.0f, 1.0f, 0.0f, 0.0f);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, cube_diffuse);
	glutSolidCube(1.5f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.75f, 0.6f, 0.0f);
	glRotatef(30.0f, 1.0f, 0.0f, 0.0f);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, sphere_diffuse);
	glutSolidSphere(1.0f, 16, 16);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.7f, -0.9f, 0.25f);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, octa_diffuse);
	glutSolidOctahedron();
	glPopMatrix();

	glPopMatrix();
}

void accFrustrum(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar, GLdouble pixdx, GLdouble pixdy, GLdouble eyedx, GLdouble eyedy, GLdouble focus) {
	GLdouble xwsize, ywsize;
	GLdouble dx, dy;
	GLint viewport[4];

	glGetIntegerv(GL_VIEWPORT, viewport);

	xwsize = right - left;
	ywsize = top - bottom;

	dx = -(pixdx * xwsize / (GLdouble) viewport[2] + eyedx * zNear / focus);
	dy = -(pixdy * ywsize / (GLdouble) viewport[3] + eyedy * zNear / focus);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(left + dx, right + dx, bottom + dy, top + dy, zNear, zFar);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(-eyedx, -eyedy, 0.0f);
}

void accPerspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar, GLdouble pixdx, GLdouble pixdy, GLdouble eyedx, GLdouble eyedy, GLdouble focus) {
	GLdouble fov2, left, right, bottom, top;

	fov2 = ((fovy * M_PI) / 180.0f) / 2.0f;

	top = zNear / (cos(fov2) / sin(fov2));
	bottom  = -top;
	right = top * aspect;
	left = -right;

	accFrustrum(left, right, bottom, top, zNear, zFar, pixdx, pixdy, eyedx, eyedy, focus);
}

#define ACSIZE 8

void display() {
	GLint viewport[4];
	int jitter;

	glGetIntegerv(GL_VIEWPORT, viewport);

	glClear(GL_ACCUM_BUFFER_BIT);
	for(jitter = 0; jitter < ACSIZE; jitter++) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		accPerspective(50.0f, (GLdouble) viewport[2] / viewport[3], 1.0f, 15.0f, j8[jitter].x, j8[jitter].y, 0.0f, 0.0f, 1.0f);
		displayObjects();
		glAccum(GL_ACCUM, 1.0f / ACSIZE);
	}
	glAccum(GL_RETURN, 1.0f);
	glFlush();
}

void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

void Keyboard(unsigned char key, int x, int y) {
	switch(key) {
	case 'F': case 'f':
		glutFullScreenToggle();
		break;
	case 27:
		glutLeaveMainLoop();
		break;
	default:
		break;
	}
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_ACCUM);
	glutInitWindowPosition(10, 10);
	glutInitWindowSize(500, 500);
	glutCreateWindow(argv[0]);
	init();
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(Keyboard);
	glutMainLoop();
	return 0;
}
