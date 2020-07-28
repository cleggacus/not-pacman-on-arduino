#include <Arduino.h>
#include "player.h"

class Enimy{
  private:
    short int x;
    short int y;
    bool toggleState;

  public:
    Enimy(short int initX, short int initY);
    ~Enimy();

    void updateEnimy(Player p);
    void moveAsset(Player p);
    void restart(short int initX, short int initY);
    bool getAssetPixel(short int byX, short int byY);
    bool isColliding(short int byX, short int byY);
    
    short int getX(){return x;};
    short int getY(){return y;};
};
