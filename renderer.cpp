#include "renderer.h"

Renderer::Renderer(short int pins[6]):
  lcd(LiquidCrystal(pins[0],pins[1],pins[2],pins[3],pins[4],pins[5]))
{
}

Renderer::~Renderer(){
}

byte boolsToByte(bool b[], short int size){
  byte result = 0;
  
  for(short int i = 0; i < size; i++){
      if(b[i])
         result |= (1 << (size-1-i));
  }
  
  return result;
}

void Renderer::renderCenterText(){
  lcd.begin(16, 2);
  lcd.setCursor(floor((16-s1.length())/2), 0);
  lcd.print(s1);
  lcd.setCursor(ceil((16-s2.length())/2), 1);
  lcd.print(s2);
}

void Renderer::render(Player player, Enimy enimy, short int coinsSize, Coin coins[]){
  for(short int i = 0; i < 16; i++){
    for(short int j = 0; j < 60; j++){
      if(player.getAssetPixel(j, i) || enimy.getAssetPixel(j, i))
        grid[i][j] = true;
      else
        grid[i][j] = false;

      for(short int k = 0; k < coinsSize; k++){
        short int cx = coins[k].getX();
        short int cy = coins[k].getY();

        if(cx == j && cy == i)
          grid[i][j] = true;
      }
    }
  }

  
  lcd.begin(16, 2);
  short int curChar = 0;

  for(short int i = 0; i < 24; i++){
    bool isChar = false;
    byte b[8];
    short int row = i >= 12 ? 1 : 0;
    
    for(short int j = 0; j < 8; j++){
      bool bs[5];
      
      for(short int k = 0; k < 5; k++){
        bs[k] = grid[j+row*8][k + i*5 - 60*row];
        
        if(bs[k])
          isChar = true;
      }

      b[j] = boolsToByte(bs, 5);
    }

    if(isChar){
      lcd.createChar(curChar, b);
      lcd.setCursor(i - row*12, row);
      lcd.write(byte(curChar));
      curChar++;
    }
  }

  lcd.setCursor(12, 0);
  lcd.print(s1);
  lcd.setCursor(12, 1);
  lcd.print(s2);
}
