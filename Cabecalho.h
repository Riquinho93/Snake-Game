#pragma once
#define GAME_H_INCLUDED

#define UP 1
#define DOWN -1
#define RIGHT 2
#define LEFT -2
#define velocidadeSnake 10	

void initGrid(int, int);
void desenharGrid();
void desenharCorpo();
void desenharComida();
void randomValue(int &, int &);
