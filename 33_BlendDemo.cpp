#include<GL/freeglut.h>
#include<stdio.h>

#define SRC_COUNT 9
#define DST_COUNT 8

typedef struct GLblendparam {
	GLenum param;
	char msg[25];
} GLblendparam;

GLubyte currentSrc = 0, currentDest = 0;
GLblendparam blendSrcParams[SRC_COUNT] = {
	{GL_ZERO, "GL_ZERO"},
	{GL_ONE, "GL_ONE"},
	{GL_DST_COLOR, "GL_DST_COLOR"},
	{GL_ONE_MINUS_DST_COLOR, "GL_ONE_MINUS_DST_COLOR"},
	{GL_SRC_ALPHA, "GL_SRC_ALPHA"},
	{GL_ONE_MINUS_SRC_ALPHA, "GL_ONE_MINUS_SRC_ALPHA"},
	{GL_DST_ALPHA, "GL_DST_ALPHA"},
	{GL_ONE_MINUS_DST_ALPHA, "GL_ONE_MINUS_DST_ALPHA"},
	{GL_SRC_ALPHA_SATURATE, "GL_SRC_ALPHA_SATURATE"},
};

GLblendparam blendDstParams[DST_COUNT] = {
	{GL_ZERO, "GL_ZERO"},
	{GL_ONE, "GL_ONE"},
	{GL_SRC_COLOR, "GL_SRC_COLOR"},
	{GL_ONE_MINUS_SRC_COLOR, "GL_ONE_MINUS_SRC_COLOR"},
	{GL_SRC_ALPHA, "GL_SRC_ALPHA"},
	{GL_ONE_MINUS_SRC_ALPHA, "GL_ONE_MINUS_SRC_ALPHA"},
	{GL_DST_ALPHA, "GL_DST_ALPHA"},
	{GL_ONE_MINUS_DST_ALPHA, "GL_ONE_MINUS_DST_ALPHA"}
};

void Init() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);

	glDepthFunc(GL_LEQUAL);
}

void Reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w >= h) {
		glOrtho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
	} else {
		glOrtho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
	}
}

void glPrint(const char* format, ...) {
	va_list args;
	char buffer[255], *s;

	va_start(args, format);
	vsprintf(buffer, format, args);
	va_end(args);

	for(s=buffer; *s; s++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *s);
	}
}

void Keyboard(unsigned char ch, int x, int y) {
	switch(ch) {
	case 'F': case 'f':
		glutFullScreenToggle();
		break;
	case 27:
		glutLeaveMainLoop();
		break;
	case 'S': case 's':
		currentSrc = ++currentSrc % SRC_COUNT;
		glutPostRedisplay();
		break;
	case 'W': case 'w':
		if(currentSrc == 0) {
			currentSrc = SRC_COUNT;
		}
		currentSrc--;
		glutPostRedisplay();
		break;
	case 'K': case 'k':
		currentDest = ++currentDest % DST_COUNT;
		glutPostRedisplay();
		break;
	case 'I': case 'i':
		if(currentDest == 0) {
			currentDest = DST_COUNT;
		}
		currentDest--;
		glutPostRedisplay();
		break;
	}
}

void Display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glRasterPos2f(-0.9f, 0.85f);
	glPrint("Source");
	for(int i = 0; i < SRC_COUNT; i++) {
		if(i == currentSrc) {
			glColor3f(0.0f, 1.0f, 0.0f);
		} else {
			glColor3f(1.0f, 1.0f, 1.0f);
		}
		glTranslatef(0.0f, -0.12f, 0.0f);
		glRasterPos2f(-0.9f, 0.8f);
		glPrint(blendSrcParams[i].msg);
	}
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glRasterPos2f(0.55f, 0.85f);
	glPrint("Destination");
	for(int i = 0; i < DST_COUNT; i++) {
		if(i == currentDest) {
			glColor3f(0.0f, 1.0f, 0.0f);
		} else {
			glColor3f(1.0f, 1.0f, 1.0f);
		}
		glTranslatef(0.0f, -0.12f, 0.0f);
		glRasterPos2f(0.55f, 0.8f);
		glPrint(blendDstParams[i].msg);
	}
	glPopMatrix();

	glBlendFunc(blendSrcParams[currentSrc].param, blendDstParams[currentDest].param);
	glEnable(GL_BLEND);

	glBegin(GL_TRIANGLES);
		glColor4f(1.0f, 1.0f, 0.0f, 0.5f);
		glVertex3f(-0.3f, 0.3f, 0.0f);
		glVertex3f(-0.3f, -0.3f, 0.0f);
		glVertex3f(0.3f, 0.0f, 0.0f);
	
		glColor4f(0.0f, 1.0f, 1.0f, 0.5f);
		glVertex3f(0.3f, 0.3f, 0.01f);
		glVertex3f(0.3f, -0.3f, 0.01f);
		glVertex3f(-0.3f, 0.0f, 0.01f);
	glEnd();

	glDisable(GL_BLEND);
	glutSwapBuffers();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(10, 10);
	glutCreateWindow(argv[0]);
	Init();
	glutReshapeFunc(Reshape);
	glutDisplayFunc(Display);
	glutKeyboardFunc(Keyboard);
	glutMainLoop();
	return 0;
}