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
	glutCreateWindow("Transformation");
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

void DrawTriangle() {
	glBegin(GL_TRIANGLES);
	glVertex2f(0.0f, 0.5f);
	glVertex2f(-0.5f, -0.5f);
	glVertex2f(0.5f, -0.5f);
	glEnd();
}

void Display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_LINE_STIPPLE);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3f(1.0f, 1.0f, 1.0f);
	DrawTriangle();

	glLineStipple(1, 0xF0F0);
	glColor3f(1.0f, 0.0f, 0.0f);
	glLoadIdentity();
	glTranslatef(-0.6f, 0.0f, 0.0f);
	DrawTriangle();

	glLineStipple(1, 0xF00F);
	glColor3f(0.0f, 1.0f, 0.0f);
	glLoadIdentity();
	glScalef(1.5f, 0.5f, 1.0f);
	DrawTriangle();

	glLineStipple(1, 0x8888);
	glColor3f(0.0f, 0.0f, 1.0f);
	glLoadIdentity();
	glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
	DrawTriangle();

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
}