#include "enimy.h"

Enimy::Enimy(short int initX, short int initY):
  x(initX),
  y(initY),
  toggleState(false)
{
}

Enimy::~Enimy(){
  
}

void Enimy::restart(short int initX, short int initY){
  x = initX;
  y = initY;
}

bool Enimy::isColliding(short int byX, short int byY){
  byX -= x;
  byY -= y;
  
  if(byX >= 2 || byX < 0 || byY >= 2 || byY < 0)
    return false;
    
  return true;
}

bool Enimy::getAssetPixel(short int byX, short int byY){
  if(!isColliding(byX, byY))
    return false;
    
  byX -= x;
  byY -= y;
  
  return toggleState ? byX != byY : byX == byY;
}

void Enimy::updateEnimy(Player p){
  moveAsset(p);
  toggleState = !toggleState;
}

void Enimy::moveAsset(Player p){
  if(x > p.getX())
    x --;
  else if(x < p.getX())
    x ++;

  if(y > p.getY())
    y --;
  else if(y < p.getY())
    y ++;
}
