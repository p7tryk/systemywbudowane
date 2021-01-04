#pragma once
#include <stdio.h>
#include <stdlib.h>

class LiquidCrystal
{
public:
  LiquidCrystal(int a, int b, int c, int d, int e, int f);
  void begin(int columns, int rows);
  void print(char * string);
  void setCursor(int columns, int rows);
private:
  char * display;
  char * cursor;
  int colcount, rowcount;
  

};

LiquidCrystal::LiquidCrystal(int a, int b, int c, int d, int e, int f)
{
  printf("display initialized");
}
void LiquidCrystal::begin(int columns, int rows)
{
  display = (char * ) malloc(sizeof(char) * columns * rows);
  cursor = display;
  colcount = columns;
  rowcount = rows;
}
void LiquidCrystal::setCursor(int columns, int rows)
{
  cursor = &display[rows*colcount+columns];
}

void LiquidCrystal::print(char * string)
{

}
