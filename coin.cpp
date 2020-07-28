#include "coin.h"

Coin::Coin():
  x(0),
  y(0)
{
}

Coin::~Coin(){
  
}

void Coin::setRandomPosition(){
  setPosition(random(60), random(16));
}

void Coin::setPosition(short int toX, short int toY){
  x = toX;
  y = toY;
}
