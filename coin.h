#include <Arduino.h>

class Coin{
  private:
    short int x;
    short int y;

  public:
    Coin();
    ~Coin();

    void setRandomPosition();
    void setPosition(short int toX, short int toY);
    short int getX(){return x;};
    short int getY(){return y;};
};
