#include<GL/freeglut.h>

#define SPEED 0.1

#pragma comment(lib, "freeglut.lib")

GLenum type = GL_FILL;
GLfloat rotate = 0.0f;
bool gbAnim = true;

int main(int argc, char **argv) {
	void Init();
	void Display();
	void Reshape(int w, int h);
	void Update(void);
	void Keyboard(unsigned char key, int x, int y);
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Edge Flag");
	Init();
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutIdleFunc(Update);
	glutMainLoop();
	return 0;
}


void Keyboard(unsigned char key, int x, int y) {
	switch(key) {
	case 'F': case 'f':
		glutFullScreenToggle();
		break;
	case 'T': case 't':
		if(type == GL_LINE) {
			type = GL_FILL;
		} else {
			type = GL_LINE;
		}
		break;
	case 27:
		glutLeaveMainLoop();
		break;
	case ' ':
		gbAnim = !gbAnim;
		break;
	}
}

void Update() {
	if(gbAnim) {
		rotate += SPEED;
		if(rotate >= 360.0f) {
			rotate -= 360.0f;
		}
	}
	glutPostRedisplay();
}

void Display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(rotate, 1.0f, 1.0f, 1.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glPolygonMode(GL_FRONT_AND_BACK, type);
	glBegin(GL_TRIANGLES);
	//T1
	glEdgeFlag(GL_TRUE);
	glVertex2f(-0.6f, 0.6f);
	glEdgeFlag(GL_FALSE);
	glVertex2f(-0.5f, 0.0f);
	glEdgeFlag(GL_TRUE);
	glVertex2f(0.0f, 0.3f);
	//T2
	glEdgeFlag(GL_FALSE);
	glVertex2f(0.0f, 0.3f);
	glEdgeFlag(GL_TRUE);
	glVertex2f(-0.5f, 0.0f);
	glEdgeFlag(GL_FALSE);
	glVertex2f(0.2f, -0.3f);
	//T3
	glEdgeFlag(GL_FALSE);
	glVertex2f(0.0f, 0.3f);
	glEdgeFlag(GL_TRUE);
	glVertex2f(0.2f, -0.3f);
	glEdgeFlag(GL_FALSE);
	glVertex2f(0.5f, 0.3f);
	//T4
	glEdgeFlag(GL_FALSE);
	glVertex2f(0.0f, 0.3f);
	glEdgeFlag(GL_TRUE);
	glVertex2f(0.5f, 0.3f);
	glEdgeFlag(GL_TRUE);
	glVertex2f(-0.1f, 0.9f);
	glEnd();
	glutSwapBuffers();
}

void Reshape(int width, int height) {
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

void Init() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}