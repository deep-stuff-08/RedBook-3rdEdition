#include<GL/freeglut.h>
#include<math.h>
#include<stdio.h>

GLint fogmode;

void Init(void) {
	GLfloat position[] = {0.5f, 0.5f, 3.0f, 0.0f};

	glEnable(GL_DEPTH_TEST);

	glLightfv(GL_LIGHT0, GL_POSITION, position);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	{
		GLfloat mat[3] = {0.1745f, 0.01175f, 0.01175f};
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat);
		mat[0] = 0.61424f; mat[1] = 0.04136f; mat[2] = 0.04136f;
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
		mat[0] = 0.727811f; mat[1] = 0.626959f; mat[2] = 0.626959f;
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat);
		glMaterialf(GL_FRONT, GL_SHININESS, 0.6f * 128.0f);
	}

	glEnable(GL_FOG);

	{
		GLfloat fogColor[4] = {0.5f, 0.5f, 0.5f, 1.0f};
		fogmode = GL_EXP;
		glFogi(GL_FOG_MODE, fogmode);
		glFogfv(GL_FOG_COLOR, fogColor);
		glFogf(GL_FOG_DENSITY, 0.35f);
		glHint(GL_FOG_HINT, GL_DONT_CARE);
		glFogf(GL_FOG_START, 1.0f);
		glFogf(GL_FOG_END, 5.0f);
	}
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClearDepth(1.0f);
}

void drawSphere(GLfloat x, GLfloat y, GLfloat z) {
	glPushMatrix();
	glTranslatef(x, y, z);
	glutSolidSphere(0.4f, 16, 16);
	glPopMatrix();
}

void Display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawSphere(-2.0f, -0.5f, -1.0f);
	drawSphere(-1.0f, -0.5f, -2.0f);
	drawSphere(0.0f, -0.5f, -3.0f);
	drawSphere(1.0f, -0.5f, -4.0f);
	drawSphere(2.0f, -0.5f, -5.0f);
	glutSwapBuffers();
}

void Reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w <= h) {
		glOrtho(-2.5f, 2.5f, -2.5f * (GLfloat)h / w, 2.5f * (GLfloat)h / w, -10.0f, 10.0f);
	} else {
		glOrtho(-2.5f * (GLfloat)w / h, 2.5f * (GLfloat)w / h, -2.5f, 2.5f, -10.0f, 10.0f);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Keyboard(unsigned char key, int x, int y) {
	switch(key) {
	case 'f': case 'F':
		glutFullScreenToggle();
		break;
	case ' ':
		if(fogmode == GL_EXP) {
			fogmode = GL_EXP2;
		} else if(fogmode == GL_EXP2) {
			fogmode = GL_LINEAR;
		} else if(fogmode == GL_LINEAR) {
			fogmode = GL_EXP;
		}
		glFogi(GL_FOG_MODE, fogmode);
		glutPostRedisplay();
		break;
	case 27:
		glutLeaveMainLoop();
		break;
	}
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(10, 10);
	glutCreateWindow(argv[0]);
	Init();
	printf("Press 'SPACE': Toggle between Linear, Exponential and Exponential2 Fog\n");
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutDisplayFunc(Display);
	glutMainLoop();
	return 0;
}