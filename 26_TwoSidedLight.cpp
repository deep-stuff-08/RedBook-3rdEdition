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
	}
}

void Resize(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w >= h) {
		glOrtho(-1.0 * (GLfloat)w / h, 1.0 * (GLfloat)w / h, -1.0f, 1.0f, -1.0f, 1.0f);
	} else {
		glOrtho(-1.0, 1.0f, -1.0 * (GLfloat)w / h, 1.0 * (GLfloat)w / h, -1.0f, 1.0f);
	}
}

void Init() {
	GLfloat ambient_light[] = {0.3f, 0.3f, 0.3f, 0.0f};
	GLfloat light_pos[] = { 0.0f, 1.0f, 1.0f, 1.0f};
	GLdouble clipPlane[] = {1.0f, 0.0f, -0.5f, 0.2f}; 

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glClipPlane(GL_CLIP_PLANE0, clipPlane);
	glEnable(GL_CLIP_PLANE0);
	
	glShadeModel(GL_SMOOTH);
	
	glDepthFunc(GL_LEQUAL);

	glEnable(GL_DEPTH_TEST);
}

void Display() {
	GLfloat outer_diffuse[] = {0.0f, 1.0f, 0.0f};
	GLfloat inner_diffuse[] = {0.0f, 0.0f, 1.0f};

	GLfloat default_ambient[] = {0.2f, 0.2f, 0.2f};
	GLfloat outer_ambient[] = {0.6f, 0.6f, 0.0f};
	GLfloat inner_ambient[] = {0.0f, 0.6f, 0.6f};

	GLfloat specular[] = {1.0f, 1.0f, 1.0f};
	GLfloat shinines = 20.0f;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Row 1 Col 1
	glMaterialfv(GL_FRONT, GL_DIFFUSE, outer_diffuse);
	glPushMatrix();
	glTranslatef(-0.8f, 0.7f, 0.0f);
	glutSolidSphere(0.3f, 30, 30);
	glPopMatrix();
	//Row 1 Col 2
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, outer_diffuse);
	glPushMatrix();
	glTranslatef(0.0f, 0.7f, 0.0f);
	glutSolidSphere(0.3f, 30, 30);
	glPopMatrix();
	//Row 1 Col 3
	glMaterialfv(GL_BACK, GL_DIFFUSE, inner_diffuse);
	glPushMatrix();
	glTranslatef(0.8f, 0.7f, 0.0f);
	glutSolidSphere(0.3f, 30, 30);
	glPopMatrix();
	//Row 2 Col 1
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
	glMaterialfv(GL_FRONT, GL_AMBIENT, outer_ambient);
	glPushMatrix();
	glTranslatef(-0.8f, 0.0f, 0.0f);
	glutSolidSphere(0.3f, 30, 30);
	glPopMatrix();
	//Row 2 Col 2
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, outer_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, outer_diffuse);
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	glutSolidSphere(0.3f, 30, 30);
	glPopMatrix();
	//Row 2 Col 3
	glMaterialfv(GL_BACK, GL_AMBIENT, inner_ambient);
	glMaterialfv(GL_BACK, GL_DIFFUSE, inner_diffuse);
	glPushMatrix();
	glTranslatef(0.8f, 0.0f, 0.0f);
	glutSolidSphere(0.3f, 30, 30);
	glPopMatrix();
	//Row 3 Col 1
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, default_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT, GL_SHININESS, shinines);
	glPushMatrix();
	glTranslatef(-0.8f, -0.7f, 0.0f);
	glutSolidSphere(0.3f, 30, 30);
	glPopMatrix();
	//Row 3 Col 2
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shinines);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, outer_diffuse);
	glPushMatrix();
	glTranslatef(0.0f, -0.7f, 0.0f);
	glutSolidSphere(0.3f, 30, 30);
	glPopMatrix();
	//Row 3 Col 3
	glMaterialfv(GL_BACK, GL_DIFFUSE, inner_diffuse);
	glPushMatrix();
	glTranslatef(0.8f, -0.7f, 0.0f);
	glutSolidSphere(0.3f, 30, 30);
	glPopMatrix();
	glutSwapBuffers();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowPosition(10, 10);
	glutInitWindowSize(900, 700);
	glutCreateWindow(argv[0]);
	Init();
	glutDisplayFunc(Display);
	glutReshapeFunc(Resize);
	glutKeyboardFunc(Keyboard);
	glutMainLoop();
}