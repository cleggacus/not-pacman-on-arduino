#include <LiquidCrystal.h>
#include "renderer.h"

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST      0

int tempo = 105;
int buzzer = 9;

int melody[] = {
  NOTE_B4, 16, NOTE_B5, 16, NOTE_FS5, 16, NOTE_DS5, 16,
  NOTE_B5, 32, NOTE_FS5, -16, NOTE_DS5, 8, 
  NOTE_C5, 16,
  NOTE_C6, 16, NOTE_G6, 16, NOTE_E6, 16, NOTE_C6, 32, NOTE_G6, -16, NOTE_E6, 8,

  NOTE_B4, 16,  NOTE_B5, 16,  NOTE_FS5, 16,   NOTE_DS5, 16,  NOTE_B5, 32,
  NOTE_FS5, -16, NOTE_DS5, 8,  NOTE_DS5, 32, NOTE_E5, 32,  NOTE_F5, 32,
  NOTE_F5, 32,  NOTE_FS5, 32,  NOTE_G5, 32,  NOTE_G5, 32, NOTE_GS5, 32,  NOTE_A5, 16, NOTE_B5, 8
};

int notes = sizeof(melody) / sizeof(melody[0]) / 2;
int wholenote = (60000 * 4) / tempo;
int divider = 0, noteDuration = 0;
int thisNote = 0;

short int lcdPins[6] = {7, 6, 5, 4, 3, 2};

Renderer renderer(lcdPins);
Player player(0, 0);
Enimy enimy(56, 12);

short int enimyCanMove = 0;
short int state;

short int coinsSize = 1;
Coin coins[1];

short int score;

unsigned long startMillis;
unsigned long currentMillis;
short int overTime;

void start(){
  overTime = (short int)floor(millis()/1000);
  currentMillis = millis();
  score = 0;
  state = 0;
  enimy.restart(56, 12);
  player.restart(0, 0);
  
  for(short int i = 0; i < coinsSize; i++){
    short int cx = coins[i].getX();
    short int cy = coins[i].getY();
    
    coins[i].setRandomPosition();
    
    while(player.isColliding(cx, cy)){
      cx = coins[i].getX();
      cy = coins[i].getY();
      
      coins[i].setRandomPosition();
    }
  }
}

void setup() {
  state = 0;
  pinMode(8, INPUT_PULLUP);
  
  randomSeed(analogRead(2));
  start();
}

void loop() {
  if(state == 2){
    if(thisNote < notes * 2){
      divider = melody[thisNote + 1];
      if (divider > 0) {
        noteDuration = (wholenote) / divider;
      } else if (divider < 0) {
        noteDuration = (wholenote) / abs(divider);
        noteDuration *= 1.5;
      }
  
      tone(buzzer, melody[thisNote], noteDuration * 0.9);
      delay(noteDuration);
      noTone(buzzer);
      thisNote += 2;
    }else{
      notes = sizeof(melody) / sizeof(melody[0]) / 2;
      wholenote = (60000 * 4) / tempo;
      divider = 0, noteDuration = 0;
      thisNote = 0;
    }
  }
  
  if(digitalRead(8) == LOW){
    delay(500);
    
    if(state == 1 || state == 2){
      state = state == 1 ? 2 : 1;
    }else if(state == 0){
      startMillis = millis();
      state = 2;
    }
  }
    
  float y = ((float)analogRead(0)/500)-1;
  float x = ((float)analogRead(1)/500)-1;
  
  short int yn = round(y);
  short int xn = round(x);

  float c = 0.3;
  
  if((yn != player.getVY() && (y > c || y < -c)) || (xn != player.getVX() && (x > c || x < -c))){
    Rotation targetR = none;
    
    if(x > c){
      targetR = left;
    }else if(y > c){
      targetR = up;
    }else if(y < -c){
      targetR = down;
    }else if(x < -c){
      targetR = right;
    }

    player.rotate(targetR);
  }

  for(short int i = 0; i < coinsSize; i++){
    short int cx = coins[i].getX();
    short int cy = coins[i].getY();
    
    if(player.isColliding(cx, cy)){
      while(player.isColliding(cx, cy)){
        cx = coins[i].getX();
        cy = coins[i].getY();
        coins[i].setRandomPosition();
      }
      
      score++;
    }
  }

  short int ex = enimy.getX();
  short int ey = enimy.getY();
  
  if(player.isColliding(ex, ey))
    state = 3;
  
  if(millis() - currentMillis >= 150){
      String t = "TIME " + String(overTime - (short int)floor(startMillis/1000));
      String s = "SCORE " + String(score);
        
    switch(state){
      case 0:
        currentMillis = millis();
        renderer.setS1("NOT PACMAN");
        renderer.setS2("CLICK TO START");
        renderer.renderCenterText();
        break;
      case 1:
        currentMillis = millis();
      
        renderer.setS1("PAUSED");
        renderer.setS2("CLICK TO RESUME");
        renderer.renderCenterText();
        break;
      case 2:
        player.updatePlayer();
        enimyCanMove ++;
        
        if(enimyCanMove >= 5){
          enimyCanMove = 0;
          enimy.updateEnimy(player);
        }
        
        render();
        break;
      case 3:
        currentMillis = millis();
        renderer.setS1(s);
        renderer.setS2(t);
        renderer.renderCenterText();
        delay(3000);
        start();
        break;
    }
  }
}

void render(){
    currentMillis = millis();

    String s = String(score);
  
    while(s.length() < 4){
      s = "0" + s;
    }

    overTime= (short int)floor(millis()/1000);
    
    String t = String(overTime - (short int)floor(startMillis/1000));
  
    while(t.length() < 4){
      t = "0" + t;
    }
    
    renderer.setS1(s);
    renderer.setS2(t);
    renderer.render(player, enimy, coinsSize, coins);
}
