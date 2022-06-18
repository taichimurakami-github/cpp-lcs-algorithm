#include <stdio.h>
#include <iostream>

// using namespace std;

struct LcsCell
{
  int score;
  int row;
  int col;
  // LcsCell *prev_cell;
};

void input(std::string *str_A, std::string *str_B);

void resetLcsTable(LcsCell **dp, int y, int x);

void printDpTable(LcsCell **dp, int y, int x);

void fillInCell(LcsCell *cell, int score, int y, int x, LcsCell *prev_cell);

void fillInLcsTable(LcsCell **dp, std::string *str_A, std::string *str_B, int y, int x);
