#include<GL/freeglut.h>

#define SPEED 0.1

GLfloat rotate = 0.0f;
bool gbAnim = true;

int main(int argc, char **argv) {
	void Init();
	void Display();
	void Reshape(int w, int h);
	void Update(void);
	void Keyboard(unsigned char key, int x, int y);
	
	//Triangle Using Interleaved Array and glArrayElements
	//Hexagon Using Interleaved Array and glDrawElements
	//Cube Using glDrawElements
	//Quad Using glDrawArrays
	//Tetraheadron Using glInterleavedArrays and glDrawElements

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Vertex Arrays");
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
	GLfloat fHexArrays[] = { //2 3
		0.0f, 0.2f, 1.0f, 0.0f, 0.0f,
		-0.2f, 0.1, 1.0f, 1.0f, 0.0f,
		-0.2f, -0.1f, 0.0f, 1.0f, 0.0f,
		0.0f, -0.2f, 0.0f, 1.0f, 1.0f,
		0.2f, -0.1f, 0.0f, 0.0f, 1.0f,
		0.2f, 0.1f, 1.0f, 0.0f, 1.0f
	};

	GLfloat fCubeVertices[] = {
		-0.2f, 0.2f, 0.2f,
		-0.2f, -0.2f, 0.2f,
		0.2f, -0.2f, 0.2f,
		0.2f, 0.2f ,0.2f,
		0.2f, 0.2f, -0.2f,
		0.2f, -0.2f, -0.2f,
		-0.2f, -0.2f, -0.2f,
		-0.2f, 0.2f, -0.2f
	};

	GLfloat fCubesColors[] = {
		1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.5f
	};

	GLfloat fQuadVertices[] = {
		-0.2f, 0.2f,
		-0.2f, -0.2f,
		0.2f, -0.2f,
		0.2f, 0.2f
	};

	GLfloat fQuadColors[] = {
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

	GLfloat fTetraheadronInter[] = {
		1.0f, 1.0f, 1.0f, 0.0f, 0.2f, 0.0f,
		1.0f, 0.0f, 0.0f, -0.2f, -0.2f, 0.2f,
		0.0f, 1.0f, 0.0f, 0.2f, -0.2f, 0.2f,
		0.0f, 0.0f, 1.0f, 0.0f, -0.2f, -0.2f
	};


	GLubyte tetraheadron_list[] = {
		0, 1, 2, //Front
		0, 3, 1, //Left
		0, 2, 3, //Right
		1, 3, 2  //Bottom
	};

	GLubyte hex_list[] = {0, 1, 2, 3, 4, 5};

	GLubyte cube_list[] = {
		0, 1, 2, 3, // Front
		7, 6, 1, 0, // Left
		4, 5, 6, 7, // Back
		3, 2, 5, 4, // Right
		7, 0, 3, 4, // Top
		1, 6, 5, 2  // Bottom
	};

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glInterleavedArrays(GL_C3F_V3F, 0, fTetraheadronInter);
	
	glLoadIdentity();
	glTranslatef(0.6f, 0.6f, 0.0f);
	glRotatef(rotate, 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_BYTE, tetraheadron_list);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glColorPointer(3, GL_FLOAT, sizeof(GL_FLOAT) * 5, &fHexArrays[2]);
	glVertexPointer(2, GL_FLOAT, sizeof(GL_FLOAT) * 5, fHexArrays);

	glLoadIdentity();
	glTranslatef(-0.6f, 0.6f, 0.0f);
	glBegin(GL_TRIANGLES);
	glArrayElement(0);
	glArrayElement(2);
	glArrayElement(4);
	glEnd();
	
	glLoadIdentity();
	glTranslatef(0.6f, -0.6f, 0.0f);
	glDrawElements(GL_POLYGON, 6, GL_UNSIGNED_BYTE, hex_list);

	glVertexPointer(3, GL_FLOAT, 0, fCubeVertices);
	glColorPointer(3, GL_FLOAT, 0, fCubesColors);

	glLoadIdentity();
	glTranslatef(-0.6f, -0.6f, 0.0f);
	glRotatef(rotate, 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, cube_list);

	glVertexPointer(2, GL_FLOAT, 0, fQuadVertices);
	glColorPointer(3, GL_FLOAT, 0, fQuadColors);

	glLoadIdentity();
	glDrawArrays(GL_QUADS, 0, 4);

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