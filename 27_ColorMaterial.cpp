#include<GL/freeglut.h>
#include<stdio.h>

GLfloat mat_diffuse[] = {0.5f, 0.5f, 0.5f, 1.0f};

void Keyboard(unsigned char key, int kx, int ky) {
	switch(key) {
	case 27:
		glutLeaveMainLoop();
		break;
	case 'R':
		if(mat_diffuse[0] < 1.0f) {
			mat_diffuse[0] += 0.1f;
		}
		glColor4fv(mat_diffuse);
		break;
	case 'r':
		if(mat_diffuse[0] > 0.0f) {
			mat_diffuse[0] -= 0.1f;
		}
		glColor4fv(mat_diffuse);
		break;
	case 'G':
		if(mat_diffuse[1] < 1.0f) {
			mat_diffuse[1] += 0.1f;
		}
		glColor4fv(mat_diffuse);
		break;
	case 'g':
		if(mat_diffuse[1] > 0.0f) {
			mat_diffuse[1] -= 0.1f;
		}
		glColor4fv(mat_diffuse);
		break;
	case 'B':
		if(mat_diffuse[2] < 1.0f) {
			mat_diffuse[2] += 0.1f;
		}
		glColor4fv(mat_diffuse);
		break;
	case 'b':
		if(mat_diffuse[2] > 0.0f) {
			mat_diffuse[2] -= 0.1f;
		}
		glColor4fv(mat_diffuse);
		break;
	case 'F': case 'f':
		glutFullScreenToggle();
		break;
	}
	glutPostRedisplay();
}

void Resize(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w >= h) {
		glOrtho(-1.0 * (GLfloat)w / h, 1.0 * (GLfloat)w / h, -1.0f, 1.0f, -1.0f, 1.0f);
	} else {
		glOrtho(-1.0, 1.0f, -1.0 * (GLfloat)w / h, 1.0 * (GLfloat)w / h, -1.0f, 1.0f);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Init() {
	GLfloat mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat light_pos[] = {1.0f, 1.0f, 1.0f, 0.0f};

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glShadeModel(GL_SMOOTH);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 15.0f);
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
}

void Display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glRotatef(90, 1.0f, 0.0f, 0.0f);
	glutSolidSphere(0.66f, 25, 25);
	glPopMatrix();
	glutSwapBuffers();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowPosition(10, 10);
	glutInitWindowSize(900, 700);
	glutCreateWindow(argv[0]);
	Init();
	glutDisplayFunc(Display);
	glutReshapeFunc(Resize);
	glutKeyboardFunc(Keyboard);
	glutMainLoop();
}