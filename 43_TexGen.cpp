#include<GL/freeglut.h>
#include<stdlib.h>
#include<stdio.h>

#define stripeImageWidth 32
GLubyte stripeImage[4 * stripeImageWidth];

static GLuint texName;

void makeStripeImage(void) {
	for(int j = 0; j < stripeImageWidth; j++) {
		stripeImage[4 * j] = (GLubyte) ((j <= 4) ? 255 : 0);
		stripeImage[4 * j + 1] = (GLubyte) ((j > 4) ? 255 : 0);
		stripeImage[4 * j + 2] = (GLubyte) 0;
		stripeImage[4 * j + 3] = (GLubyte) 255;
	}
}

GLfloat xequalzero[] = { 1.0f, 0.0f, 0.0f, 0.0f};
GLfloat slanted[] = {1.0f, 1.0f, 1.0f, 0.0f};
GLfloat *currentCoeff;
GLenum currentPlane;
GLint currentGenMode;

GLfloat rot = 0.0f;

void Init(void) {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

	makeStripeImage();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glGenTextures(1, &texName);
	glBindTexture(GL_TEXTURE_1D, texName);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage1D(GL_TEXTURE_1D, 0, GL_RGBA, stripeImageWidth, 0, GL_RGBA, GL_UNSIGNED_BYTE, stripeImage);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	currentCoeff = xequalzero;
	currentGenMode = GL_OBJECT_LINEAR;
	currentPlane = GL_OBJECT_PLANE;
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, currentGenMode);
	glTexGenfv(GL_S, currentPlane, currentCoeff);

	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_1D);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);
	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	glMaterialf(GL_FRONT, GL_SHININESS, 64.0f);
}

void Display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glRotatef(rot, 1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_1D, texName);
	glutSolidTeapot(2.0f);
	glPopMatrix();
	glutSwapBuffers();
}

void Reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w <= h) {
		glOrtho(-3.5f, 3.5f, -3.5f * (GLfloat)h / (GLfloat)w, 3.5f * (GLfloat)h / (GLfloat)w, -3.5f, 3.5f);
	} else {
		glOrtho(-3.5f * (GLfloat)w / (GLfloat)h, 3.5f * (GLfloat)w / (GLfloat)h, -3.5f, 3.5f, -3.5f, 3.5f);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Keyboard(unsigned char key, int x, int y) {
	switch(key) {
	case 'e':
	case 'E':
		currentGenMode = GL_EYE_LINEAR;
		currentPlane = GL_EYE_PLANE;
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, currentGenMode);
		glTexGenfv(GL_S, currentPlane, currentCoeff);
		glutPostRedisplay();
		break;
	case 'o':
	case 'O':
		currentGenMode = GL_OBJECT_LINEAR;
		currentPlane = GL_OBJECT_PLANE;
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, currentGenMode);
		glTexGenfv(GL_S, currentPlane, currentCoeff);
		glutPostRedisplay();	
		break;
	case 's':
	case 'S':
		currentCoeff = slanted;
		glTexGenfv(GL_S, currentPlane, currentCoeff);
		glutPostRedisplay();
		break;
	case 'x':
	case 'X':
		currentCoeff = xequalzero;
		glTexGenfv(GL_S, currentPlane, currentCoeff);
		glutPostRedisplay();
		break;
	case 27:
		glutLeaveMainLoop();
		break;
	default:
		break;
	}
}

void Idle(void) {
	rot += 0.01f;
	if(rot >= 360) {
		rot -= 360.0f;
	}
	glutPostRedisplay();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(256, 256);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	Init();
	glutDisplayFunc(Display);
	glutKeyboardFunc(Keyboard);
	glutReshapeFunc(Reshape);
	glutIdleFunc(Idle);
	glutMainLoop();
	return 0;
}
