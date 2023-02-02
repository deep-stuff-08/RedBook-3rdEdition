#include<GL/freeglut.h>

#define MAXZ 8.0f
#define MINZ -8.0f
#define INCZ 0.4f

GLfloat solidZ = MAXZ;
GLfloat transparentZ = MINZ;
GLuint sphereList, cubeList;

void Init(void) {
	GLfloat mat_specular[] = {1.0f, 1.0f, 1.0f, 0.15f};
	GLfloat mat_shininess[] = { 100.0f };
	GLfloat light_position[] = {0.5f, 0.5f, 1.0f, 0.0f};

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

	sphereList = glGenLists(1);
	glNewList(sphereList, GL_COMPILE);
		glutSolidSphere(0.4f, 16, 16);
	glEndList();
	cubeList = glGenLists(1);
	glNewList(cubeList, GL_COMPILE);
		glutSolidCube(0.6f);
	glEndList();
}

void Display() {
	GLfloat mat_solid[] = {0.75f, 0.75f, 0.0f, 1.0f};
	GLfloat mat_zero[] = {0.0f, 0.0f, 0.0f, 1.0f};
	GLfloat mat_transparent[] = {0.0f, 0.8f, 0.8f, 0.6f};
	GLfloat mat_emission[] = {0.0f, 0.3f, 0.3f, 0.6f};

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glTranslatef(-0.15f, -0.15f, solidZ);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_solid);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_zero);
	glCallList(sphereList);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.15f, 0.15f, transparentZ);
	glRotatef(15, 1.0f, 1.0f, 0.0f);
	glRotatef(30, 0.0f, 1.0f, 0.0f);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_transparent);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	glEnable(GL_BLEND);
	glDepthMask(GL_FALSE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glCallList(cubeList);
	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
	glPopMatrix();

	glutSwapBuffers();
}

void Reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w <= h) {
		glOrtho(-1.5f, 1.5f, -1.5f * (GLdouble)h / w, 1.5f * (GLdouble)h / w, -10.0f, 10.0f);
	} else {
		glOrtho(-1.5f * (GLdouble)h / w, 1.5f * (GLdouble)h / w, -1.5f, 1.5f, -10.0f, 10.0f);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Animate(void) {
	if(solidZ <= MINZ || transparentZ >= MAXZ) {
		glutIdleFunc(NULL);
	} else {
		solidZ -= INCZ;
		transparentZ += INCZ;
		glutPostRedisplay();
	}
}

void Keyboard(unsigned char key, int x, int y) {
	switch(key) {
	case 'a': case 'A':
		solidZ = MAXZ;
		transparentZ = MINZ;
		glutIdleFunc(Animate);
		break;
	case 'r': case 'R':
		solidZ = MAXZ;
		transparentZ = MINZ;
		glutPostRedisplay();
		break;
	case 27:
		glutLeaveMainLoop();
		break;
	}
}

int main(int argc, char** argv) {
	glutInit (&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow(argv[0]);
	Init();
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutDisplayFunc(Display);
	glutMainLoop();
}