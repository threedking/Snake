#include "Snake.h"

Snake::Snake(unsigned long new_delay_time, Coordinates<dimension_type> spawn_point): TimeUnit(new_delay_time){
  for(int i = 0; i < this->length_; i++){
    body_[i] = spawn_point;
  }
}

void Snake::Die(){
  this->is_alive_ = false;
}
void Snake::Grow(){ //Рост на 1
  if(this->length_ < this->body_array_length_){
    this->length_++;
    this->body_[this->length_-1] = this->body_[this->length_-2];
  }  
}
void Snake::ApplyEnergy(){
  if(this->energy_ >= this->required_energy_to_grow_){
    this->energy_ -= this->required_energy_to_grow_;
    Grow();
  }
}
void Snake::Move(){
  for(int i = this->length_ - 1; i > 0; i--){
    this->body_[i] = this->body_[i-1];
  }
  this->HeadStep();
}
void Snake::HeadStep(){
  this->body_[0].x_ += this->direction_ == Direction::left ? -1 : this->direction_ == Direction::right ? 1 : 0;
  this->body_[0].y_ += this->direction_ == Direction::up ? 1 : this->direction_ == Direction::down ? -1 : 0;
}

void Snake::Tick(unsigned long &now){
  if(!this->IsTickTime(now) || !this->CheckIsAlive()){
    return;
  }
  this->ApplyEnergy();
  this->Move();
  this->CheckIsAlive();
}
  
void Snake::SetDirection(Direction new_direction){
  switch(new_direction){
    case Direction::left:
    case Direction::right:
      if(this->direction_ == Direction::up || this->direction_ == Direction::down || this->direction_ == Direction::none){
        this->direction_ = new_direction;
      }
    break;
    case Direction::up:
    case Direction::down:
      if(this->direction_ == Direction::left || this->direction_ == Direction::right || this->direction_ == Direction::none){
        this->direction_ = new_direction;
      }
    break;
  }
}
bool Snake::CheckIsAlive(){
    this->is_alive_ = !(!this->is_alive_ || 
    this->length_ < this->min_length_ && this->energy_ < this->required_energy_to_grow_ );
  return this->is_alive_;
}
void Snake::Feed(const int energy){
  this->energy_ += energy;
}

int Snake::GetLength(){
  return this->length_;
}
Coordinates<dimension_type> Snake::GetCoordinatesOfBodyPart(unsigned int body_part_index){
  return body_part_index < this->length_ ? this->body_[body_part_index] : Coordinates<dimension_type>();
}
void Snake::BiteAt(unsigned int body_part_index){
  if(body_part_index < this->length_){
    this->length_ = body_part_index;
  }
}
int Snake::GetNutritionEnergy(){
  return this->nutrition_energy_;
}
Coordinates<dimension_type>* Snake::GetHeadCoordinatesPtr(){
  return &this->body_[0];
}
