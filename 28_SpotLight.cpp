#include<GL/freeglut.h>
#include<stdio.h>
#include<math.h>

#define SPEED 0.01f
#define COLOR_SELECTED(param) (current_property == param ? select_color : normal_color) 

GLfloat win_width, win_height;
GLfloat light_position[] = {0.0f, 0.0f, 1.0f, 1.0f};
GLfloat spot_direction[] = {0.0f, 0.0f, -1.0f};
GLfloat spot_exponent = 0.0f;
GLfloat spot_angle = 90.0f;
GLfloat attenuation[] = {1.0f, 0.0f, 0.0f};
GLfloat select_color[] = {0.0f, 1.0f, 0.0f};
GLfloat normal_color[] = {1.0f, 1.0f, 1.0f};
unsigned current_property = 0;

void Keyboard(unsigned char key, int kx, int ky) {
	switch(key) {
	case 27:
		glutLeaveMainLoop();
		break;
	case 'F': case 'f':
		glutFullScreenToggle();
		break;
	case 'W': case 'w':
		if(current_property == 0) {
			current_property = 5;
		}
		current_property = (current_property - 1) % 5;
		break;
	case 'S': case 's':
		current_property = (current_property + 1) % 5;
		break;
	case 'U': case 'u':
		switch(current_property) {
		case 0:
			if(light_position[0] < 0.999f) {
				light_position[0] += SPEED;
			}
			break;
		case 1:
			if(spot_direction[0] < 0.999f) {
				spot_direction[0] += SPEED; 
			}
			break;
		case 2:
			if(spot_exponent < 128.0f) {
				spot_exponent += SPEED * 100.0f;
			}
			break;
		case 3:
			if(spot_angle < 90.0f) {
				spot_angle += SPEED * 100.0f;
			}
			break;
		case 4:
			if(attenuation[0] < 5.0f) {
				attenuation[0] += SPEED * 100.0f;
			}
			break;
		}
		break;
	case 'J': case 'j':
		switch(current_property) {
		case 0:
			if(light_position[0] > -0.999f) {
				light_position[0] -= SPEED;
			}
			break;
		case 1:
			if(spot_direction[0] > -0.999f) {
				spot_direction[0] -= SPEED; 
			}
			break;
		case 2:
			if(spot_exponent > 0.9f) {
				spot_exponent -= SPEED * 100.0f;
			}
			break;
		case 3:
			if(spot_angle > 0.9f) {
				spot_angle -= SPEED * 100.0f;
			}
			break;
		case 4:
			if(attenuation[0] > 0.9f) {
				attenuation[0] -= SPEED * 100.0f;
			}
			break;
		}
		break;
	case 'I': case 'i':
		switch(current_property) {
		case 0:
			if(light_position[1] < 0.999f) {
				light_position[1] += SPEED;
			}
			break;
		case 1:
			if(spot_direction[1] < 0.999f) {
				spot_direction[1] += SPEED; 
			}
			break;
		case 2:
			if(spot_exponent < 128.0f) {
				spot_exponent += SPEED * 100.0f;
			}
			break;
		case 3:
			if(spot_angle < 90.0f) {
				spot_angle += SPEED * 100.0f;
			}
			break;
		case 4:
			if(attenuation[1] < 5.0f) {
				attenuation[1] += SPEED * 100.0f;
			}
			break;
		}
		break;
	case 'K': case 'k':
		switch(current_property) {
		case 0:
			if(light_position[1] > -0.999f) {
				light_position[1] -= SPEED;
			}
			break;
		case 1:
			if(spot_direction[1] > -0.999f) {
				spot_direction[1] -= SPEED; 
			}
			break;
		case 2:
			if(spot_exponent > 0.9f) {
				spot_exponent -= SPEED * 100.0f;
			}
			break;
		case 3:
			if(spot_angle > 0.9f) {
				spot_angle -= SPEED * 100.0f;
			}
			break;
		case 4:
			if(attenuation[1] > 0.9f) {
				attenuation[1] -= SPEED * 100.0f;
			}
			break;
		}
		break;
	case 'O': case 'o':
		switch(current_property) {
		case 0:
			if(light_position[2] < 0.999f) {
				light_position[2] += SPEED;
			}
			break;
		case 1:
			if(spot_direction[2] < 0.999f) {
				spot_direction[2] += SPEED; 
			}
			break;
		case 2:
			if(spot_exponent < 128.0f) {
				spot_exponent += SPEED * 100.0f;
			}
			break;
		case 3:
			if(spot_angle < 90.0f) {
				spot_angle += SPEED * 100.0f;
			}
			break;
		case 4:
			if(attenuation[2] < 5.0f) {
				attenuation[2] += SPEED * 100.0f;
			}
			break;
		}
		break;
	case 'L': case 'l':
		switch(current_property) {
		case 0:
			if(light_position[2] > -0.999f) {
				light_position[2] -= SPEED;
			}
			break;
		case 1:
			if(spot_direction[2] > -0.999f) {
				spot_direction[2] -= SPEED; 
			}
			break;
		case 2:
			if(spot_exponent > 0.9f) {
				spot_exponent -= SPEED * 100.0f;
			}
			break;
		case 3:
			if(spot_angle > 0.9f) {
				spot_angle -= SPEED * 100.0f;
			}
			break;
		case 4:
			if(attenuation[2] > 0.9f) {
				attenuation[2] -= SPEED * 100.0f;
			}
			break;
		}
		break;
	}
	glutPostRedisplay();
}

void Resize(int w, int h) {
	win_width = w;
	win_height = h;
	glutPostRedisplay();
}

void Init() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
	glShadeModel(GL_SMOOTH);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHT0);
}

void glPrint(const char* format, ...) {
	va_list args;
	char buffer[255], *s;

	va_start(args, format);
	vsprintf(buffer, format, args);
	va_end(args);

	for(s=buffer; *s; s++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *s);
	}
}

void Display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_LIGHTING);
	glViewport(win_width * 2.0f / 3.0f, 0.0f, win_width / 3.0f, win_height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0f, 1.0f, -1.0f * win_height / (win_width / 3.0f), 1.0f * win_height / (win_width / 3.0f), -1.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3fv(current_property == 0?select_color:normal_color);
	glRasterPos2f(-1.0f, 1.0f);
	glPrint("Postion:( %1.2f, %1.2f, %1.2f )", light_position[0], light_position[1], light_position[2]);
	glColor3fv(current_property == 1?select_color:normal_color);
	glRasterPos2f(-1.0f, 0.7f);
	glPrint("Spotlight Direction:( %1.2f, %1.2f, %1.2f )", spot_direction[0], spot_direction[1], spot_direction[2]);
	glColor3fv(current_property == 2?select_color:normal_color);
	glRasterPos2f(-1.0f, 0.4f);
	glPrint("Spotlight Exponent:( %1.2f )", spot_exponent);
	glColor3fv(current_property == 3?select_color:normal_color);
	glRasterPos2f(-1.0f, 0.1f);
	glPrint("Spotlight Angle:( %3.0f )", spot_angle);
	glColor3fv(current_property == 4?select_color:normal_color);
	glRasterPos2f(-1.0f, -0.2f);
	glPrint("Attenuation:( %1.2f, %1.2f, %1.2f )", attenuation[0], attenuation[1], attenuation[2]);
	glEnable(GL_LIGHTING);

	glColor3fv(normal_color);
	glViewport(0, 0, win_width * 2.0f / 3.0f, win_height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (win_width * 2.0f / 3.0f) / win_height, 1.0f, 20.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -3.0f);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, spot_angle);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, spot_exponent);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, attenuation[0]);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, attenuation[1]);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, attenuation[2]);
	glPopMatrix();
	glPushMatrix();
	gluLookAt(0.0f, 1.0f, 3.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	glPushMatrix();
	glTranslatef(-0.5f, -0.5f, 0.0f);
	glRotatef(90, -1.0f, 0.0f, 0.0f);
	glutSolidCone(0.6f, 1.0f, 40, 5);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-0.5f, 0.0f, 0.0f);
	glRotatef(90, -1.0f, 0.0f, 0.0f);
	glutSolidTorus(0.15f, 0.4f, 20, 20);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.4f, -0.2f, -0.5f);
	glRotatef(90, -1.0f, 0.0f, 0.0f);
	glutSolidSphere(0.6f, 20, 20);
	glPopMatrix();
	glPopMatrix();
	glutSwapBuffers();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(1200, 700);
	glutCreateWindow(argv[0]);
	Init();
	printf("Press 'W': Select Next Property\n");
	printf("Press 'S': Select Previous Property\n");
	printf("Press 'U': Increase 'X' Component of Property\n");
	printf("Press 'J': Decrease 'X' Component of Property\n");
	printf("Press 'I': Increase 'Y' Component of Property\n");
	printf("Press 'K': Decrease 'Y' Component of Property\n");
	printf("Press 'O': Increase 'Z' Component of Property\n");
	printf("Press 'L': Decrease 'Z' Component of Property\n");
	glutDisplayFunc(Display);
	glutReshapeFunc(Resize);
	glutKeyboardFunc(Keyboard);
	glutMainLoop();
}