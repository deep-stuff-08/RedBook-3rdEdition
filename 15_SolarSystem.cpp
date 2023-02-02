#include<GL/freeglut.h>

static int sun = 0,
earthyear1 = 0, earthday1 = 0, earthyear2 = 0, earthday2 = 0,
moonyear1 = 0, moonday1 = 0, moonyear2 = 0, moonday2 = 0, moonyear3 = 0, moonday3 = 0;

int main(int argc, char **argv) {
	void Init();
	void Display();
	void Resize(int w, int h);
	void Keyboard(unsigned char key, int x, int y);
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Solar System");
	Init();
	glutDisplayFunc(Display);
	glutReshapeFunc(Resize);
	glutKeyboardFunc(Keyboard);
	glutMainLoop();
	return 0;
}

void Init() {
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_FLAT);
}

void Display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Saving Location of Center Before Drawing Entire Scene
	glPushMatrix();
		//Rotate All spheres
		glRotatef(90, 1.0f, 0.0f, 0.0f);
		//Saving Location of Sun before Rotation
		glPushMatrix();
		//Rotation Sun
			glRotatef((GLfloat) sun, 0.0f, 0.0f, 1.0f);
			//Draw Sun
			glColor3f(1.0f, 1.0f, 0.0f);
			glutWireSphere(0.7, 20, 16);
		//Reload Location of Sun After Rotation
		glPopMatrix();
		//Saving Location of Sun before drawing first planet
		glPushMatrix();
			//Revolution Earth
			glRotatef((GLfloat) earthyear1, 0.0f, 0.0f, 1.0f);
			glTranslatef(1.7f, 0.0f, 0.0f);
			//Saving Location of Earth before Rotation
			glPushMatrix();
				//Titlting Earth
				glRotatef(10, 0.0f, 1.0f, 0.0f);
				//Rotation Earth
				glRotatef((GLfloat) earthday1, 0.0f, 0.0f, 1.0f);
				//Earth
				glColor3f(0.0f, 0.0f, 1.0f);
				glutWireSphere(0.3, 10, 8);
			//Reload Location of Earth After Rotation
			glPopMatrix();
			//Saving Location of Current Earth Before Drawing Moon 1
			glPushMatrix();
			//Revolution Moon 1
				glRotatef((GLfloat) moonyear1, 0.0f, 0.0f, 1.0f);
				glTranslatef(0.45f, 0.0f, 0.0f);
				//Rotation Moon 1
				glRotatef((GLfloat) moonday1, 0.0f, 0.0f, 1.0f);
				//Draw Moon 1
				glColor3f(1.0f, 1.0f, 1.0f);
				glutWireSphere(0.1, 5, 4);
			//Reload Location of Earth After Drawing Moon 1
			glPopMatrix();
			//Saving Location of Current Earth Before Drawing Moon 2
			glPushMatrix();
			//Revolution Moon 2
				glRotatef((GLfloat) moonyear2, 0.0f, 0.0f, 1.0f);
				glTranslatef(0.8f, 0.0f, 0.0f);
				//Rotation Moon 2
				glRotatef((GLfloat) moonday2, 0.0f, 0.0f, 1.0f);
				//Draw Moon 2
				glColor3f(1.0f, 0.5f, 0.0f);
				glutWireSphere(0.15, 7, 6);
			//Reload Location of Current Earth After Drawing Moon 2
			glPopMatrix();
		//Reload Location of Sun After drawing first planet
		glPopMatrix();
		//Saving Location of Sun Before drawing second planet
		glPushMatrix();
			//Revolution Planet 2
			glRotatef((GLfloat) earthyear2, 0.0f, 0.0f, 1.0f);
			glTranslatef(3.4f, 0.0f, 0.0f);
			//Saving Location of Planet 2 before Rotation
			glPushMatrix();
				//Tilting Planet 2
				glRotatef(10, 0.0f, 1.0f, 0.0f);
				//Rotation Planet 2
				glRotatef((GLfloat) earthday2, 0.0f, 0.0f, 1.0f);
				//Drawing Planet 2
				glColor3f(0.0f, 1.0f, 0.0f);
				glutWireSphere(0.27, 10, 8);
			//Reload Location of Planet 2 after Rotation
			glPopMatrix();
			//Saving Location of Planet 2 before Drawing moon
			glPushMatrix();
				//Revolving Moon 3
				glRotatef((GLfloat) moonyear3, 0.0f, 0.0f, 1.0f);
				glTranslatef(0.5f, 0.0f, 0.0f);
				//Rotating Moon 3
				glRotatef((GLfloat) moonday3, 0.0f, 0.0f, 1.0f);
				glColor3f(1.0f, 0.0f, 0.0f);
				glutWireSphere(0.1, 5, 4);
			//Reload Location of Planet 3 after Drawing moon
			glPopMatrix();
		//Reload Location of Sun After drawing second planet
		glPopMatrix();
	//Reload Location of Center After Drawing Entire Scene
	glPopMatrix();
	glutSwapBuffers();
}

void Keyboard(unsigned char key, int x, int y) {
	switch(key) {
	case 27:
		glutLeaveMainLoop();
		break;
	case 'f': case 'F':
		glutFullScreenToggle();
		break;
	case 'Q':
		earthday1 = (earthday1 - 10) % 360;
		glutPostRedisplay();
		break;
	case 'q':
		earthday1 = (earthday1 + 10) % 360;
		glutPostRedisplay();
		break;
	case 'w':
		earthyear1 = (earthyear1 - 5) % 360;
		glutPostRedisplay();
		break;
	case 'W':
		earthyear1 = (earthyear1 + 5) % 360;
		glutPostRedisplay();
		break;
	case 'e':
		moonday1 = (moonday1 - 10) % 360;
		glutPostRedisplay();
		break;
	case 'E':
		moonday1 = (moonday1 + 10) % 360;
		glutPostRedisplay();
		break;
	case 'r':
		moonyear1 = (moonyear1 - 5) % 360;
		glutPostRedisplay();
		break;
	case 'R':
		moonyear1 = (moonyear1 + 5) % 360;
		glutPostRedisplay();
		break;
	case 't':
		moonday2 = (moonday2 - 10) % 360;
		glutPostRedisplay();
		break;
	case 'T':
		moonday2 = (moonday2 + 10) % 360;
		glutPostRedisplay();
		break;
	case 'y':
		moonyear2 = (moonyear2 - 5) % 360;
		glutPostRedisplay();
		break;
	case 'Y':
		moonyear2 = (moonyear2 + 5) % 360;
		glutPostRedisplay();
		break;
	case 'u':
		earthday2 = (earthday2 - 10) % 360;
		glutPostRedisplay();
		break;
	case 'U':
		earthday2 = (earthday2 + 10) % 360;
		glutPostRedisplay();
		break;
	case 'i':
		earthyear2 = (earthyear2 - 5) % 360;
		glutPostRedisplay();
		break;
	case 'I':
		earthyear2 = (earthyear2 + 5) % 360;
		glutPostRedisplay();
		break;
	case 'o':
		moonday3 = (moonday3 - 10) % 360;
		glutPostRedisplay();
		break;
	case 'O':
		moonday3 = (moonday3 + 10) % 360;
		glutPostRedisplay();
		break;
	case 'p':
		moonyear3 = (moonyear3 - 5) % 360;
		glutPostRedisplay();
		break;
	case 'P':
		moonyear3 = (moonyear3 + 5) % 360;
		glutPostRedisplay();
		break;
	case 'a':
		sun = (sun - 10) % 360;
		glutPostRedisplay();
		break;
	case 'A':
		sun = (sun + 10) % 360;
		glutPostRedisplay();
		break;
	}
}

void Resize(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLdouble)width/(GLdouble)height, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}