#include <GameBoy.h>

class Cherry{
  int x;
  int y;
  GameBoy *gb;

public:
  Cherry(GameBoy *new_gb):gb(new_gb){
    this->CreateNew(0, 0);
  }
  void CreateNew(int new_x, int new_y){
    this->x = new_x;
    this->y = new_y;
  }  
  void CreateNewAndDraw(int new_x, int new_y){
    this->gb->wipePoint(this->x, this->y);
    this->CreateNew(new_x, new_y);
    this->gb->drawPoint(this->x, this->y);
  } 
  bool TryEat(int eat_x, int eat_y){
    return eat_x == this->x && eat_y == this->y;
  }
  void Draw(){
    this->gb->drawPoint(this->x, this->y);
  }
  int GetX(){
    return this->x;
  }
  int GetY(){
    return this->y;
  }
};

class SnakeGB{
  int mass[128][2]{};
  int lenght = 3;
  int direction = -1;
  bool direction_changed = false;
  bool use_ai = false;
  bool no_walls = false;
  bool eat_self = false;

  GameBoy *gb;
  Cherry *cherry;
public:
  SnakeGB(GameBoy *new_gb, Cherry *new_cherry):gb(new_gb), cherry(new_cherry){
    this->Start();
  }
  void Blink(unsigned int c){
    for(int t = 0; t < c; t++){
      for(int wd = 0; wd < 2; wd++){
        for(int i = 0; i < this->lenght; i++){
          if(wd==0){
            this->gb->wipePoint(this->mass[i][0], this->mass[i][1]);
          }else{
            this->gb->drawPoint(this->mass[i][0], this->mass[i][1]); 
          }
        }
        delay(100);
      }
    }
  }
  void SwitchNoWalls(){
    no_walls = !no_walls;
    Blink(3);
  }
  void SwitchEatSelf(){
    eat_self = !eat_self;
    Blink(3);
  }
  void MoveAndDraw(){ 
    this->gb->wipePoint(this->mass[this->lenght-1][0], this->mass[this->lenght-1][1]);
    this->Move();
    this->gb->drawPoint(this->mass[0][0], this->mass[0][1]);    
    this->cherry->Draw(); 
  }
  void Move(){            
    for(int i = this->lenght-1; i > 0; i--){
      this->mass[i][0]=this->mass[i-1][0];
      this->mass[i][1]=this->mass[i-1][1];
    }
    switch(this->direction){
      case 4:
        this->mass[0][0]--;
      break;
      case 5:
        this->mass[0][0]++;
      break;
      case 6:
        this->mass[0][1]++;
      break;
      case 3:
        this->mass[0][1]--;
      break;
    }
    if(this->no_walls){
      this->mass[0][0] = this->mass[0][0] < 0 ? 7 : (this->mass[0][0] > 7 ? 0 : this->mass[0][0]);
      this->mass[0][1] = this->mass[0][1] < 0 ? 15 : (this->mass[0][1] > 15 ? 0 : this->mass[0][1]);
    }
  }
  void ChangeDirection(int pressed_key){  
    if(this->direction_changed){
      return;
    }
    int new_direction = this->use_ai? this->GetAIDecision() : pressed_key;

    switch(new_direction){
      case 4:
      case 5:
        if(this->direction == 6 || this->direction == 3 || this->direction == -1){
          this->direction = new_direction;
          this->direction_changed = true;
        }
      break;
      case 6:
      case 3:
        if(this->direction == 4 || this->direction == 5 || this->direction == -1){
          this->direction = new_direction;
          this->direction_changed = true;
        }
      break;
    }
  }
  void Draw(){
    this->gb->clearDisplay();
    this->cherry->Draw();               
    for(int i = 0; i < this->lenght; i++){
      this->gb->drawPoint(this->mass[i][0], this->mass[i][1]);
    } 
  }
  bool CheckIsWin(){
    return this->lenght >= 128;
  }
  bool CheckIsDeath(){    
    if(this->mass[0][0] < 0 || this->mass[0][0] > 7 ||
       this->mass[0][1] < 0 || this->mass[0][1] > 15){
       return true;         
    }
    for(int i = 3; i < this->lenght; i++){
      if(this->mass[0][0] == this->mass[i][0] &&
        this->mass[0][1] == this->mass[i][1]){
          if(!eat_self){
            return true;
          }else{
            for(int j = i+1; j < this->lenght; j++){
              this->gb->wipePoint(this->mass[j][0], this->mass[j][1]);
            }
            this->lenght = i;
          }
      }
    } 
    return false;
  }
  void Start(){
    this->lenght = 3; 
    this->direction = -1;
    this->mass[0][0]=random(3,6);
    this->mass[0][1]=random(5,10);
    for(int i = 1; i < this->lenght; i++){
      this->mass[i][0]=this->mass[0][0];
      this->mass[i][1]=this->mass[0][1];
    } 
    this->CreateNewCherry();
    this->gb->testMatrix(5);
    this->Draw();
  }
  void TryEatCherry(){
    if(this->cherry->TryEat(this->mass[0][0], this->mass[0][1])){
      this->lenght++;
      this->mass[this->lenght-1][0]=this->mass[this->lenght-2][0];
      this->mass[this->lenght-1][1]=this->mass[this->lenght-2][1];
      this->CreateNewCherry();
    }
  }
  void CreateNewCherry(){
    int cherry_x, cherry_y;
    bool is_ok;
    do{
      cherry_x = random(0, 8);
      cherry_y = random(0, 16); 
      is_ok = true;
      for(int i = 0; i < this->lenght; i++){       
        if(cherry_x == this->mass[i][0] && cherry_y == this->mass[i][1]){
          is_ok = false;
        }
      }
      if(is_ok){
        this->cherry->CreateNew(cherry_x, cherry_y);
      }
    }while(!is_ok);    
  }
  void SetAIIsOn(bool new_use_ai){
    this->use_ai = new_use_ai;
  }
  bool CanMoveInDirection(int checking_dir){
    if(checking_dir < 3 || checking_dir > 6){  
      return false;
    }
    
    int next_x = this->mass[0][0];
    int next_y = this->mass[0][1];
    this->CalcStep(checking_dir, next_x, next_y);

    if( next_x < 0 || next_x > 7 ||
        next_y < 0 || next_y > 15){ //Если за границей
      return false;
    }
    
    for(int i = 3; i < this->lenght; i++){
      if(mass[i][0] == next_x && mass[i][1] == next_y){ //Если в себя
        return false;
      }
    }
    
    if( checking_dir == 3 && this->direction == 6 ||
        checking_dir == 6 && this->direction == 3 ||
        checking_dir == 4 && this->direction == 5 ||
        checking_dir == 5 && this->direction == 4 ){ //Если в спину
      return false;
    }
    return true;        
  }
  void CalcStep(int checking_direction, int &calc_x, int &calc_y){
    calc_x += checking_direction == 4 ? -1 : checking_direction == 5 ? 1 : 0;
    calc_y += checking_direction == 3 ? -1 : checking_direction == 6 ? 1 : 0;    
  }
  int GetAIDecision(){
    int no_walls_decision = GetAINoWallsDecision();    
    int next_x = mass[0][0];
    int next_y = mass[0][1];
    
    if(this->CanMoveInDirection(no_walls_decision)){  //Если можно ходить, куда хотим
      return no_walls_decision;
    }else{
      if(this->CanMoveInDirection(this->direction)){  //Если можно идти вперед        
        return this->direction >= 3 && this->direction <= 6 ? this->direction : random(3, 7);
      }else{
        for(int i=3; i<7; i++){  //Чекнуть все
          if(this->CanMoveInDirection(i)){
            return i;                
          }
        }
        return 3;
      }
    }
    return 3;
  }
  int GetAINoWallsDecision(){
     // 3 up; 6 down; 4 left; 5 right;
    int diff_x, diff_y;
    diff_x = mass[0][0] - this->cherry->GetX();
    diff_y = mass[0][1] - this->cherry->GetY();
      
    if(abs(diff_x) > abs(diff_y)){  
      if(this->direction == 3 || this->direction == 6 || this->direction == -1){ //Если перпердикулярны цели
        return diff_x > 0 ? 4 : 5;
      }else{
        if(this->direction == 4 && diff_x < 0 ||
           this->direction == 5 && diff_x > 0 ){ //Если надо развернуться
          return diff_y > 0 ? 3 : 6;
        }else{
          return diff_y > 0 ? 4 : 5;  
        }
      }
    }else if(abs(diff_x) < abs(diff_y)){  
      if(this->direction == 4 || this->direction == 5 || this->direction == -1){ //Если перпердикулярны цели        
        return diff_y > 0 ? 3 : 6;
      }else{
        if(this->direction == 3 && diff_y < 0 ||
           this->direction == 6 && diff_y > 0 ){ //Если надо развернуться
          return diff_x > 0 ? 4 : 5;
        }else{
          return diff_x > 0 ? 3 : 6;  
        }
      }    
    }else{
      return this->direction == -1 ? random(3, 7) : this->direction;
    }        
    return random(3, 7);
  }  
  void Tick(int pressed_key){
    this->ChangeDirection(pressed_key);
    this->direction_changed = false;
    
    //this->Move();
    this->MoveAndDraw();
    
    this->TryEatCherry();
    if(this->CheckIsDeath() || this->CheckIsWin()){
      Serial.println(this->CheckIsWin()?"I AM WIN!!!!!":"I AM DEATH!!!!!");
      this->Start();
    }
    //this->Draw();
  }
};

GameBoy gb;
Cherry *cherry;
SnakeGB *snake;

bool ai_on = false;
int key = 0;
bool pause = false;
int intensity = 7;
int game_delay = 300;
int game_delay_real = 300;

void setup() {
  Serial.begin(9600);
  gb.begin(intensity); 
    
  cherry = new Cherry(&gb);
  snake = new SnakeGB(&gb, cherry);
}

void CheckPause(){
  if(key == 1){
    pause=!pause;
    ai_on = false;
    snake->SetAIIsOn(ai_on);   
    delay(500);
  }
}

void loop() {
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
  }
}
