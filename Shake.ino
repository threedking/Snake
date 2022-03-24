#include <GameBoy.h>
#include "Snake.h"

/*
GameBoy gb;
Cherry *cherry;
SnakeGB *snake;

bool ai_on = false;
int key = 0;
bool pause = false;
int intensity = 7;
int game_delay = 300;
int game_delay_real = 300;
*/
void setup() {
  Serial.begin(9600);
  randomSeed(A0);

  /*
  gb.begin(intensity); 
    
  cherry = new Cherry(&gb);
  snake = new SnakeGB(&gb, cherry);*/
}
/*
void CheckPause(){
  if(key == 1){
    pause=!pause;
    ai_on = false;
    snake->SetAIIsOn(ai_on);   
    delay(500);
  }
}
*/
void loop() { /*
  static unsigned long last = 0, now;
  key = gb.getKey();
  Serial.print("Key ");Serial.println(key);
  CheckPause();
  if(!pause || ai_on){
    now = millis();
    if(!ai_on){
      snake->ChangeDirection(key);
    }
    if(now > last + game_delay_real){
      snake->SetAIIsOn(ai_on);
      snake->Tick(key);
      last = now;      
      game_delay_real = key == 2 ? game_delay/2 : game_delay;
      game_delay_real = ai_on ? game_delay/3 : game_delay_real;
    }
  }
  if(pause){
    if(key == 3){
      intensity += intensity < 15 ? 1 : 0;
      gb.setIntensity(intensity);
      delay(200);
    }
    if(key == 6){
      intensity -= intensity > 0 ? 1 : 0;
      gb.setIntensity(intensity);
      delay(200);
    }
    if(!ai_on){
      if(key == 4){      
        snake->SwitchNoWalls();
        delay(200);
      }
      if(key == 5){
        snake->SwitchEatSelf(); 
        delay(200);
      }
    }
    if(key == 2){      
      ai_on = !ai_on;      
      delay(500);
    }
  }*/
}
