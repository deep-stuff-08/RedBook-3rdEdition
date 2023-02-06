#include<GL/freeglut.h>
#include<stdio.h>

#define SPEED 0.1
#define X 0.525731112119133606
#define Z 0.850650808352039932

GLfloat rotate = 0.0f;
bool gbAnim = true;

int main(int argc, char **argv) {
	void Init();
	void Display();
	void Reshape(int w, int h);
	void Update(void);
	void Keyboard(unsigned char key, int x, int y);
	
	//Left One: glVertex() and glColor()
	//Right One: glDrawElements()

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Isoheadron");
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
	static GLdouble vertice_data[] = {
		-X, 0.0, Z, X, 0.0, Z, -X, 0.0, -Z, X, 0.0, -Z,
		0.0, Z, X, 0.0, Z, -X, 0.0, -Z, X, 0.0, -Z, -X,
		Z, X, 0.0, -Z, X, 0.0, Z, -X, 0.0, -Z, -X, 0.0
	};
	
	static GLuint isoheadron_list[] = {
		1, 4, 0, 4, 9, 0, 4, 5, 9, 8, 5, 4, 1, 8, 4,
		1, 10, 8, 10, 3, 8, 8, 3, 5, 3, 2, 5, 3, 7, 2,
		3, 10, 7, 10, 6, 7, 6, 11, 7, 6, 0, 11, 6, 1, 0,
		10, 1, 6, 11, 0, 9, 2, 11, 9, 5, 2, 9, 11, 2, 7
	};

	static GLfloat colors_data[] = {
		0.25f, 1.0f, 0.5f,
		0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f,
		1.0f, 0.5f, 0.0f,
		0.0f, 1.0f, 0.5f,
		0.5f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.5f,
		0.5f, 1.0f, 0.0f,
		0.0f, 0.5f, 1.0f,
		1.0f, 0.5f, 0.25f,
		0.5f, 1.0f, 0.25f,
		0.25f, 0.5f, 1.0f,
		1.0f, 0.25f, 0.5f,
		1.0f, 0.0f, 0.0f,
		0.5f, 0.25f, 1.0f,
		1.0f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f
	};

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(-0.5f, 0.0f, 0.0f);
	glRotatef(rotate, 1.0f, 1.0f, 1.0f);
	glScalef(0.5f, 0.5f, 0.5f);
	glBegin(GL_TRIANGLES);
	for(int i = 0; i < 20; i++) {
		glColor3fv(&colors_data[i*3]);
		glVertex3dv(&vertice_data[isoheadron_list[i * 3] * 3]);
		glVertex3dv(&vertice_data[isoheadron_list[i * 3 + 1] * 3]);
		glVertex3dv(&vertice_data[isoheadron_list[i * 3 + 2] * 3]);
	}
	glEnd();
	
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

	glColorPointer(3, GL_FLOAT, 0, colors_data);
	glVertexPointer(3, GL_DOUBLE, 0, vertice_data);

	glLoadIdentity();
	glTranslatef(0.5f, 0.0f, 0.0f);
	glRotatef(rotate, 1.0f, 1.0f, 1.0f);
	glScalef(0.5f, 0.5f, 0.5f);
	glDrawElements(GL_TRIANGLES, 60, GL_UNSIGNED_INT, isoheadron_list);
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
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
}