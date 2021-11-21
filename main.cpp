/*
*******************************************************************************************************************
**           SNAKE SPACE
**
**				 BY
**
**	   HENRIQUE DAS VIRGENS
**	   
**	   
*******************************************************************************************************************
*******************************************************************************************************************
**				G A M E   D E S C R I P T I O N
**
**					keybord controls=   UP, DOWN, RIGHT, LEFTH

**
**	  INSTRUCTIONS:
**					get food
**
**	  OBJECTIVE :   Get as many food as possible. Maximum 55
**					
**					
*******************************************************************************************************************
*/

#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <windows.h>
#include <string.h>
#include <GL/gl.h>


#include "Cabecalho.h"
#include <math.h>
#include <iostream>

//#include <vector>

#define COLUMNS 40
#define ROWS 40
int stoneTranslationSpeed = 5;


extern short direction;
int score = 0;
int veloc = 10; //frames per second (fps)
int auxVeloc;

bool GAMEOVER = false;

GLfloat PI = 3.1415;
GLfloat bolaRaio = 0.5f;
GLfloat bolaX = 0.0f;
GLfloat bolaY = 0.0f;

//Menu itens
enum MENU_TYPE {
	EASY,
	NORMAL,
	HARD,
	EXIT
};

//Menu handling function definition
void menu(int item) {

	switch (item) {
	case EASY:
	{
		veloc = 5;
	}break;
	case NORMAL:
	{
		veloc = 10;
	}break;
	case HARD:
	{	
		veloc = 30;
	}break;
	case EXIT:
		exit(1);

	}
	glutPostRedisplay(); //Continues the animation
}

struct point
{
	float x, y;
	point() {}
	point(float a, float b) { x = a; y = b; }
};

int random(int lower, int upper)
{
	return (rand() % (upper - lower + 1)) + lower;
}

//Stars in background
void estrelas() {
	glColor3f(1, 1, 1);
	glPointSize(3);
	glBegin(GL_POINTS);
	for (int i = 0; i < 100; i++)
		glVertex3f(random(0, 600), random(0, 500), 1.0f);
	glVertex3f(random(0, 600), random(0, 500), 1.0f);
	glEnd();

	glFlush();

}

//Display score
void displayText(float x, float y, float z, char* stringToDisplay) {
	int length;
	glRasterPos3f(x, y, z);
	length = strlen(stringToDisplay);

	for (int i = 0; i < length; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, stringToDisplay[i]);
	}
}

//The sun
void circle() {
	float theta;
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.7, 0.7, 0.0);
	glPointSize(1.0);
	glBegin(GL_POLYGON);
	for (theta = 0; theta <= 360; theta += 0.01) {
		glVertex2f(20 * sin(theta * 3.142 / 180), 20 * cos(theta * 3.142 / 180));
	}
	glEnd();
	glFlush();
}

// Welcome screen
void welcome() {
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 0.0);
	glRasterPos3f(13.8, 35.5, 0.0);
	char msg1[] = "SPACE SNAKE";
	for (int i = 0; i < strlen(msg1); i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, msg1[i]);

	glColor3f(1.0, 1.0, 1.0);
	glRasterPos3f(3.8, 30.5, 0.0);
	char msg2[] = "DEVELOPED BY:";
	for (int i = 0; i < strlen(msg2); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, msg2[i]);

	glColor3f(1.0, 1.0, 1.0);
	glRasterPos3f(5.0, 29.5, 0.0);
	char msg0[] = " HENRIQUE DAS VIRGENS";
	for (int i = 0; i < strlen(msg0); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, msg0[i]);


	glColor3f(1.0, 1.0, 1.0);
	glRasterPos3f(12.8, 5.5, 0.0);
	char msg3[] = "PRESS SPACE TO START THE GAME";
	for (int i = 0; i < strlen(msg3); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, msg3[i]);

	glutSwapBuffers();
}

//Show game over when you lose
void gameOver() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 0.0);
	glRasterPos3f(13.8, 35.5, 0.0);
	char msg1[] = "GAME OVER";
	for (int i = 0; i < strlen(msg1); i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, msg1[i]);

	glutSwapBuffers();
}
void winner() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 0.0);
	glRasterPos3f(13.8, 35.5, 0.0);
	char msg1[] = "YOU WIN!";
	for (int i = 0; i < strlen(msg1); i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, msg1[i]);

	glutSwapBuffers();
}

void display(void) {
	//select clearing(background) color
	glClearColor(0.0, 0.0, 0.15, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	circle();
	desenharGrid();
	desenharCorpo();
	
	desenharComida();
	
	estrelas();

	char temp[40];
	glColor3f(1, 1, 1);
	sprintf_s(temp, "SCORE = %d", score); 
	displayText(0.5, 38, 0.0, temp);//show score on screen
	glutSwapBuffers();
	if (score == 55) {
		winner();
	}
	if (GAMEOVER && score!=55) {
		gameOver();
		//exit(0);
	}

	//glutPostRedisplay(); //criar loop em display
	/*glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-2, 2, -2, 2);

	glBegin(GL_POLYGON);
	glVertex2f(0, 0);
	glVertex2f(0, 0);
	glVertex2f(0, 0);
	glEnd();*/
	glFlush();
}

//comands to the game
void keyboard(int key, int, int) {
	
	switch (key)
	{
		case GLUT_KEY_UP:
			if (direction != DOWN)
				direction = UP;
			break;
		case GLUT_KEY_DOWN:
			if (direction != UP)
				direction = DOWN;
			break;
	case GLUT_KEY_RIGHT:
		if (direction != LEFT)
			direction = RIGHT;
		break;
	case GLUT_KEY_LEFT:
		if (direction != RIGHT)
			direction = LEFT;
	}
}

void timer(int) {

	glutPostRedisplay();
	glutTimerFunc(1000/ veloc, timer,0);

}

void reshape(int l, int h) {

	glViewport(0, 0, (GLsizei)l, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, COLUMNS, 0.0, ROWS, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);



}

void init() {

	//select clearing(background) color
	glClearColor(0.0, 0.0, 0.0, 1.0);
	initGrid(COLUMNS, ROWS);
	

}

//Space to Start the game
void start(unsigned char key, int x, int y) {

	if (key == ' ') {
		glutDisplayFunc(display);

	}

	glutPostRedisplay();

}


int main(int argc, char** argv) {
	glutInit(&argc, argv); // initializes GLUT and processes any command line arguments
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // specifies whether to use an RGBA or color-index color model
	glutInitWindowSize(600, 500); //specifies the size, in pixels, of your window
	glutCreateWindow("Space Snake "); // creates a window with an OpenGL context
	glutDisplayFunc(welcome); // is the first and most important event callback function

	//Reshape
	glutReshapeFunc(reshape); // indicates what action should be taken when the window is resized

	glutTimerFunc(0,timer, 0);

	glutSpecialFunc(keyboard); //allow you to link a keyboard key with a routine that's invoked when the key is pressed 

	glutKeyboardFunc(start);
	//create menu
	glutCreateMenu(menu);
	glutAddMenuEntry("EASY", EASY); 
	glutAddMenuEntry("NORMAL", NORMAL);
	glutAddMenuEntry("HARD", HARD);
	glutAddMenuEntry("EXIT", EXIT);
	//Associating the mouse with the menu
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	init();
	glutMainLoop(); //All windows that have been created are now shown, once this loop is entered, it is never exited
	return 0;
}
















