#include<GL/freeglut.h>

bool isRot = true;
GLint rot = 0;

int main(int argc, char **argv) {
	void Init();
	void Display();
	void Resize(int w, int h);
	void Keyboard(unsigned char key, int x, int y);
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Clipping Planes");
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
	static GLfloat rotate = 0.0f;
	GLdouble eqn1[] = {0.0, 1.0, 0.0, 0.0};
	GLdouble eqn2[] = {1.0, 0.0, 0.0, 0.0};
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -5.0f);

	if(isRot) {
		glRotatef(rot, 1.0f, 1.0f, 1.0f);
	}

	glClipPlane(GL_CLIP_PLANE0, eqn1);
	glEnable(GL_CLIP_PLANE0);
	
	glClipPlane(GL_CLIP_PLANE1, eqn2);
	glEnable(GL_CLIP_PLANE1);
	
	if(!isRot) {
		glRotatef(rot, 1.0f, 1.0f, 1.0f);
	}

	glRotatef(90, 1.0f, 0.0f, 0.0f);
	glutWireSphere(1.0, 20, 16);
	glPopMatrix();
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
	case 'r': case 'R':
		rot += 3 % 360;
		glutPostRedisplay();
		break;
	case ' ':
		isRot = !isRot;
		glutPostRedisplay();
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