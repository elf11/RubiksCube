#include <windows.h>
#include "Mover.h"

int win_w = 1, win_h = 1;

/*
 * O serie de variabile in care retinem :
 * aspectul ferestrei
 * rotatia pe x si y
 * unghiul de rotatie
 * tipul rotatiei
 * pasul de rotatie
 * daca am rezolvat deja cubul
 * bufferul in care scriem
 * numarul de mutari
 * numarul de mutari efectuate la rezolvare
 * timpul - scurs, curent, vechi
 * vectorul de miscari utilizat la rezolvarea automata a cubului
 * vectorul de miscari inversate
 * flaguri daca am rezolvat sau nu cubul, daca am afisat sau nu scorul, daca rezolvam automat sau nu
 *
 */

GLfloat aspect = 1;
GLfloat xRot = 0.0f;
GLfloat yRot = 0.0f;
static GLfloat rot = 0.0f;
static int type = 0;
static int ok = 0;
static GLfloat rStep = 0.087264;
static int notSolved = 0;
static char frbuf[100] = "";
static int moves = -1;
static int did = 0;
static GLfloat elapsedTime = 0;
static GLfloat currentTime = 0;
static GLfloat oldTime = 0;

int movesArray[300];
int reverse[300];

bool flag = false;
bool automate = false;
bool write = false;

Mover *mover = new Mover();


void init(void)
{
	glClearColor(0.0f, 0.0f, 0.1f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

	printf("int type = %d, rot = %f\n", type, rot);
	mover->drawCube(type, rot);
	glPopMatrix();

	glutSwapBuffers();
}

void reshape(int w, int h)
{
	//transformarea in poarta de vizualizare
	glViewport(0,0, (GLsizei) w, (GLsizei) h);

	aspect = (GLfloat) w / (GLfloat) h;

	//se lucreaza pe matricea de proiectie
	glMatrixMode(GL_PROJECTION);
	//se porneste de la matricea identitate
	glLoadIdentity();

	// setam perspectiva intr-un mod cat mai dragut
	if (w <= h) 
		glOrtho (-50, 50, -50*h/w, 50*h/w, -50, 50);
    else 
		glOrtho (-50*w/h, 50*w/h, -50, 50, -50, 50);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	win_w = w;
	win_h = h;
}

void animatieDisplay(int value)
{
	/*
	 * trcem in modul rezolvare culoarea backgroundului se schimba, nu mai este albastru este o nuanta de rosu.
	 */
	if (notSolved == 0 && flag == true)
	{
		glClearColor(0.1f, 0.0f, 0.0f, 0.0f);
		oldTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
		notSolved = 1;
		moves = 0;
		glutPostRedisplay();
		glutTimerFunc(25, animatieDisplay, 1);
		return;
	}

	if (write == true)
	{
		write = false;
		currentTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
		elapsedTime = currentTime - oldTime;
		sprintf(frbuf, "Timpul de pana acum este %f secunde. Numarul de mutari este este %d.", elapsedTime, moves);
		printf("moves = %d\n", moves);
		glColor3f(0.0f, 0.0f, 1.0f);
		glRasterPos2f(-50, 30);
		int len = strlen(frbuf);
		for (int i = 0; i < len; i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, frbuf[i]);
		}
		glutSwapBuffers();
		glClearColor(0.0f, 0.0f, 0.1f, 0.0f);
		Sleep(3000);
		//glutTimerFunc(25, animatieDisplay, 1);
		return;
	}

	if (automate == true)
	{
		int j = did - 1;
		for (int i = 0; i < did && j >= 0; i += 1)
		{
			reverse[i] = movesArray[j];
			j -= 1;
		}
		for (int i = 0; i < did; i += 1)
		{
			mover->rotateLocal(reverse[i]);
			reverse[i] = 0;
			ok = 0;
			rot = 0.0f;
			glutPostRedisplay();
		}
		moves = did;
		currentTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
		elapsedTime = currentTime - oldTime;
		automate = false;
		glutPostRedisplay();
		glutTimerFunc(25, animatieDisplay, 1);
		return;
	}

	if (rot >= M_PI/2)
	{
		mover->rotateLocal(type);
		type = 0;
		ok = 0;
		rot = 0.0f;
		glutPostRedisplay();
		if (moves > -1)
		{
			moves += 1;
		}
		return;
	}

	rot += rStep;
	glutPostRedisplay();
	glutTimerFunc(25, animatieDisplay, 1);
}

void keyHandler(unsigned char key, int k, int y)
{
	switch(key)
	{
	case 27 :
		exit(0);
		break;
	case 'a' :
		if (ok == 1)
			return;
		type = 1;
		movesArray[did] = 7;
		did += 1;
		ok = 1;
		rot = 0.0f;
		glutTimerFunc(25, animatieDisplay, 1);
		break;
	case 's' :
		if (ok == 1)
			return;
		type = 2;
		movesArray[did] = 8;
		did += 1;
		ok = 1;
		rot =0.0f;
		glutTimerFunc(25, animatieDisplay, 1);
		break;
	case 'd' :
		if (ok == 1)
			return;
		type = 3;
		movesArray[did] = 9;
		did += 1;
		ok = 1;
		rot = 0.0f;
		glutTimerFunc(25, animatieDisplay, 1);
		break;
	case 'f' :
		if (ok == 1)
			return;
		type = 4;
		movesArray[did] = 10;
		did += 1;
		ok = 1;
		rot = 0.0f;
		glutTimerFunc(100, animatieDisplay, 1);
		break;
	case 'g' :
		if (ok == 1)
			return;
		type = 5;
		movesArray[did] = 11;
		did += 1;
		ok = 1;
		rot = 0.0f;
		glutTimerFunc(25, animatieDisplay, 1);
		break;
	case 'h' :
		if (ok == 1)
			return;
		type = 6;
		movesArray[did] = 12;
		did += 1;
		ok = 1;
		rot = 0.0f;
		glutTimerFunc(25, animatieDisplay, 1);
		break;
	case 'q' :
		if (ok == 1)
			return;
		type = 7;
		movesArray[did] = 1;
		did += 1;
		ok = 1;
		rot = 0.0f;
		glutTimerFunc(25, animatieDisplay, 1);
		break;
	case 'w' :
		if (ok == 1)
			return;
		type = 8;
		movesArray[did] = 2;
		did += 1;
		ok = 1;
		rot = 0.0f;
		glutTimerFunc(25, animatieDisplay, 1);
		break;
	case 'e' :
		if (ok == 1)
			return;
		type = 9;
		movesArray[did] = 3;
		did += 1;
		ok = 1;
		rot = 0.0f;
		glutTimerFunc(25, animatieDisplay, 1);
		break;
	case 'r' :
		if (ok == 1)
			return;
		type = 10;
		movesArray[did] = 4;
		did += 1;
		ok = 1;
		rot = 0.0f;
		glutTimerFunc(25, animatieDisplay, 1);
		break;
	case 't' :
		if (ok == 1)
			return;
		type = 11;
		movesArray[did] = 5;
		did += 1;
		ok = 1;
		rot = 0.0f;
		glutTimerFunc(25, animatieDisplay, 1);
		break;
	case 'y' :
		if (ok == 1)
			return;
		type = 12;
		movesArray[did] = 6;
		did += 1;
		ok = 1;
		rot = 0.0f;
		glutTimerFunc(25, animatieDisplay, 1);
		break;
	case 'v' :
		xRot -= 5.0f;
		glutTimerFunc(25, animatieDisplay, 1);
		break;
	case 'b' :
		xRot += 5.0f;
		glutTimerFunc(25, animatieDisplay, 1);
		break;
	case 'n' :
		yRot -= 5.0f;
		glutTimerFunc(25, animatieDisplay, 1);
		break;
	case 'm' :
		yRot += 5.0f;
		glutTimerFunc(25, animatieDisplay, 1);
		break;
	case 'o' :
		//trecem in modul rezolvare prin apasarea tastei 'o'
		flag = true;
		glutTimerFunc(25, animatieDisplay, 1);
		break;
	case 'p':
		//semnalam jocului faptul ca am terminat de rezolvat cubul si asteptam feedback
		write = true;
		//user = true;
		glutTimerFunc(25, animatieDisplay, 1);
		break;
	case 'i':
		// incepem rezolvarea automata a cubului
		automate = true;
		glutTimerFunc(25, animatieDisplay, 1);
		break;

	}

	if(xRot > 356.0f)
		xRot = 0.0f;

	if(xRot < -1.0f)
		xRot = 355.0f;

	if(yRot > 356.0f)
		yRot = 0.0f;

	if(yRot < -1.0f)
		yRot = 355.0f;

	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("TEMA 2 EGC - RUBIK");
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyHandler);
	glutDisplayFunc(display);
	init();
	glutMainLoop();

	return 0;
}