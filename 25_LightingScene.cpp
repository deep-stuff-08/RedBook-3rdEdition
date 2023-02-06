#include<GL/freeglut.h>
#include<stdio.h>
#include<math.h>

#define SPEED 0.01f
#define COLOR_SELECTED(param) (current_property == param ? select_color : normal_color) 

GLubyte noOfSettings = 4;
GLubyte current_setting = 0;
GLubyte noOfProperties[] = {4, 5, 5, 5};
GLubyte current_property = 0;
GLfloat select_color[] = {0.0f, 1.0f, 0.0f};
GLfloat normal_color[] = {1.0f, 1.0f, 1.0f};
GLsizei win_width, win_height;

GLfloat light_ambient[] = {0.0f, 0.0f, 0.0f};
GLfloat light_diffuse[] = {1.0f, 1.0f, 1.0f};
GLfloat light_specular[] = {1.0f, 1.0f, 1.0f};
GLfloat light_position[] = {0.0f, 0.0f, 1.0f, 1.0f};

GLfloat cone_ambient[] = {0.2f, 0.2f, 0.2f};
GLfloat cone_diffuse[] = {0.8f, 0.8f, 0.8f};
GLfloat cone_specular[] = {0.0f, 0.0f, 0.0f};
GLfloat cone_emission[] = {0.0f, 0.0f, 0.0f};
GLfloat cone_shininess[] = {0.0f};

GLfloat torus_ambient[] = {0.2f, 0.2f, 0.2f};
GLfloat torus_diffuse[] = {0.8f, 0.8f, 0.8f};
GLfloat torus_specular[] = {0.0f, 0.0f, 0.0f};
GLfloat torus_emission[] = {0.0f, 0.0f, 0.0f};
GLfloat torus_shininess[] = {0.0f};

GLfloat sphere_ambient[] = {0.2f, 0.2f, 0.2f};
GLfloat sphere_diffuse[] = {0.8f, 0.8f, 0.8f};
GLfloat sphere_specular[] = {0.0f, 0.0f, 0.0f};
GLfloat sphere_emission[] = {0.0f, 0.0f, 0.0f};
GLfloat sphere_shininess[] = {0.0f};

GLfloat *selected_setting[5];
GLfloat *selected_property;

const char *settingnames[] = {
	"Lighting",
	"Cone Material",
	"Torus Material",
	"Sphere Material"
};

const char *lightpropnames[] = {
	"Ambient",
	"Diffuse",
	"Specular",
	"Position"
};

const char *materialpropnames[] = {
	"Ambient",
	"Diffuse",
	"Specular",
	"Emission",
	"Shininess"
};

void Keyboard(unsigned char key, int kx, int ky) {
	switch(key) {
	case 27:
		glutLeaveMainLoop();
		break;
	case 'F': case 'f':
		glutFullScreenToggle();
		break;
	case 'A': case 'a':
		if(current_setting > 0) {
			current_property = 0;
			current_setting--;
			if(current_setting == 0) {
				selected_setting[0] = light_ambient;	
				selected_setting[1] = light_diffuse;	
				selected_setting[2] = light_specular;	
				selected_setting[3] = light_position;
				selected_property = light_ambient;	
			} else if(current_setting == 1) {
				selected_setting[0] = cone_ambient;	
				selected_setting[1] = cone_diffuse;	
				selected_setting[2] = cone_specular;	
				selected_setting[3] = cone_emission;
				selected_setting[4] = cone_shininess;
				selected_property = cone_ambient;	
			} else if(current_setting == 2) {
				selected_setting[0] = torus_ambient;	
				selected_setting[1] = torus_diffuse;	
				selected_setting[2] = torus_specular;	
				selected_setting[3] = torus_emission;
				selected_setting[4] = torus_shininess;
				selected_property = torus_ambient;	
			} else if(current_setting == 3) {
				selected_setting[0] = sphere_ambient;	
				selected_setting[1] = sphere_diffuse;	
				selected_setting[2] = sphere_specular;	
				selected_setting[3] = sphere_emission;
				selected_setting[4] = sphere_shininess;
				selected_property = sphere_ambient;	
			}
		}
		break;
	case 'D': case 'd':
		if(current_setting < noOfSettings - 1) {
			current_property = 0;
			current_setting++;
			if(current_setting == 0) {
				selected_setting[0] = light_ambient;	
				selected_setting[1] = light_diffuse;	
				selected_setting[2] = light_specular;	
				selected_setting[3] = light_position;
				selected_property = light_ambient;	
			} else if(current_setting == 1) {
				selected_setting[0] = cone_ambient;	
				selected_setting[1] = cone_diffuse;	
				selected_setting[2] = cone_specular;	
				selected_setting[3] = cone_emission;
				selected_setting[4] = cone_shininess;
				selected_property = cone_ambient;	
			} else if(current_setting == 2) {
				selected_setting[0] = torus_ambient;	
				selected_setting[1] = torus_diffuse;	
				selected_setting[2] = torus_specular;	
				selected_setting[3] = torus_emission;
				selected_setting[4] = torus_shininess;
				selected_property = torus_ambient;	
			} else if(current_setting == 3) {
				selected_setting[0] = sphere_ambient;	
				selected_setting[1] = sphere_diffuse;	
				selected_setting[2] = sphere_specular;	
				selected_setting[3] = sphere_emission;
				selected_setting[4] = sphere_shininess;
				selected_property = sphere_ambient;	
			}
		}
		break;
	case 'W': case 'w':
		if(current_property > 0) {
			current_property--;
			selected_property = selected_setting[current_property];
		}
		break;
	case 'S': case 's':
		if(current_property < noOfProperties[current_setting] - 1) {
			current_property++;
			selected_property = selected_setting[current_property];
		}
		break;
	case 'U': case 'u':
		if(current_property == 4) {
			selected_property[0] += SPEED * 100;
			break;
		}
		if(selected_property[0] < 0.999f) {
			selected_property[0] += SPEED;
		}
		break;
	case 'I': case 'i':
		if(selected_property[1] < 0.999f) {
			selected_property[1] += SPEED;
		}
		break;
	case 'O': case 'o':
		if(selected_property[2] < 0.999f) {
			selected_property[2] += SPEED;
		}
		break;
	case 'J': case 'j':
		if(current_property == 4 && selected_property != NULL) {
			selected_property[0] -= SPEED * 100;
			break;
		}
		if(selected_property[0] > 0.009f) {
			selected_property[0] -=SPEED;
		}
		break;
	case 'K': case 'k':
		if(selected_property[1] > 0.009f) {
			selected_property[1] -=SPEED;
		}
		break;
	case 'L': case 'l':
		if(selected_property[2] > 0.009f) {
			selected_property[2] -=SPEED;
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

	selected_setting[0] = light_ambient;
	selected_setting[1] = light_diffuse;
	selected_setting[2] = light_specular;
	selected_setting[3] = light_position;
	selected_property = light_ambient;
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
	GLfloat gap = 0.3f;
	glColor3fv(normal_color);
	glRasterPos2f(-1.0f, 1.3f);
	glPrint(settingnames[current_setting]);
	if(current_setting == 0) {
		glColor3fv(current_property == 0?select_color:normal_color);
		glRasterPos2f(-1.0f, 1.0f);
		glPrint("Ambient:( %1.2f, %1.2f, %1.2f )", light_ambient[0], light_ambient[1], light_ambient[2]);
		glColor3fv(current_property == 1?select_color:normal_color);
		glRasterPos2f(-1.0f, 0.7f);
		glPrint("Diffuse:( %1.2f, %1.2f, %1.2f )", light_diffuse[0], light_diffuse[1], light_diffuse[2]);
		glColor3fv(current_property == 2?select_color:normal_color);
		glRasterPos2f(-1.0f, 0.4f);
		glPrint("Specular:( %1.2f, %1.2f, %1.2f )", light_specular[0], light_specular[1], light_specular[2]);
		glColor3fv(current_property == 3?select_color:normal_color);
		glRasterPos2f(-1.0f, 0.1f);
		glPrint("Position:( %1.2f, %1.2f, %1.2f )", light_position[0], light_position[1], light_position[2]);
	} else if(current_setting == 1) {
		glColor3fv(current_property == 0?select_color:normal_color);
		glRasterPos2f(-1.0f, 1.0f);
		glPrint("Ambient:( %1.2f, %1.2f, %1.2f )", cone_ambient[0], cone_ambient[1], cone_ambient[2]);
		glColor3fv(current_property == 1?select_color:normal_color);
		glRasterPos2f(-1.0f, 0.7f);
		glPrint("Diffuse:( %1.2f, %1.2f, %1.2f )", cone_diffuse[0], cone_diffuse[1], cone_diffuse[2]);
		glColor3fv(current_property == 2?select_color:normal_color);
		glRasterPos2f(-1.0f, 0.4f);
		glPrint("Specular:( %1.2f, %1.2f, %1.2f )", cone_specular[0], cone_specular[1], cone_specular[2]);
		glColor3fv(current_property == 3?select_color:normal_color);
		glRasterPos2f(-1.0f, 0.1f);
		glPrint("Emission:( %1.2f, %1.2f, %1.2f )", cone_emission[0], cone_emission[1], cone_emission[2]);
		glColor3fv(current_property == 4?select_color:normal_color);
		glRasterPos2f(-1.0f, -0.2f);
		glPrint("Shininess:( %1.2f )", cone_shininess[0]);
	} else if(current_setting == 2) {
		glColor3fv(current_property == 0?select_color:normal_color);
		glRasterPos2f(-1.0f, 1.0f);
		glPrint("Ambient:( %1.2f, %1.2f, %1.2f )", torus_ambient[0], torus_ambient[1], torus_ambient[2]);
		glColor3fv(current_property == 1?select_color:normal_color);
		glRasterPos2f(-1.0f, 0.7f);
		glPrint("Diffuse:( %1.2f, %1.2f, %1.2f )", torus_diffuse[0], torus_diffuse[1], torus_diffuse[2]);
		glColor3fv(current_property == 2?select_color:normal_color);
		glRasterPos2f(-1.0f, 0.4f);
		glPrint("Specular:( %1.2f, %1.2f, %1.2f )", torus_specular[0], torus_specular[1], torus_specular[2]);
		glColor3fv(current_property == 3?select_color:normal_color);
		glRasterPos2f(-1.0f, 0.1f);
		glPrint("Emission:( %1.2f, %1.2f, %1.2f )", torus_emission[0], torus_emission[1], torus_emission[2]);
		glColor3fv(current_property == 4?select_color:normal_color);
		glRasterPos2f(-1.0f, -0.2f);
		glPrint("Shininess:( %1.2f )", torus_shininess[0]);
	} else if(current_setting == 3) {
		glColor3fv(current_property == 0?select_color:normal_color);
		glRasterPos2f(-1.0f, 1.0f);
		glPrint("Ambient:( %1.2f, %1.2f, %1.2f )", sphere_ambient[0], sphere_ambient[1], sphere_ambient[2]);
		glColor3fv(current_property == 1?select_color:normal_color);
		glRasterPos2f(-1.0f, 0.7f);
		glPrint("Diffuse:( %1.2f, %1.2f, %1.2f )", sphere_diffuse[0], sphere_diffuse[1], sphere_diffuse[2]);
		glColor3fv(current_property == 2?select_color:normal_color);
		glRasterPos2f(-1.0f, 0.4f);
		glPrint("Specular:( %1.2f, %1.2f, %1.2f )", sphere_specular[0], sphere_specular[1], sphere_specular[2]);
		glColor3fv(current_property == 3?select_color:normal_color);
		glRasterPos2f(-1.0f, 0.1f);
		glPrint("Emission:( %1.2f, %1.2f, %1.2f )", sphere_emission[0], sphere_emission[1], sphere_emission[2]);
		glColor3fv(current_property == 4?select_color:normal_color);
		glRasterPos2f(-1.0f, -0.2f);
		glPrint("Shininess:( %1.2f )", sphere_shininess[0]);
	}
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
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glPopMatrix();
	glPushMatrix();
	gluLookAt(0.0f, 1.0f, 3.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, cone_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, cone_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, cone_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, cone_emission);
	glMaterialfv(GL_FRONT, GL_SHININESS, cone_shininess);
	glTranslatef(-0.5f, -0.5f, 0.0f);
	glRotatef(90, -1.0f, 0.0f, 0.0f);
	glutSolidCone(0.6f, 1.0f, 40, 5);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, torus_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, torus_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, torus_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, torus_emission);
	glMaterialfv(GL_FRONT, GL_SHININESS, torus_shininess);
	glTranslatef(-0.5f, 0.0f, 0.0f);
	glRotatef(90, -1.0f, 0.0f, 0.0f);
	glutSolidTorus(0.15f, 0.4f, 20, 20);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, sphere_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, sphere_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, sphere_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, sphere_emission);
	glMaterialfv(GL_FRONT, GL_SHININESS, sphere_shininess);
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
	printf("Press 'A': Goto Next Menu\n");
	printf("Press 'D': Goto Previous Menu\n");
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