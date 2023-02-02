#include<GL/freeglut.h>

#define checkImageWidth 64
#define checkImageHeight 64

GLubyte checkImage[checkImageHeight][checkImageWidth][4];
GLubyte otherImage[checkImageHeight][checkImageWidth][4];

GLuint texName[2];

void makeCheckImage(void) {
	int i, j, c;

	for(i = 0; i < checkImageHeight; i++) {
		for(j = 0; j < checkImageWidth; j++) {
			c = ((((i & 0x8) == 0) ^ ((j & 0x8)) == 0)) * 255;
			checkImage[i][j][0] = (GLubyte) c;
			checkImage[i][j][1] = (GLubyte) c;
			checkImage[i][j][2] = (GLubyte) c;
			checkImage[i][j][3] = (GLubyte) 255;
			c = ((((i & 0x10) == 0) ^ ((j & 0x10)) == 0)) * 255;
			otherImage[i][j][0] = (GLubyte)c;
			otherImage[i][j][1] = (GLubyte)0;
			otherImage[i][j][2] = (GLubyte)0;
			otherImage[i][j][3] = (GLubyte)255;
		}
	}
}

void init(void) {
	glClearColor(0.5f, 0.5f, 0.5f, 0.0f);
	glClearDepth(1.0f);
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);
	makeCheckImage();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(2, texName);
	glBindTexture(GL_TEXTURE_2D, texName[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, checkImageWidth, checkImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, checkImage);

	glBindTexture(GL_TEXTURE_2D, texName[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, checkImageWidth, checkImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, otherImage);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glEnable(GL_TEXTURE_2D);
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindTexture(GL_TEXTURE_2D, texName[0]);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.0f, -1.0f, 0.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.0f, 1.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, 1.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, -1.0f, 0.0f);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, texName[1]);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 0.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(2.41421f, 1.0f, -1.41421);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(2.41421f, -1.0f, -1.41421);
	glEnd();
	glutSwapBuffers();
}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, (GLfloat) w / h, 1.0f, 30.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -3.6f);
}

void keyboard(unsigned char key, int x, int y) {
	switch(key) {
	case 27:
		glutLeaveMainLoop();
		break;
	default:
		break;
	}
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(650, 650);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
}