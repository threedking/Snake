#include "Food.h"

//----------------
Food::Food(Coordinates<dimension_type> new_coordinates) :coordinates_(new_coordinates){
}
//----------------
bool Food::TryEat(Coordinates<dimension_type> eat_coordinates){
  return this->coordinates_ == eat_coordinates;
}
//----------------
Coordinates<dimension_type> Food::GetCoordinates(){
  return this->coordinates_;
}
//----------------
int Food::GetNutritionEnergy(){
  return this->is_exist_ ? this->nutrition_energy_ : 0;
}
//----------------
void Food::Tick(){
  return;
}
//----------------
void Food::Destroy(){
  this->is_exist_ = false;
}
//----------------
bool Food::GetIsExist(){
  return this->is_exist_;
}
//----------------
void Food::Restore(Coordinates<dimension_type> new_coordinates){
  this->coordinates_ = new_coordinates;
  this->is_exist_ = true;  
}
//----------------
//----------------
//----------------
Cherry::Cherry(Coordinates<dimension_type> new_coordinates):Food(new_coordinates){
  this->nutrition_energy_ = 1;
}
//----------------
