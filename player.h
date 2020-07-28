#include <Arduino.h>

enum Rotation{
  none, right, up, left, down
};

class Player{
  private:
    short int x;
    short int y;
    short int vx;
    short int vy;
    bool isOpen;
    Rotation rotation;

    byte asset[5][7] = {
      {
        byte(B0011100),
        byte(B0111110),
        byte(B1111111),
        byte(B1111111),
        byte(B1111111),
        byte(B0111110),
        byte(B0011100)
      },{
        byte(B0011100),
        byte(B0111100),
        byte(B1111000),
        byte(B1110000),
        byte(B1111000),
        byte(B0111100),
        byte(B0011100)
      },{
        byte(B0000000),
        byte(B0000000),
        byte(B1100011),
        byte(B1110111),
        byte(B1111111),
        byte(B0111110),
        byte(B0011100)
      },{
        byte(B0011100),
        byte(B0011110),
        byte(B0001111),
        byte(B0000111),
        byte(B0001111),
        byte(B0011110),
        byte(B0011100)
      },{
        byte(B0011100),
        byte(B0111110),
        byte(B1111111),
        byte(B1110111),
        byte(B1100011),
        byte(B0000000),
        byte(B0000000)
      }
    };

  public:
    Player(short int initX, short int initY);
    ~Player();
    
    void moveAsset(short int byX, short int byY);
    bool getAssetPixel(short int byX, short int byY);
    bool isColliding(short int byX, short int byY);
    void rotate(Rotation targetR);
    void resolveCollision();
    void updatePlayer();
    void toggleOpen();
    void restart(short int initX, short int initY);
    
    inline short int getX(){return x;};
    inline short int getY(){return y;};
    inline short int getVX(){return vx;};
    inline short int getVY(){return vy;};
    inline Rotation getR(){return rotation;};
    
};
