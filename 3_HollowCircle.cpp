#include<math.h>
#include<GL/freeglut.h>

#define PI 3.1415926535898

#pragma comment(lib, "freeglut.lib")

GLenum circle_type = GL_LINE_LOOP;

int main(int argc, char **argv) {
	void Init();
	void Display();
	void Resize(int w, int h);
	void Keyboard(unsigned char key, int x, int y);
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Hollow Circle");
	Init();
	glutDisplayFunc(Display);
	glutReshapeFunc(Resize);
	glutKeyboardFunc(Keyboard);
	glutMainLoop();
	return 0;
}

void Init() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glLineWidth(1.0f);
}

void Keyboard(unsigned char key, int x, int y) {
	switch(key) {
	case 's': case 'S':
		if(circle_type == GL_LINE_LOOP) {
			circle_type = GL_TRIANGLE_FAN;
		} else {
			circle_type = GL_LINE_LOOP; 
		}
		glutPostRedisplay();
		break;
	case 'f': case 'F':
		glutFullScreenToggle();
		break;
	case 27:
		glutLeaveMainLoop();
		break;
	}
}

void Resize(int width, int height) {
	if(width == 0) {
		width = 1;
	}
	glViewport(0, 0, width, height);
}

void Display() {
	GLint circle_points = 100;
	GLdouble angle;
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(circle_type);
	for(int i = 0; i < circle_points; i++) {
		angle = 2 * PI * i / circle_points;
		glVertex2f(cos(angle) * 0.5, sin(angle) * 0.5);
	}
	glEnd();
	glutSwapBuffers();
}