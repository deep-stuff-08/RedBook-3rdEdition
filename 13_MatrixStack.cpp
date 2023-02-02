#include<GL/freeglut.h>

int main(int argc, char **argv) {
	void Init();
	void Display();
	void Resize(int w, int h);
	void Keyboard(unsigned char key, int x, int y);
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Matrix Stack");
	Init();
	glutDisplayFunc(Display);
	glutReshapeFunc(Resize);
	glutKeyboardFunc(Keyboard);
	glutMainLoop();
	return 0;
}

void Init() {
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);
}

void Display() {
	GLint signVec[4][2] = {
		{1, 1},
		{1, -1},
		{-1, 1},
		{-1, -1}
	};
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -3.0f);
	for(int i = 0; i < 4; i++) {
		glColor3f(0.0f, 1.0f, 0.0f);
		glPushMatrix();
		glTranslatef(1.0f * signVec[i][0], 1.0f * signVec[i][1], 0.0f);
		glBegin(GL_QUADS);
		glVertex2f(0.0f, 0.5f);
		glVertex2f(-0.5f, 0.0f);
		glVertex2f(0.0f, -0.5f);
		glVertex2f(0.5f, 0.0f);
		glEnd();
		glColor3f(0.0f, 1.0f, 1.0f);
		for(int j = 0; j < 4; j++) {
			glPushMatrix();
			glTranslatef(0.5f * signVec[j][0], 0.5f * signVec[j][1], 0.0f);
			glBegin(GL_QUADS);
			glVertex2f(0.1f, 0.1f);
			glVertex2f(-0.1f, 0.1f);
			glVertex2f(-0.1f, -0.1f);
			glVertex2f(0.1f, -0.1f);
			glEnd();				
			glPopMatrix();
		}
		glPopMatrix();
	}
	glutSwapBuffers();
}

void Keyboard(unsigned char key, int x, int y) {
	switch(key) {
	case 27:
		glutLeaveMainLoop();
		break;
	case 'f': case 'F':
		glutFullScreenToggle();
		break;
	}
}

void Resize(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)width/height, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
}