#include "player.h"

Player::Player(short int initX, short int initY):
  x(initX),
  y(initY),
  vx(1),
  vy(0),
  rotation(right),
  isOpen(false)
{
  
}

Player::~Player(){
  
}

void Player::restart(short int initX, short int initY){
  x = initX;
  y = initY;
}

void Player::resolveCollision(){
  for(short int i = 0; i < 7; i++){
    bool result[7];
    
    for (short int j = 0; j < 7; j++)
        result[6-j] = (asset[isOpen ? (short int)rotation : 0][i] & (1 << j)) == 0 ? false : true;
    
    for(short int j = 0; j < 7; j++){
      if(result[j]){
        bool changed = false;
        if((x <= 0 && rotation == left) || (x+7 >= 60 && rotation == right)){
          vx = 0;
          changed = true;
        }
        
        if((y + 7 >= 16 && rotation == down) || (y <= 0 && rotation == up)){
          vy = 0;
          changed = true;
        }

        if(changed)
          return;
      }
    }
  }
}

void Player::rotate(Rotation targetR){
  rotation = targetR;
  
  if(rotation == left){
    vx = -1;
    vy = 0;
  }else if(rotation == up){
    vx = 0;
    vy = -1;
  }else if(rotation == down){
    vx = 0;
    vy = 1;
  }else if(rotation == right){
    vx = 1;
    vy = 0;
  }

  resolveCollision();
}
bool Player::isColliding(short int byX, short int byY){
  byX -= x;
  byY -= y;
  
  if(byX >= 7 || byX < 0 || byY >= 7 || byY < 0)
    return false;
    
  return true;
}

bool Player::getAssetPixel(short int byX, short int byY){
  if(!isColliding(byX, byY))
    return false;
    
  byX -= x;
  byY -= y;
  
  bool result[7];

  for (short int i = 0; i < 7; i++)
      result[6-i] = (asset[isOpen ? (short int)rotation : 0][byY] & (1 << i)) == 0 ? false : true;
    
  return result[byX];
}

void Player::updatePlayer(){
  toggleOpen();
  resolveCollision();
  moveAsset(vx, vy);
}

void Player::moveAsset(short int byX, short int byY){
  x += byX;
  y += byY;
}

void Player::toggleOpen(){
  isOpen = !isOpen;
}
