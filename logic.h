#ifndef LOGIC_H_INCLUDED
#define LOGIC_H_INCLUDED
#include <iostream>
#include <string>
#include<vector>
#include <fstream>
#include<cstring>
#include <cmath>
const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 800;

const int MAX = 2048;
int score =6;




int copy_board[4][4];

int board[4][4]={0};

void add_random();

void display();

void moveleft();

void moveright();

void movebottom();

void board_copy();

bool check_board_copy();

void moveup();

bool check_over();

bool check_win();

 bool check_0();


#endif // LOGIC_H_INCLUDED
