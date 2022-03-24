#include "World.h"

World::World(dimension_type new_limit_x, dimension_type new_limit_y):limit_x_(new_limit_x), limit_y_(new_limit_y){
  
}

Coordinates<dimension_type> World::FindFreePlace(){
  Coordinates<dimension_type> free_place{};

  do{
    free_place.x_ = Random::GetRandom(this->limit_x_);
    free_place.y_ = Random::GetRandom(this->limit_y_);  
  }while(this->IsCollideWithWorldParts(free_place));
  
  return free_place;
}

bool World::IsCollideWithWorldParts(Coordinates<dimension_type> checking_place){
  
  for(int it_s = 0; it_s < this->amount_snakes_; it_s++){
    if(!this->snakes_[it_s]){continue;}
    for(int i = 0; i < this->snakes_[it_s]->GetLength(); i++){
      if(this->snakes_[it_s]->CheckIsAlive() && checking_place == this->snakes_[it_s]->GetCoordinatesOfBodyPart(i)){
        return true;
      }
    }
  }
  for(int it_f = 0; it_f < this->amount_food_; it_f++){
    if(this->food_[it_f]->GetIsExist() && checking_place == this->food_[it_f]->GetCoordinates()){
      return true;
    }
  }
  for(int it_w = 0; it_w < this->amount_wall_; it_w++){
    if(this->wall_[it_w]->GetIsExist() && checking_place == this->wall_[it_w]->GetCoordinates()){
      return true;
    }
  }
  
  return false;
}

void World::DestroyAndRestoreFood(Food *food){
  if(!food){
    return;
  }  
  food->Destroy();
  food->Restore(this->FindFreePlace());
  //переделать чтобы работало в конце
}

void World::Tick(){
  for(int i = 0; i < this->amount_snakes_; i++){
    if(!this->snakes_[i]){
      continue;
    }
    if(!this->snakes_[i]->CheckIsAlive()){
      continue;
    }

    for(int j = 0; j < this->amount_wall_; j++){  //Змея - стена
      if( this->snakes_[i]->GetCoordinatesOfBodyPart(0) == this->wall_[j]->GetCoordinates() ){        
        this->snakes_[i]->Die();
        break;
      }
    }  
    if(!this->snakes_[i]->CheckIsAlive()){
      continue;
    }

    for(int j = 0; j < this->amount_food_; j++){  //Змея - еда
      if( this->snakes_[i]->GetCoordinatesOfBodyPart(0) == this->food_[j]->GetCoordinates() ){
        this->snakes_[i]->Feed(this->food_[j]->GetNutritionEnergy()); 
        this->DestroyAndRestoreFood(this->food_[j]);
      }
    }
    
    for(int j = 0; j < this->amount_snakes_; j++){  //Змея - змея    
      if(!this->snakes_[j]){
        continue;
      }
      if(!this->snakes_[j]->CheckIsAlive()){
        continue;
      }
      if(i != j){
        if(this->snakes_[i]->GetCoordinatesOfBodyPart(0) == this->snakes_[j]->GetCoordinatesOfBodyPart(0)){
          this->snakes_[i]->Die();
          this->snakes_[j]->Die();
          break;
        }
      }
      for(int z = 1; z < this->snakes_[j]->GetLength(); z++){
        if(this->snakes_[i]->GetCoordinatesOfBodyPart(0) == this->snakes_[j]->GetCoordinatesOfBodyPart(z)){
          this->snakes_[i]->Feed(this->snakes_[j]->GetNutritionEnergy());
          if(this->snakes_leave_parts_){
            for(int c = z+1; c < this->snakes_[j]->GetLength(); c++){
              this->snakes_[j]->GetCoordinatesOfBodyPart(c); //TODO это еда
            }
          }
          this->snakes_[j]->BiteAt(z);
          break;
        }
      }      
    }
  }
  
}
  
void World::AddSnake(Snake *new_snake){
  if(!new_snake){
    return;
  }
  if(this->amount_snakes_ < this->snakes_array_length_){
    snakes_[this->amount_snakes_] = new_snake;
    this->amount_snakes_++;
  }  
}
