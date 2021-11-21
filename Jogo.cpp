#include <GL/glut.h>
#include <GL/GL.h>
#include "Cabecalho.h"
#include <ctime>
#include <math.h>

extern int score;
extern int veloc;
extern bool GAMEOVER;

int gridX, gridY;
bool comida = true;
int comidaX, comidaY;
int snake_lenght = 5;
GLfloat PI2 = 3.1415;
GLfloat bolaRaio2 = 0.5f;

short direction = RIGHT;

int posX[60] = { 20,20,20,20,20 }, posY[60] = {20,19,18,17,16}; //start position for snake

void initGrid(int x, int y) {
	gridX = x;
	gridY = y;
}
//draw unit
void unidade(int x, int y) {

	glLineWidth(5.0);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINE_LOOP);
	
	
	glEnd();

}

//draw grid
void desenharGrid() {

	for (int x = 0; x < gridX; x++) {
		for (int y = 0; y < gridY; y++) {
			unidade(x, y);
		}
	}

}

//draw food
void desenharComida() {
	if (comida)
		randomValue(comidaX, comidaY);
	comida = false;
	
	glColor3f(0.0, 0.0, 1.0);
	glRectf(comidaX, comidaY, comidaX + 1, comidaY + 1);

	/*glLoadIdentity();
	glTranslatef(comidaX, comidaY, 0.0);
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.0, 0.0, 1.0);
	int numSeg = 100;
	GLfloat angulo;
	for (int i = 0; i <= numSeg; i++) {
		angulo = i * 2.0 * PI2 / numSeg;
		glVertex2f(cos(angulo) * bolaRaio2, sin(angulo) * bolaRaio2);

	}
	glEnd();*/

}

//Show screen when you win

//Snake body
void desenharCorpo() {
	
	for (int i = snake_lenght - 1; i > 0; i--) {
		posX[i] = posX[i - 1];
		posY[i] = posY[i - 1];
		
	}
	if (direction == UP)
		posY[0]++;
	else if (direction == DOWN) 
		posY[0]--;
	if (direction == RIGHT)
		posX[0]++;
	else if (direction == LEFT)
		posX[0]--;
	
	for (int i = 0; i < snake_lenght; i++) {
		if (i == 0)
			glColor3f(1.0, 1.0, 1.0);
		else
			glColor3f(1.0, 0.25, 0.0);

		glRectd(posX[i], posY[i], posX[i] + 1, posY[i] + 1);
		
		
		
	}

	if (posX[0] == 0 || posX[0] == gridX + 0 || posY[0] == 0 || posY[0] ==gridY -1)
		GAMEOVER = true;

	if (posX[0] == comidaX && posY[0] == comidaY) {
		score++;
		snake_lenght++;
		comida = true;
		if (score == 15 && veloc != 5 && veloc != 30)  veloc = 12; 
		if (score == 20 && veloc != 5 && veloc != 30) veloc = 13;
		if (score == 30 && veloc != 5 && veloc != 30) veloc = 14;
		if (score == 40 && veloc != 5 && veloc != 30) veloc = 16;
		if (score == 45 && veloc != 5 && veloc != 30) veloc = 17;
		if (score == 50 && veloc != 5 && veloc != 30) veloc = 20;
		if (score == 55 && veloc != 5 && veloc != 30) {

			
		
		}
	}
	
	

}


//Charge food location
void randomValue(int &x, int &y) {

	int _maxX = gridX - 2;
	int _maxY = gridY - 2;
	int _min = 1;
	srand(time(NULL));
	x = _min + rand() % (_maxX - _min);
	y = _min + rand() % (_maxY - _min);

}





