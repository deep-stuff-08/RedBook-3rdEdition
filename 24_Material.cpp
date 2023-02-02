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
	GLfloat white_light[] = {1.0f, 1.0f, 1.0f, 0.0f};
	GLfloat light_pos[] = { 0.0f, 5.0f, 10.0f , 2.0f};

	glClearColor(0.3f, 0.3f, 0.3f, 0.0f);
	glClearDepth(1.0f);
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, white_light);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glShadeModel(GL_SMOOTH);
	
	glDepthFunc(GL_LEQUAL);

	glEnable(GL_DEPTH_TEST);
}

void Display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	GLfloat mat_none[] = {0.0f, 0.0f, 0.0f, 1.0f};
	GLfloat mat_ambience_grey[] = {0.3f, 0.3f, 0.3f, 1.0f};
	GLfloat mat_ambience_blue[] = {0.0f, 0.6f, 0.0f, 1.0f};
	GLfloat mat_diffuse_blue[] = {0.0f, 0.0f, 1.0f, 1.0f};
	GLfloat mat_specular_white[] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat mat_shineness_low = 5.0f;
	GLfloat mat_shineness_high = 100.0f;
	GLfloat mat_emission[] = {0.3f, 0.3f, 0.3f, 1.0f};

	//Row 1 Column 1
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_none);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse_blue);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_none);
	glPushMatrix();
	glTranslatef(-0.9f, 0.6f, 0.0f);
	glutSolidSphere(0.2f, 50, 50);
	glPopMatrix();
	//Row 2 Column 1
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambience_grey);
	glPushMatrix();
	glTranslatef(-0.9f, 0.0f, 0.0f);
	glutSolidSphere(0.2f, 50, 50);
	glPopMatrix();
	//Row 3 Column 1
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambience_blue);
	glPushMatrix();
	glTranslatef(-0.9f, -0.6f, 0.0f);
	glutSolidSphere(0.2f, 50, 50);
	glPopMatrix();
	//Row 1 Column 2
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_none);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular_white);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shineness_low);
	glPushMatrix();
	glTranslatef(-0.3f, 0.6f, 0.0f);
	glutSolidSphere(0.2f, 50, 50);
	glPopMatrix();
	//Row 2 Column 2
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambience_grey);
	glPushMatrix();
	glTranslatef(-0.3f, 0.0f, 0.0f);
	glutSolidSphere(0.2f, 50, 50);
	glPopMatrix();
	//Row 3 Column 2
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambience_blue);
	glPushMatrix();
	glTranslatef(-0.3f, -0.6f, 0.0f);
	glutSolidSphere(0.2f, 50, 50);
	glPopMatrix();
	//Row 1 Column 3
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_none);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shineness_high);
	glPushMatrix();
	glTranslatef(0.3f, 0.6f, 0.0f);
	glutSolidSphere(0.2f, 50, 50);
	glPopMatrix();
	//Row 2 Column 3
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambience_grey);
	glPushMatrix();
	glTranslatef(0.3f, 0.0f, 0.0f);
	glutSolidSphere(0.2f, 50, 50);
	glPopMatrix();
	//Row 3 Column 3
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambience_blue);
	glPushMatrix();
	glTranslatef(0.3f, -0.6f, 0.0f);
	glutSolidSphere(0.2f, 50, 50);
	glPopMatrix();
	//Row 1 Column 4
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_none);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_none);
	glMaterialf(GL_FRONT, GL_SHININESS, 0.0f);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	glPushMatrix();
	glTranslatef(0.9f, 0.6f, 0.0f);
	glutSolidSphere(0.2f, 50, 50);
	glPopMatrix();
	//Row 2 Column 4
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambience_grey);
	glPushMatrix();
	glTranslatef(0.9f, 0.0f, 0.0f);
	glutSolidSphere(0.2f, 50, 50);
	glPopMatrix();
	//Row 3 Column 4
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambience_blue);
	glPushMatrix();
	glTranslatef(0.9f, -0.6f, 0.0f);
	glutSolidSphere(0.2f, 50, 50);
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