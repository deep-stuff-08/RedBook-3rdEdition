#include<GL/freeglut.h>
#include<stdlib.h>
#include<string.h>

#define PT 1
#define STROKE 2
#define END 3

typedef struct charpoint {
	GLfloat x, y;
	int type;
} CP;

CP Adata[] = {
	{ 0, 0, PT}, {0, 9, PT}, {1, 10, PT}, {4, 10, PT} ,
	{5, 9, PT}, {5, 0, STROKE}, {0, 5, PT} , {5, 5, END}
};

CP Edata[] = {
	{5, 0, PT}, {0, 0, PT}, {0, 10, PT}, {5, 10, STROKE},
	{0, 5, PT}, {4, 5, END}
};

CP Pdata[] = {
	{0, 0, PT}, {0, 10, PT}, {4, 10, PT}, {5, 9, PT} , {5, 6, PT},
	{4, 5, PT}, {0, 5, END}
};

CP Rdata[] = {
	{0, 0, PT}, {0, 10, PT}, {4, 10, PT}, {5, 9, PT} , {5, 6, PT},
	{4, 5, PT}, {0, 5, STROKE}, {3, 5, PT} , {5, 0, END}
};

CP Sdata[] = {
	{0, 1, PT}, {1, 0, PT}, {4, 0, PT}, {5, 1, PT}, {5, 4, PT},
	{4, 5, PT}, {1, 5, PT}, {0, 6, PT}, {0, 9, PT} , {1, 10, PT},
	{4, 10, PT}, {5, 9, END}
};

void drawLetter(CP *l) {
	glBegin(GL_LINE_STRIP);
	while(1) {
		switch(l->type) {
		case PT:
			glVertex2fv(&l->x);
			break;
		case STROKE:
			glVertex2fv(&l->x);
			glEnd();
			glBegin(GL_LINE_STRIP);
			break;
		case END:
			glVertex2fv(&l->x);
			glEnd();
			glTranslatef(8.0f, 0.0f, 0.0f);
			return;
		}
		l++;
	}
}

void init(void) {
	GLuint base;

	glShadeModel(GL_FLAT);

	base = glGenLists(128);
	glListBase(base);
	glNewList(base + 'A', GL_COMPILE);
		drawLetter(Adata);
	glEndList();
	glNewList(base + 'E', GL_COMPILE);
		drawLetter(Edata);
	glEndList();
	glNewList(base + 'P', GL_COMPILE);
		drawLetter(Pdata);
	glEndList();
	glNewList(base + 'R', GL_COMPILE);
		drawLetter(Rdata);
	glEndList();
	glNewList(base + 'S', GL_COMPILE);
		drawLetter(Sdata);
	glEndList();
	glNewList(base + ' ', GL_COMPILE);
		glTranslatef(8.0f, 0.0f, 0.0f);
	glEndList();
}

const char *test1 = "A SPARE SERAPE APPEARS AS";
const char *test2 = "APES PREPARE RARE PEPPERS";

void glPrint(const char *s) {
	GLsizei len = strlen(s);
	glCallLists(len, GL_BYTE, (GLbyte *)s);
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 1.0f, 1.0f);
	glScalef(2.0f, 2.0f, 2.0f);
	
	glPushMatrix();
	glTranslatef(10.0f, 30.0f, 0.0f);
	glPrint(test1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(10.0f, 13.0f, 0.0f);
	glPrint(test2);
	glPopMatrix();

	glutSwapBuffers();
}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0f, 900.0, 0.0f, 200.0f);
}

void keyboard(unsigned char key, int x, int y) {
	switch(key) {
	case 'F': case 'f':
		glutFullScreenToggle();
		break;
	case 27:
		glutLeaveMainLoop();
		break;
	}
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutCreateWindow(argv[0]);
	init();
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}