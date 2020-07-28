#include <Arduino.h>
#include <LiquidCrystal.h>
#include "coin.h"
#include "enimy.h"

class Renderer{
  private:
    bool grid [16][60];
    String s1;
    String s2;
    
  public:
    Renderer(short int pins[6]);
    ~Renderer();

    LiquidCrystal lcd;

    void resetGrid();
    void renderCenterText();
    void render(Player player, Enimy enimy, short int coinsSize, Coin coins[]);
    inline void setS1(String s){s1 = s;};
    inline void setS2(String s){s2 = s;};
};
