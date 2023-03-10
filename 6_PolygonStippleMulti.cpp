#include<GL/freeglut.h>
#include<stdio.h>

#define SPEED 0.1

GLfloat rotate = 0.0f;
bool gbAnim = true;

int main(int argc, char **argv) {
	void Init(void);
	void Display(void);
	void Reshape(int w, int h);
	void Keyboard(unsigned char key, int x, int y);
	void Update(void);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Polygon Stipple Front and Back");
	Init();
	printf("Press SPACE: Toggle Animation On/Off\n");
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
	GLubyte xsign[] = {
		0xf8, 0x00, 0x00, 0x1f,
		0xfc, 0x00, 0x00, 0x3f,
		0xfe, 0x00, 0x00, 0x7f,
		0xff, 0x00, 0x00, 0xff,
		0xff, 0x80, 0x01, 0xff,
		0x7f, 0xc0, 0x03, 0xfe,
		0x3f, 0xe0, 0x07, 0xfc,
		0x1f, 0xf0, 0x0f, 0xf8,
		0x0f, 0xf8, 0x1f, 0xf0,
		0x07, 0xfc, 0x3f, 0xe0,
		0x03, 0xfe, 0x7f, 0xc0,
		0x01, 0xff, 0xff, 0x80,
		0x00, 0xff, 0xff, 0x00,
		0x00, 0x7f, 0xfe, 0x00,
		0x00, 0x3f, 0xfc, 0x00,
		0x00, 0x1f, 0xf8, 0x00,
		0x00, 0x1f, 0xf8, 0x00,
		0x00, 0x3f, 0xfc, 0x00,
		0x00, 0x7f, 0xfe, 0x00,
		0x00, 0xff, 0xff, 0x00,
		0x01, 0xff, 0xff, 0x80,
		0x03, 0xfe, 0x7f, 0xc0,
		0x07, 0xfc, 0x3f, 0xe0,
		0x0f, 0xf8, 0x1f, 0xf0,
		0x1f, 0xf0, 0x0f, 0xf8,
		0x3f, 0xe0, 0x07, 0xfc,
		0x7f, 0xc0, 0x03, 0xfe,
		0xff, 0x80, 0x01, 0xff,
		0xff, 0x00, 0x00, 0xff,
		0xfe, 0x00, 0x00, 0x7f,
		0xfc, 0x00, 0x00, 0x3f,
		0xf8, 0x00, 0x00, 0x1f
	};

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(rotate, 0.0f, 1.0f, 0.0f);
	glPolygonMode(GL_FRONT, GL_LINE);
	glPolygonMode(GL_BACK, GL_FILL);
	glColor3f(0.0f, 1.0f, 0.0f);
	glPolygonStipple(xsign);
	glBegin(GL_QUADS);
	glVertex2f(-0.4f, 0.6f);
	glVertex2f(-0.4f, -0.6f);
	glVertex2f(0.4f, -0.6f);
	glVertex2f(0.4f, 0.6f);
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
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_POLYGON_STIPPLE);
	glDepthFunc(GL_LEQUAL);
}